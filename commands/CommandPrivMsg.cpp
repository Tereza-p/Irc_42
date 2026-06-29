//
// Created by jazema on 01/04/2026.
//

#include "CommandPrivMsg.hpp"

#include <set>

#include "../Irc.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../helpers/MsgBuilder.hpp"
#include "../helpers/StringHelper.hpp"

void CommandPrivMsg::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (args.size() < 2)
	{
		client.sendMessage(msgBuilder.errNeedMoreParams("PRIVMSG"));
		return;
	}
	// on vérifie le début du premier arg pour savoir si on veut envoyer le message dans un channel
	if (StringHelper::startsWith(args[0], "#") || StringHelper::startsWith(args[0], "&"))
	{
		if (!server.getServerData().existsChannel(args[0]))
		{
			client.sendMessage(msgBuilder.errNoSuchChannel(args[0]));
			return;
		}
		Channel &channel = server.getServerData().getChannel(args[0]);

		if (!channel.isMember(client.getClientFd()))
		{
			//todo erreur??
			return;
		}
		// On envoie le message aux membres du channel
		for (std::set<int>::iterator it = channel.getMembers().begin(); it != channel.getMembers().end(); ++it)
		{
			int currentMember = *it;

			// Si c'est le client qui a exécuté la commande, on ne fait rien et on passe au suivant
			if (currentMember == client.getClientFd())
				continue;
			//no space after : !
			server.getClient(currentMember).sendMessage(":" + client.buildPrefix() + " PRIVMSG " + args[0] + " :" + args[1]);
		}
		return;
	}
	if (!server.existsClient(args[0]))
	{
		client.sendMessage(msgBuilder.format(ERR_NOSUCHNICK, args[0] + " :No such nick/channel"));
		return;
	}
	Client &target = server.getClientByNickname(args[0]);
	target.sendMessage(":" + client.buildPrefix() + " PRIVMSG " + args[0] + " :" + args[1]);
}
