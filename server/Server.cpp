/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:12:20 by elaudrez          #+#    #+#             */
/*   Updated: 2026/04/05 15:23:25 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <cerrno>

#include "../Irc.hpp"
#include "Server.hpp"
#include "../commands/Command.hpp"
#include "../helpers/MsgBuilder.hpp"

#include "../commands/CommandCap.hpp"
#include "../commands/CommandJoin.hpp"
#include "../commands/CommandMode.hpp"
#include "../commands/CommandMotd.hpp"
#include "../commands/CommandPass.hpp"
#include "../commands/CommandPrivMsg.hpp"
#include "../commands/CommandUser.hpp"
#include "../commands/CommandNick.hpp"
#include "../commands/CommandQuit.hpp"
#include "../commands/CommandTopic.hpp"
#include "../commands/CommandWhois.hpp"
#include "commands/CommandPart.hpp"

Server::Server() : _serverFd(-1), _epollFd(-1)
{
	// Le constructeur du serveur va nous servir à register toutes les commandes
	this->_commandManager.registerCommand<CommandPrivMsg>("PRIVMSG");
	this->_commandManager.registerCommand<CommandMode>("MODE");
	this->_commandManager.registerCommand<CommandUser>("USER");
	// this->_commandManager.registerCommand<CommandCap>("CAP");
	this->_commandManager.registerCommand<CommandJoin>("JOIN");
	this->_commandManager.registerCommand<CommandPart>("PART");
	this->_commandManager.registerCommand<CommandPass>("PASS");
	this->_commandManager.registerCommand<CommandNick>("NICK");
	this->_commandManager.registerCommand<CommandWhois>("WHOIS");
	this->_commandManager.registerCommand<CommandQuit>("QUIT");
	this->_commandManager.registerCommand<CommandMotd>("MOTD");
	this->_commandManager.registerCommand<CommandTopic>("TOPIC");
}

Server::~Server()
{
	// On s'assure que le fd du socket soit bien fermé (shutdown)
	this->shutdown();
}

void Server::createSocket()
{
	//Creation du socket serveur
	this->_serverFd = socket(AF_INET, SOCK_STREAM, 0); // = int domain : AF_INET (domaine de communication, la famille d'adresse, IPv(AF_INET), IPv6(AF_INET6), locale(AF_LOCAL),...) | int type : SOCK_STREAM ou SOCK_DGRAM | int protocol: le protocole a utiliser. 0 = utiliser le protocle par defaut associe au domain et type donc TCP pour SOCK_STREAM
	if (this->_serverFd < 0)
		throw std::runtime_error("Socket's creation failed");
	fcntl(this->_serverFd, F_SETFL, O_NONBLOCK);
}

void	Server::bindSocket(long port)
{
	int opt = 1;

	setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	//Associer socket a un port local et une adrr IP. Config de l'addresse du socket
	std::memset(&this->_serverAddr, 0, sizeof(this->_serverAddr)); //initialiser this->_serverAddr
	this->_serverAddr.sin_family = AF_INET;
	this->_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //dans sockadrr_in y'a une struc+t in_addr qui contient s_addr | Host To Network LONG, ecouter sur toutes les interfaces reseau de la machine
	this->_serverAddr.sin_port = htons(port); //Defini le port en NBO | Host to Network Short
	if (bind(this->_serverFd, (struct sockaddr *)&this->_serverAddr, sizeof(this->_serverAddr)) == -1) // Associer le server_fd a this->_serverAddr notamment sur le port sur lequel il doit ecouter, bind() avant de listen() sinon ecoutera sur n'importquel port
		throw std::runtime_error ("Not possible to bind the socket");
	// Mettre le socket en mode ecoute
	if (listen(this->_serverFd, SOMAXCONN) == -1) // nb de connection autorisee dans la file entrante. les connections vont attendre jusqu'a etre acceptees avec accept()
		throw std::runtime_error("Not possible to put the socket in listen mode");
	std::cout << "IRC Server started ! Listening on port " << port << std::endl;
}

void Server::run()
{
	//Creation de l'instance de surveillance epoll
	this->_epollFd = epoll_create1(0);

	this->getServerData().setServerName("best.irc.42");
	if (this->_epollFd == -1)
	{
		this->shutdown();
		throw std::runtime_error("Failed to create epoll fd");
	}

	epoll_event	server_event;

	//Initialisation de la ficher surveillance de server
	server_event.events = EPOLLIN;
	server_event.data.fd = this->_serverFd;


	//Ajout de la fiche de surveillance de server dans epoll (l'instance qui surveille)
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, this->_serverFd, &server_event) == -1)
    {
		this->shutdown();
        throw std::runtime_error("Failed to add server fd to epoll");
    }

	epoll_event tracking_tab[100];

	while (true)
	{
		//std::cout << "Polling for input..." << std::endl;

		int	n_events = epoll_wait(this->_epollFd, tracking_tab, 100, -1);

		for (int i = 0; i < n_events; i++) // Boucler sur tracking_tab qui contient les events qui se sont declenches
		{
			// Si event vient du socket serveur, ca veut dire qu'un client demande a se connecter donc creation d'un nv socket
			if (tracking_tab[i].data.fd == this->_serverFd)
			{
				this->acceptClient();
				continue;
			}
			//Sinon ca veut dire requete d'un client deja existant
			Client &currentClient = this->getClient(tracking_tab[i].data.fd);

			if (tracking_tab[i].events & (EPOLLERR | EPOLLHUP))
			{
				closeClient(currentClient);
				continue;
			}
			this->handleClientInput(currentClient);
		}
	}
}

void Server::executeCommand(Client &client, const std::string &command)
{
	Command cmd(command);
	CommandManager &command_manager = this->getCommandManager();

	if (command_manager.getCommandExecutor(cmd.cmd) != NULL)
	{
		command_manager.getCommandExecutor(cmd.cmd)->execute(*this, client, cmd.params);
		return;
	}

	client.sendMessage(MsgBuilder(this->_serverData.getServerName(), client.getNickname()).format(421, cmd.cmd + " :Unknown command"));
}

void Server::acceptClient()
{
	sockaddr_in client_addr;
	socklen_t   client_addr_len;
	int         newClientFd;

	client_addr_len = sizeof(client_addr);
	newClientFd = accept(this->_serverFd, (sockaddr *)&client_addr, &client_addr_len);
	if (newClientFd == -1)
		throw std::runtime_error("Could not accept new client connection");

	//on insert en apelant le ctor special de Client ! #swag
	this->_clients.insert(std::make_pair(newClientFd, Client(newClientFd, client_addr, client_addr_len)));

	//reference = alias
	Client &client = this->getClient(newClientFd);

	client.initClient();

	fcntl(client.getClientFd(), F_SETFL, O_NONBLOCK); //rendre socket non bloquant,

	// Ajouter le nv client a l'instance de surveillance epoll
	epoll_event client_event; // role temporaire, sert a ajouter un client_fd a epoll pour etre surveille, est reutilise pour chaque creation de socket client
	client_event.events = EPOLLIN | EPOLLERR | EPOLLHUP; // + epollerror ?
	client_event.data.fd = client.getClientFd();

	epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, client.getClientFd(), &client_event);

	std::cout << "Client connected : " << client.getIp() << ":" << client.getPort() << std::endl;
}

void Server::closeClient(Client &client)
{
	int clientFd = client.getClientFd();

	std::cout << red << "Client disconnected : " << reset << clientFd << std::endl;
	epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, clientFd, NULL);
	close(clientFd);
	this->_clients.erase(clientFd);
	for (std::map<std::string, Channel>::iterator it = this->_serverData.getChannels().begin(); it != this->_serverData.getChannels().end(); it++)
	{
		if (it->second.isMember(clientFd))
		{
			it->second.removeMember(clientFd);
			it->second.removeOp(clientFd);
			//todo voir si il faut broadcast ? ou supprimer un channel vide ? dans ce cas pourquoi pas faire un joinChannel(Client, Channel) et leaveChannel(Client, Channel) dans Server
		}
	}
}


void Server::handleClientInput(Client &client)
{
	char	buffer[1024];
	ssize_t bytes_read;
	int		clientFd;

	clientFd = client.getClientFd();
	bytes_read = read(clientFd, buffer, sizeof(buffer));
	if (bytes_read <= 0)
	{
		// if (bytes_read == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
			// return; // ← pas de données dispo, socket non-bloquant, c'est normal
		closeClient(client);
		return;
	}
	buffer[bytes_read] = '\0';
	client.appendBuffer(buffer);

	std::string &buf = client.getInputBuffer();
	size_t tmp;

	std::cout << green << "Handling client " << client.getClientFd() << " input ="  << buffer << reset << std::endl;
	while ((tmp = buf.find("\r\n")) != std::string::npos)
	{
		std::string currentCommand = buf.substr(0, tmp);
		std::cout << "[CLIENT " << client.getClientFd() << "] << " << currentCommand << std::endl;
		buf.erase(0, tmp + 2);
		this->executeCommand(client, currentCommand);
		if (this->_clients.find(clientFd) == this->_clients.end())
			break;
	}
}

void Server::shutdown()
{
	if (this->_serverFd != -1)
	{
		close(this->_serverFd);
		this->_serverFd = -1;
	}
	if (this->_epollFd != -1)
	{
		close(this->_epollFd);
		this->_epollFd = -1;
	}
}

int Server::getServerFd() const
{
	return (this->_serverFd);
}

CommandManager &Server::getCommandManager()
{
	return (this->_commandManager);
}

ServerData &Server::getServerData()
{
	return (this->_serverData);
}

Client &Server::getClient(int clientId)
{
	std::map<int, Client>::iterator it = this->_clients.find(clientId);
	if (it == this->_clients.end())
		throw std::runtime_error("Client not found");
	return it->second;
}

bool Server::existsClient(const std::string &nickName)
{
	std::map<int, Client>::iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (it->second.getNickname() == nickName)
			return (true);
		it++;
	}
	return (false);
}


Client &Server::getClientByNickname(const std::string &nickName)
{
	for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
	{
		if (it->second.getNickname() == nickName)
			return (it->second);
	}
	throw std::runtime_error("Client not found");
}


std::map<int, Client> &Server::getClients()
{
	return (this->_clients);
}

void Server::broadcast(const std::string &message)
{
	for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		it->second.sendMessage(message);
	}
}

void Server::broadcast(const Channel &channel, const std::string &message)
{
	for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (channel.isMember(it->second.getClientFd()))
			it->second.sendMessage(message);
	}
}
