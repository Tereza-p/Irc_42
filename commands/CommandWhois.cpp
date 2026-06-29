//
// Created by jazema on 03/04/2026.
//

#include "CommandWhois.hpp"

#include <iostream>

#include "../Irc.hpp"
#include "../client/Client.hpp"
#include "../helpers/MsgBuilder.hpp"
#include "../server/Server.hpp"

void CommandWhois::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (args.size() == 0)
	{
		client.sendMessage(msgBuilder.errNoNicknameGiven());
		return;
	}
	if (!server.existsClient(args[0]))
	{
		std::cout << "Unknown client " << args[0] << std::endl;
		client.sendMessage(msgBuilder.format(ERR_NOSUCHNICK, args[0] + " :No such nick/channel"));
		return;
	}
	Client &target = server.getClientByNickname(args[0]);

	client.sendMessage(msgBuilder.format(RPL_WHOISUSER, target.getNickname() + " " + target.getUsername() + " " + target.getHostname() + " * :" + target.getRealname()));
	client.sendMessage(msgBuilder.format(RPL_WHOISSERVER, target.getNickname() + " " + server.getServerData().getServerName() + " :Serveur IRC"));
	client.sendMessage(msgBuilder.format(RPL_ENDOFWHOIS, target.getNickname() + ": End of WHOIS list"));
}
