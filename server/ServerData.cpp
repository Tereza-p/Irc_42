//
// Created by jazema on 31/03/2026.
//

#include "ServerData.hpp"

const std::string &ServerData::getServerName() const
{
	return (this->_serverName);
}

void ServerData::setServerName(const std::string &serverName)
{
	this->_serverName = serverName;
}

const std::string &ServerData::getServerPassword() const
{
	return (this->_serverPassword);
}

void ServerData::setServerPassword(const std::string &serverPassword)
{
	this->_serverPassword = serverPassword;
}

std::map<std::string, Channel> &ServerData::getChannels()
{
	return (this->_channels);
}

Channel &ServerData::getChannel(const std::string &channelName)
{
	return (this->_channels.find(channelName)->second);
}

bool ServerData::existsChannel(const std::string &name)
{
	return (this->_channels.find(name) != this->_channels.end());
}

Channel &ServerData::createChannel(const std::string &channelName)
{
	if (existsChannel(channelName))
		return (getChannels().find(channelName)->second);
	this->_channels.insert(std::make_pair(channelName, Channel(channelName)));
	return (this->_channels.at(channelName));
}

void	ServerData::deleteChannel(const std::string &channelName)
{
	if (!existsChannel(channelName))
		return ;
	this->_channels.erase(channelName);
}
