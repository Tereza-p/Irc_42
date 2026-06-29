//
// Created by jazema on 4/4/26.
//

#include "CommandPart.hpp"

#include "../client/Client.hpp"
#include "../helpers/MsgBuilder.hpp"
#include "../helpers/StringHelper.hpp"
#include "../server/Server.hpp"

void CommandPart::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	MsgBuilder msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (args.size() == 0)
	{
		client.sendMessage(msgBuilder.errNeedMoreParams("PART"));
		return;
	}
	std::vector<std::string> channels;

	channels = StringHelper::split(args[0], ",");
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (!server.getServerData().existsChannel(channels[i]))
		{
			client.sendMessage(msgBuilder.errNoSuchChannel(channels[i]));
			continue;
		}
		Channel &channel = server.getServerData().getChannel(channels[i]);

		if (!channel.isMember(client.getClientFd()))
		{
			client.sendMessage(msgBuilder.errNotOnChan(channels[i]));
			continue;
		}
		server.broadcast(channel, ":" + client.buildPrefix() + " PART " + channels[i] + (args.size() > 1 ? " :" + args[1] : ""));
		channel.removeMember(client.getClientFd());
	}
}
