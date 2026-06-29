/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:46:20 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/04 17:43:33 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <string>

//colors - extern declarations
extern std::string red;
extern std::string green;
extern std::string yellow;
extern std::string blue;
extern std::string purple;
extern std::string reset;

#define RPL_WELCOME				001
#define RPL_YOURHOST			002
#define RPL_CREATED				003
#define RPL_MYINFO				004

#define RPL_UMODEIS				221
#define RPL_WHOISUSER			311
#define RPL_WHOISSERVER			312
#define RPL_ENDOFWHOIS			318
#define RPL_NOTOPIC				331
#define RPL_TOPIC				332

#define RPL_NAMREPLY			353
#define RPL_ENDOFNAMES			366

#define RPL_MOTDSTART			375
#define RPL_MOTD				372
#define RPL_ENDOFMOTD			376

#define ERR_NOSUCHNICK			401
#define ERR_USERNOTINCHANNEL	441
#define ERR_NOTONCHANNEL		442
#define ERR_NEEDMOREPARAMS		461
#define ERR_ALREADYREGISTERED	462
#define ERR_PASSWDMISMATCH 		464

#define ERR_NICKNAMEINUSE 		433
#define ERR_ERRONEUSNICKNAME 	432
#define	ERR_NONICKNAMEGIVEN 	431

#define ERR_NOSUCHCHANNEL		403
#define ERR_INVITEONLYCHAN		473
#define ERR_CHANNELISFULL		471
#define ERR_BANNEDFROMCHAN		474
#define ERR_BADCHANNELKEY		475
#define ERR_BADCHANMASK			476
#define ERR_TOOMANYCHANNELS		405
#define ERR_NOTONCHANNEL		442
#define ERR_USERONCHANNEL		443

#define ERR_UNKNOWNMODE			472
#define ERR_CHANOPRIVSNEEDED	482
#define ERR_UNIQOPPRIVSNEEDED	485
#define ERR_USERSDONTMATCH		502

#endif

