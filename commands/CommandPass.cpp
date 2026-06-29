//
// Created by jazema on 02/04/2026.
//

#include "CommandPass.hpp"

#include <iostream>
#include <string>

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../helpers/MsgBuilder.hpp"

void CommandPass::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (client.isRegistered()) //si ya deja le nick ?
	{
		client.sendMessage(msgBuilder.errArlreadyRegistered());
		return ;
	}
	if (args.size() != 1)
	{
		client.sendMessage(msgBuilder.errNeedMoreParams("PASS"));
		return;
	}
	client.passReceived();
	if (args[0] != server.getServerData().getServerPassword())
	{
		client.sendMessage(msgBuilder.errPasswdMismatch());
		return ;
	}
	client.passValid();
}
