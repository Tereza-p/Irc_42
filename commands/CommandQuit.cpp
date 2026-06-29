//
// Created by jazema on 4/4/26.
//

#include "CommandQuit.hpp"

#include "../client/Client.hpp"
#include "../server/Server.hpp"

void CommandQuit::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	std::string quitMessage = args[0];

	if (quitMessage.empty())
		quitMessage = "Client Quit";
	client.sendMessage("ERROR :Closing Link: " + client.getNickname() + "[" + client.getUsername() + "@" + client.getHostname() + "] (" + quitMessage + ")");

	for (std::map<std::string, Channel>::iterator it = server.getServerData().getChannels().begin(); it != server.getServerData().getChannels().end(); it++)
	{
		if (it->second.isMember(client.getClientFd()))
		{
			server.broadcast(it->second, client.buildPrefix() + " QUIT :" + quitMessage);
		}
	}
	server.closeClient(client);
}

