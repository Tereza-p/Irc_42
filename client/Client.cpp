/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:09:07 by elaudrez          #+#    #+#             */
/*   Updated: 2026/04/05 15:24:18 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>

Client::Client(int clientFd, const sockaddr_in &address, socklen_t &addressLen) : _client_fd(clientFd), _client_addr(address), _client_addr_len(addressLen)
{
}

void Client::initClient()
{
	// Convertir l'adresse binaire sous forme de texte
	inet_ntop(AF_INET, &(this->_client_addr.sin_addr), this->_client_ip, this->_client_addr_len);
}

int Client::getClientFd() const
{
	return (this->_client_fd);
}

const std::string &Client::getUsername() const
{
	return (this->_username);
}

void Client::setUsername(const std::string &username)
{
	this->_username = username;
}

const std::string &Client::getNickname() const
{
	return (this->_nickname);
}

void Client::setNickname(const std::string &nickname)
{
	this->_nickname = nickname;
}

const std::string &Client::getRealname() const
{
	return (this->_realname);
}

void Client::setRealname(const std::string &realname)
{
	this->_realname = realname;
}

const std::string &Client::getHostname() const
{
	return (this->_hostname);
}

void Client::setHostname(const std::string &hostname)
{
	this->_hostname = hostname;
}

bool Client::isRegistered() const
{
	return (this->_authData.nickSet && this->_authData.userSet && (this->_authData.passValid));
}

void Client::sendMessage(const std::string &message) const
{
	std::cout << "[CLIENT " << this->getClientFd() << "] >> " << message << std::endl;
	std::string finalMessage = message + "\r\n";
	send(this->_client_fd, finalMessage.c_str(), finalMessage.length(), 0);
}

std::string Client::getIp() const
{
	return (this->_client_ip);
}

int Client::getPort() const
{
	return (ntohs(this->_client_addr.sin_port));
}

void Client::appendBuffer(const std::string &newPart)
{
	this->_inputBuffer += newPart;
}

std::string &Client::getInputBuffer()
{
	return (this->_inputBuffer);
}

std::string Client::buildPrefix() const
{
	return (this->_nickname + "!" + this->_username + "@" + this->_hostname);
}

bool Client::isPasswordValid() const
{
	return (this->_authData.passValid);
}

bool Client::isNickSet() const
{
	return (this->_authData.nickSet);
}

bool Client::isUserSet() const
{
	return (this->_authData.userSet);
}

void Client::passReceived()
{
	this->_authData.passReceived = true;
}

void Client::nickSet()
{
	this->_authData.nickSet = true;
}

void Client::passValid()
{
	this->_authData.passValid = true;
}

void Client::userSet()
{
	this->_authData.userSet = true;
}

UserModes &Client::getModes()
{
	return (this->_modes);
}

