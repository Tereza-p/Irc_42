/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandInvite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:14:25 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/04 18:45:04 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandInvite.hpp"

//INVITE <nick> <chan>
void	CommandInvite::execute(Server &server, Client &client, std::vector<std::string> &args) const
{

	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (args.size() < 2)
	{
		client.sendMessage(msgBuilder.errNeedMoreParams("INVITE"));
		return ;
	}
	std::string &target_name = args[0];
	std::string &channel_name = args[1];

	//check if channel exist -> else 403 nosuchchannel
	if (server.getServerData().existsChannel(channel_name))
	{
		client.sendMessage(msgBuilder.errNoSuchChannel(channel_name));
		return ;
	}

	Channel &channel = server.getServerData().getChannel(channel_name);

	//check if client is channel's member -> else 442 notonchannel
	if (channel.isMember(client.getClientFd()))
	{
		client.sendMessage(msgBuilder.errNotOnChan(channel_name));
		return ;
	}

	//check if channel is in invite mode
	if (channel.hasInvitationMode() && !channel.isOp(client.getClientFd()))
	{
		client.sendMessage(msgBuilder.errChanOpNeeded(channel_name));
		return ;
	}

	//check if target exist else 401 nosuchnick
	if (!server.existsClient(target_name))
	{
		client.sendMessage(msgBuilder.errNoSuchNick(target_name));
		return ;
	}
	Client &target = server.getClientByNickname(target_name);
	//check if target is channel's member else 443 useronchannel
	if (channel.isMember(target.getClientFd()))
	{
		client.sendMessage(msgBuilder.userOnChan(target_name, channel_name));
		return ;
	}
	//add target to channel
	channel.addMember(target.getClientFd());

	//send invite msg (target)
	target.sendMessage(msgBuilder.format(341, channel_name + " " + target_name));
	//send confirm msg (client)
	//RPL_INVITING
	client.sendMessage(msgBuilder.format(341, channel_name + " " + target_name));



}
