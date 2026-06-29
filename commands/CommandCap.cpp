//
// Created by jazema on 02/04/2026.
//

#include "CommandCap.hpp"

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../helpers/MsgBuilder.hpp"

void CommandCap::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	std::string	nick;
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	nick = "*";
	if (client.isRegistered())
		nick = client.getNickname();
	if (args[0] == "LS")
	{
		client.sendMessage(msgBuilder.capMsg(""));
		return;
	}
	if (args[0] == "END")
	{
		;
	}
}

