//
// Created by jazema on 4/4/26.
//

#include "CommandMotd.hpp"

#include "Irc.hpp"
#include "../client/Client.hpp"
#include "../helpers/MsgBuilder.hpp"
#include "../server/Server.hpp"

//motd == comand ?
void CommandMotd::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	(void)args;
	client.sendMessage(msgBuilder.motdStart());
	client.sendMessage(msgBuilder.motdMsg());
	client.sendMessage(msgBuilder.motdEnd());
}

