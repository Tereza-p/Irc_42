/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsgBuilder.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:53:25 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/05 15:13:12 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Irc.hpp"
#include "MsgBuilder.hpp"

#include <iomanip>
#include <sstream>

#include "../client/Client.hpp"

/* ************************************************************************** */
/*                            CONSTRUCTOR/DESTRUCTOR                          */
/* ************************************************************************** */

MsgBuilder::MsgBuilder(const std::string& server_name, const std::string &nick)
	: _server_name(server_name), _nick(nick)
{
	;
}

MsgBuilder::~MsgBuilder()
{
	;
}

/* ************************************************************************** */
/*                                   FORMAT                                   */
/* ************************************************************************** */

std::string MsgBuilder::format(int code, const std::string& msg)
{
	std::ostringstream str;

	str << ":" << _server_name << " ";
	str << std::setw(3) << std::setfill('0') << code << " ";
	str << _nick << " ";
	str << msg;
	return (str.str());
}

/* ************************************************************************** */
/*                                    RPL                                     */
/* ************************************************************************** */

/* 001 RPL_WELCOME */
std::string MsgBuilder::welcomeMsg(const std::string& user, const std::string &host)
{
	std::string str;

	str = ":Welcome to the Internet Relay Network " + _nick + "!" + user + "@" + host;
	return (format(RPL_WELCOME, str));
}

/* 002 RPL_YOURHOST */
std::string	MsgBuilder::hostMsg()
{
	std::string str;

	str = " :Your host is " + _server_name;
	return format(RPL_YOURHOST, str);
}

/* 003 RPL_CREATED */
std::string	MsgBuilder::createMsg()
{
	std::string str;

	str = " :This server was created now";
	return format(RPL_CREATED, str);
}

/* 004 RPL_MYINFO */
std::string	MsgBuilder::infoMsg()
{
	std::string str;

	str= " :" + _server_name + " 1.0 o o";
	return format(RPL_MYINFO, str);
}

/* 331 RPL_NOTOPIC */
std::string		MsgBuilder::noTopic(const std::string &channel)
{
	std::string str;

	str = channel + " :No topic is set";
	return format(RPL_NOTOPIC, str);
}

/* 332 RPL_TOPIC */
std::string 	MsgBuilder::getTopic(const std::string &channel, const std::string &topic)
{
	std::string str;

	str = channel + " :" + topic;
	return format(RPL_TOPIC, str);
}

/* 353 RPL_NAMREPLY */
std::string 	MsgBuilder::memberList(const std::string &channel_name, const std::string &names)
{
	std::string str;

	str = "= " + channel_name + " :" + names;
	return format(RPL_NAMREPLY, str);
}

/* 366 RPL_ENDOFNAMES */
std::string MsgBuilder::memberListEnd(const std::string& channel_name)
{
	std::string str;

	str = channel_name + " :End of /NAMES list";
	return format(RPL_ENDOFNAMES, str);
}

/* 372 RPL_MOTD */
std::string	MsgBuilder::motdMsg()
{
	std::string str;

	str = " :- Have a good day !";
	return format(RPL_MOTD, str);
}

/* 375 RPL_MOTDSTART */
std::string	MsgBuilder::motdStart()
{
	std::string str;

	str = " :- " + _server_name + " Message of the day";
	return format(RPL_MOTDSTART, str);
}

/* 376 RPL_ENDOFMOTD */
std::string	MsgBuilder::motdEnd()
{
	std::string str;

	str = " :End of /MOTD command";
	return format(RPL_ENDOFMOTD, str);
}

/* ************************************************************************** */
/*                                    ERR                                     */
/* ************************************************************************** */

/* 401 ERR_NOSUCHNICK */
std::string	MsgBuilder::errNoSuchNick(const std::string &name)
{
	std::string str;

	str = name + " :No such channel/channel";
	return format(ERR_NOSUCHNICK, str);
}

/* 403 ERR_NOSUCHCHANNEL */
std::string	MsgBuilder::errNoSuchChannel(const std::string &name)
{
	std::string str;

	str = name + " :No such channel";
	return format(ERR_NOSUCHCHANNEL, str);
}

/* 431 ERR_NONICKNAMEGIVEN */
std::string	MsgBuilder::errNoNicknameGiven()
{
	std::string	str;

	str = ":Erroneous nickname";
	return format(ERR_NONICKNAMEGIVEN, str);
}

/* 432 ERR_ERRONEUSNICKNAME */
std::string MsgBuilder::errErroneousNickname(const std::string &new_nick)
{
	std::string	str;

	str = _nick +  " " + new_nick + " :Erroneous nickname";
	return format(ERR_ERRONEUSNICKNAME, str);
}

/* 433 ERR_NICKNAMEINUSE */
std::string MsgBuilder::errNicknameInUse(const std::string &new_nick)
{
	std::string	str;

	str = _nick + " " + new_nick + " :Nickname is already in use";
	return format(ERR_NICKNAMEINUSE, str);
}

/* 441 ERR_USERNOTINCHANNEL */
std::string MsgBuilder::errUserNotOnChan(const std::string& nick, const std::string& channel_name)
{
	std::string str;

	str = nick + " " + channel_name + " :You're not on that channel";
	return format(ERR_USERNOTINCHANNEL, str);
}

/* 442 ERR_NOTONCHANNEL */
std::string MsgBuilder::errNotOnChan(const std::string& channel_name)
{
	std::string str;

	str = channel_name + " :You're not on that channel";
	return format(ERR_NOTONCHANNEL, str);
}

/* 443 ERR_USERONCHANNEL */
std::string MsgBuilder::userOnChan(const std::string& user_name, const std::string &channel_name)
{
	std::string str;

	str = user_name + channel_name + " :is already on channel";
	return format(ERR_USERONCHANNEL, str);
}

/* 461 ERR_NEEDMOREPARAMS */
std::string	MsgBuilder::errNeedMoreParams(const std::string& cmd)
{
	std::string str;

	str = cmd + ":Not enough parameters";
	return (format(ERR_NEEDMOREPARAMS, str));
}

/* 462 ERR_ALREADYREGISTERED */
std::string	MsgBuilder::errArlreadyRegistered()
{
	std::string 	str;

	str = ":Unauthorized command (already registered)";
	return (format(ERR_ALREADYREGISTERED, str));
}

/* 464 ERR_PASSWDMISMATCH */
std::string	MsgBuilder::errPasswdMismatch()
{
	std::string str;

	str = " :Password incorrect";
	return (format(ERR_PASSWDMISMATCH, str));
}

/* 482 ERR_CHANOPRIVSNEEDED */
std::string MsgBuilder::errChanOpNeeded(const std::string& channel_name)
{
	std::string str;

	str = channel_name + " :You're not channel operator";
	return format(ERR_CHANOPRIVSNEEDED, str);
}

/* 485 ERR_UNIQOPPRIVSNEEDED */
std::string MsgBuilder::errNotOp(const std::string& channel_name)
{
	std::string str;

	str = channel_name + " :You're not the original channel operator";
	return format(ERR_UNIQOPPRIVSNEEDED, str);
}

/* ************************************************************************** */
/*                               CMD RESPONSES                                */
/* ************************************************************************** */

/* CAP LS */
std::string	MsgBuilder::capMsg(const std::string& cap)
{
	std::ostringstream	str;

	str << ":" << _server_name << " CAP " << _nick << " LS :" << cap;
	return str.str();
}

/* JOIN */
std::string MsgBuilder::joinMsg(Client &client, const std::string &channelName)
{
	std::ostringstream str;

	str << client.getNickname() << client.getUsername() << client.getHostname() << " join server:" << channelName;
	return str.str();
}

/* KICK */
std::string MsgBuilder::kickMsg(const std::string& nick, const std::string& channel_name, const std::string& target_name, const std::string& comment)
{
	std::ostringstream str;

	str << ":" << nick << " KICK " << channel_name << " " << target_name << " :" << comment;
	return str.str();
}
