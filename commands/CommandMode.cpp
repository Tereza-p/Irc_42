//
// Created by jazema on 01/04/2026.
//

#include "CommandMode.hpp"

#include <cstdlib>

#include "Irc.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../helpers/MsgBuilder.hpp"
#include "../helpers/StringHelper.hpp"

CommandMode::ChannelModeParameter CommandMode::parseChannelModeParameter(char c) const
{
	switch (c)
	{
		case 'i':
			return (C_INVITE_ONLY);
		case 't':
			return (C_TOPIC_RESTRICTIONS);
		case 'k':
			return (C_KEY);
		case 'o':
			return (C_OPERATOR_PRIVILEGES);
		case 'l':
			return (C_LIMIT);
	}
	return (C_UNKNOWN);
}

UserModes::UserMode CommandMode::parseUserModeParameter(char c) const
{
	switch (c)
	{
		case 'a':
			return UserModes::U_AWAY;
		case 'i':
			return UserModes::U_INVISIBLE;
		case 'o':
			return UserModes::U_OPERATOR;
	}
	return (UserModes::U_UNKNOWN);
}

void CommandMode::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (args.size() == 0)
	{
		client.sendMessage(msgBuilder.errNeedMoreParams("MODE"));
		return;
	}
	if (StringHelper::startsWith(args[0], "#")) // Sur un channel
	{
		if (args.size() == 1)
		{
			client.sendMessage(msgBuilder.errNeedMoreParams("MODE"));
			return;
		}
		if (!server.getServerData().existsChannel(args[0]))
		{
			client.sendMessage(msgBuilder.errNoSuchChannel(args[0]));
			return;
		}

		Channel &channel = server.getServerData().getChannels().at(args[0]);

		if (!channel.isOp(client.getClientFd()))
		{
			client.sendMessage(msgBuilder.format(ERR_CHANOPRIVSNEEDED, channel.getName() + " :You're not channel operator"));
			return;
		}

		bool add = true;
		size_t currentParamArg = 2;

		for (size_t i = 0 ; i < args[1].size() ; i++)
		{
			if (args[1].at(i) == '-')
			{
				add = false;
				continue;
			}
			if (args[1].at(i) == '+')
			{
				add = true;
				continue;
			}
			const ChannelModeParameter &param = parseChannelModeParameter(args[1][i]);

			if (param == C_UNKNOWN)
			{
				client.sendMessage(msgBuilder.format(ERR_UNKNOWNMODE, ": " + args[1].substr(i, 1) + " :is unknown mode char to me for " + channel.getName()));
				continue;
			}
			if (param == C_LIMIT)
			{
				if (add && args.size() <= currentParamArg)
				{
					client.sendMessage(msgBuilder.errNeedMoreParams("MODE"));
					continue;
				}
				if (add)
				{
					channel.setLimit(std::atol(args[currentParamArg].c_str()));
					currentParamArg++;
					continue;
				}
				channel.removeLimit();
			}
			if (param == C_TOPIC_RESTRICTIONS)
			{
				channel.setTopicRestriction(add);
				continue;
			}
			if (param == C_OPERATOR_PRIVILEGES)
			{
				if (args.size() <= currentParamArg)
				{
					client.sendMessage(msgBuilder.errNeedMoreParams("MODE"));
					continue;
				}
				if (!server.existsClient(args[currentParamArg]) || !channel.isMember(server.getClientByNickname(args[currentParamArg]).getClientFd()))
				{
					// ERR_USERONCHANNEL
					client.sendMessage(msgBuilder.format(441, args[currentParamArg] + " " + args[0] + " :They aren't on that channel"));
					continue;
				}
				if (add)
				{
					channel.addOp(server.getClientByNickname(args[currentParamArg]).getClientFd());
					continue;
				}
				channel.removeOp(server.getClientByNickname(args[currentParamArg]).getClientFd());
				continue;
			}
			if (param == C_INVITE_ONLY)
			{
				channel.setInvitationMode(add);
				continue;
			}
			if (param == C_KEY)
			{
				if (add && args.size() <= currentParamArg)
				{
					client.sendMessage(msgBuilder.errNeedMoreParams("MODE"));
					continue;
				}
				if (add && channel.hasPassword())
				{
					// ERR_KEYSET
					client.sendMessage(msgBuilder.format(467, channel.getName() + " :Channel key already set"));
					return;
				}
				if (add)
				{
					channel.setPassword(args[currentParamArg]);
					currentParamArg++;
					continue;
				}
				channel.removePassword();
			}
		}
		server.broadcast(channel, ":" + client.buildPrefix() + " MODE " + channel.getName() + " " + StringHelper::join(std::vector<std::string>(args.begin() + 1, args.end()), " "));
		return;
	}
	// Sur un user
	if (args[0] != client.getNickname())
	{
		// ERR_USERSDONTMATCH
		client.sendMessage(msgBuilder.format(ERR_USERSDONTMATCH, ":Cannot change mode for other users"));
		return;
	}
	if (args.size() == 1)
	{
		client.sendMessage(msgBuilder.format(RPL_UMODEIS, client.getModes().toString()));
		return;
	}
	bool add = args[1][0] != '-';
	for (size_t i = 1 ; i < args[1].size() ; i++)
	{
		const UserModes::UserMode &param = parseUserModeParameter(args[1][i]);
		if (param == UserModes::U_UNKNOWN)
		{
			// ERR_UNKNOWNMODE
			client.sendMessage(msgBuilder.format(501, ": " + args[1].substr(i, 1) + " :Unknown MODE flag"));
			continue;
		}
		std::cout << args[1][i]  << " " << param << std::endl;
		if (add)
			client.getModes().addMode(param);
		else
			client.getModes().removeMode(param);
	}
	client.sendMessage(":" + client.buildPrefix() + " MODE " + client.getNickname() + " " + args[1]); //todo remplacer par la suite args[1] par les vrais modes
}

