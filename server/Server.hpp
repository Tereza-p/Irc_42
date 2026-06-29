/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nardis <nardis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:12:31 by elaudrez          #+#    #+#             */
/*   Updated: 2026/04/03 09:52:26 by nardis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <netinet/in.h>

#include "../client/Client.hpp"
#include "ServerData.hpp"
#include "../commands/CommandManager.hpp"

class Server
{
    private:
        int            _serverFd;
        sockaddr_in    _serverAddr; //struct qui contient family adress, port, adress internet. Pour adrr IPv4
        ServerData     _serverData;
        CommandManager _commandManager;

        std::map<int, Client> _clients;

        int     _epollFd;

        void    acceptClient();
        void    handleClientInput(Client &client);

        void    executeCommand(Client &client, const std::string &command);

    public :
        Server();
        ~Server();

        void    createSocket();
        void    bindSocket(long port);

        void    run();
        void    shutdown();

        int     getServerFd() const;

        ServerData      &getServerData();
        CommandManager  &getCommandManager();

        std::map<int, Client>   &getClients();
        Client                  &getClient(int clientId);
        bool                    existsClient(const std::string &nickName);
        Client                  &getClientByNickname(const std::string &nickName);

		void	closeClient(Client &client);

		void	broadcast(const std::string &message);
		void	broadcast(const Channel &channel, const std::string &message);
};

#endif
