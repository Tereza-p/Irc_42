/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsgBuilder.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:50:29 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/04 18:38:24 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSGBUILDER_HPP
#define MSGBUILDER_HPP

class Client;

class MsgBuilder
{
private:
	const std::string _server_name;
	const std::string _nick;

public:
	MsgBuilder(const std::string& server_name, const std::string &nick);
	~MsgBuilder();

	std::string format(int code, const std::string &msg);

	std::string capMsg(const std::string &cap);
	std::string errPasswdMismatch();
	std::string errNeedMoreParams(const std::string& cmd);
	std::string errArlreadyRegistered();

	// Registration
	std::string welcomeMsg(const std::string &user, const std::string &host);
	std::string hostMsg();
	std::string createMsg();
	std::string infoMsg();

	// Message of the day
	std::string motdStart();
	std::string motdMsg();
	std::string motdEnd();

	std::string errNicknameInUse(const std::string &new_nick);
	std::string errErroneousNickname(const std::string &new_nick);
	std::string errNoNicknameGiven();
	std::string errNoSuchChannel(const std::string &name);
	std::string	errNoSuchNick(const std::string &name);


	// channel
	std::string joinMsg(Client &client, const std::string &channelName);
	std::string getTopic(const std::string &channel, const std::string &topic);
	std::string noTopic(const std::string &channel);
	std::string memberList(const std::string &channel_name, const std::string &names);
	std::string memberListEnd(const std::string &channel_name);
	std::string errNotOnChan(const std::string &channel_name);
	std::string errNotOp(const std::string &channel_name);
	std::string errUserNotOnChan(const std::string& nick, const std::string& channel_name);
	std::string errChanOpNeeded(const std::string& channel_name);
	std::string kickMsg(const std::string& nick, const std::string& channel_name, const std::string& target_name, const std::string& comment);
	std::string userOnChan(const std::string& user_name, const std::string &channel_name);

};

#endif
