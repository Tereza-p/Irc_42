//
// Created by jazema on 02/04/2026.
//

#include "CommandJoin.hpp"

#include <map>

#include "../client/Client.hpp"
#include "../helpers/MsgBuilder.hpp"
#include "../server/Server.hpp"

class Channel;

static bool    parseNameChannel(std::string name)
{
	std::string toBegin = "#&+!";

	if (name.empty() || toBegin.find(name[0]) == std::string::npos || name.length() > 50)
		return false;
	for(unsigned int i = 1; i < name.size(); i++)
	{
		unsigned char c = name[i];

		if (c == ' ' || c == ',' || c < 32 || c == 127)
			return false;
	}
	return true;
}

const std::string concatMembers(Server &server,  Channel &channel)
{
	std::string str;

	for (std::set<int>::iterator it = channel.getMembers().begin(); it != channel.getMembers().end(); it++)
	{
		Client &client = server.getClient(*it);
		if (channel.isOp(*it))
			str += "@";
		str += client.getNickname() + " ";
	}
	return str;
}

void CommandJoin::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	std::string channelName;
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (!client.isRegistered())
		return;
	if (args.size() == 0)
	{
		client.sendMessage(msgBuilder.errNeedMoreParams("JOIN"));
		return;
	}
	channelName = args[0];
	if (!parseNameChannel(channelName))
	{
		client.sendMessage(msgBuilder.errNoSuchChannel(args[0]));
		return ;
	}

	if (!server.getServerData().existsChannel(channelName))
	{
		Channel &newChannel = server.getServerData().createChannel(channelName);

		newChannel.addOp(client.getClientFd());
	}

	Channel &channel = server.getServerData().getChannel(channelName);

	if (channel.hasInvitationMode() && !channel.isInvited(client.getClientFd()))
	{
		//ERR_INVITEONLYCHAN
		client.sendMessage(msgBuilder.format(473, channel.getName() + " :Cannot join channel (+i)"));
		return;
	}

	if (channel.hasPassword() && (args.size() < 2 || !channel.checkPassword(args[1])))
	{
		// ERR_BADCHANNELKEY
		client.sendMessage(msgBuilder.format(475, channel.getName() + " :Cannot join channel (+k)"));
		return;
	}

	if (channel.isFull())
	{
		// ERR_CHANNELISFULL
		client.sendMessage(msgBuilder.format(471, channel.getName() + " :Cannot join channel (+l)"));
		return;
	}

	channel.removeInvitation(client.getClientFd());

	channel.addMember(client.getClientFd());

	server.broadcast(channel, msgBuilder.joinMsg(client, channelName));
	if (channel.getTopic().empty())
		client.sendMessage(msgBuilder.noTopic(channel.getName()));
	else
		client.sendMessage(msgBuilder.getTopic(channel.getName(), channel.getTopic()));
	client.sendMessage(msgBuilder.memberList(channel.getName(), concatMembers(server, channel)));
	client.sendMessage(msgBuilder.memberListEnd(channel.getName()));
	//TODO envoyer etat channel
}
