//
// Created by jazema on 31/03/2026.
//

#ifndef SERVERDATA_HPP
#define SERVERDATA_HPP
#include <map>
#include <string>

#include "Channel.hpp"

class ServerData {
	private:
		std::string						_serverName;
		std::string						_serverPassword;

		std::map<std::string, Channel>	_channels; //liste de tous les channels
	public:
		const std::string				&getServerName() const;
		void							setServerName(const std::string &serverName);

		const std::string				&getServerPassword() const;
		void							setServerPassword(const std::string &serverPassword);

		std::map<std::string, Channel>	&getChannels();
		Channel							&getChannel(const std::string &channelName);
		bool							existsChannel(const std::string &name);
		Channel							&createChannel(const std::string &channelName);
		void							deleteChannel(const std::string &channelName);
};

#endif
