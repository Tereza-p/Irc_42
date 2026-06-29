/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:40:29 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/04 18:01:33 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandKick.hpp"
#include <string>

//<channel> *(", <channel>") <user> * (<user>) [<comment>]
void	CommandKick::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (args.size() < 2)
	{
		client.sendMessage(msgBuilder.errNeedMoreParams("KICK"));
		return ;
	}

	std::string	&channel_name = args[0];
	std::string	&target_name = args[1];
	//If a "comment" is given, this will be sent instead of the default message, the nickname of the user issuing the KICK.
	std::string comment = client.getNickname();

	if (args.size() == 3)
		comment = args[2];

	//check if channel exist -> 403 if not
	if (!server.getServerData().existsChannel(channel_name))
	{
		client.sendMessage(msgBuilder.errNoSuchChannel(channel_name));
		return ;
	}

	Channel &channel =  server.getServerData().getChannel(channel_name);

	//check if client is in canal -> 442 if not
	if (!channel.isMember(client.getClientFd()))
	{
		client.sendMessage(msgBuilder.errNotOnChan(channel_name));
		return ;
	}

	// check if client is op -> 485 if not
	if (!channel.isOp(client.getClientFd()))
	{
		client.sendMessage(msgBuilder.errNotOp(channel_name));
		return ;
	}

	//SI ON SE DECO ON ENLEVE DU CHANNEL ?
	//look for target in connected client -> 401 if not
	if (!server.existsClient(target_name))
	{
		client.sendMessage(msgBuilder.errNoSuchNick(target_name));
		return ;
	}

	Client &target = server.getClientByNickname(target_name);

	//check if target is channel member -> 441 if not
	if (!channel.isMember(target.getClientFd()))
	{
		client.sendMessage(msgBuilder.errUserNotOnChan(target_name, channel_name));
		return ;
	}

	//notify all channel members that the client is kicked
	server.broadcast(channel, msgBuilder.kickMsg(client.getNickname(), channel_name, target_name, comment));

	//remove the target
	channel.removeMember(target.getClientFd());

	//if channel is empty -> delete channel
	if (channel.isEmpty())
		server.getServerData().deleteChannel(channel_name);
}
