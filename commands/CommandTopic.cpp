//
// Created by jazema on 4/4/26.
//

#include "CommandTopic.hpp"

#include <string>

#include "Irc.hpp"
#include "../client/Client.hpp"
#include "../helpers/MsgBuilder.hpp"
#include "../server/Server.hpp"

void CommandTopic::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (args.size() == 0)
	{
		client.sendMessage(msgBuilder.errNeedMoreParams("TOPIC"));
		return;
	}
	if (!server.getServerData().existsChannel(args[0]))
	{
		client.sendMessage(msgBuilder.errNoSuchChannel(args[0]));
		return;
	}
	Channel &channel = server.getServerData().getChannel(args[0]);

	if (!channel.isMember(client.getClientFd()))
	{
		client.sendMessage(msgBuilder.format(ERR_NOTONCHANNEL , channel.getName() + " :You're not on that channel"));
		return;
	}
	if (args.size() == 1)
	{
		std::string topic = channel.getTopic();
		if (topic.empty())
		{
			//fonction existe !
			client.sendMessage(msgBuilder.format(RPL_NOTOPIC, channel.getName() + " :No topic is set"));
			return;
		}
		//fonction existe !
		client.sendMessage(msgBuilder.format(RPL_TOPIC, channel.getName() + " :" + topic));
		return;
	}
	if (channel.hasTopicRestriction() && !channel.isOp(client.getClientFd()))
	{
		client.sendMessage(msgBuilder.format(ERR_CHANOPRIVSNEEDED, channel.getName() + " :You're not channel operator"));
		return;
	}
	channel.setTopic(args[1]);
	server.broadcast(channel, ":" + client.buildPrefix() + " TOPIC " + channel.getName() + " :" + args[1]);
}
