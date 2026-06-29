/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandKick.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:41:22 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/04 17:17:53 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_KICK_HPP
#define COMMAND_KICK_HPP

#include <string>

#include "ICommandExecutor.hpp"

#include "../../incl/Server.hpp"
#include "../../incl/Client.hpp"
#include "../../incl/MsgBuilder.hpp"
#include "../../incl/Irc.hpp"



class CommandKick : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
