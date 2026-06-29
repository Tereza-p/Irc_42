/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandInvite.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:14:33 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/04 18:17:57 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_INVITE_HPP
#define COMMAND_INVITE_HPP
#include <string>

#include "ICommandExecutor.hpp"
#include "../server/Server.hpp"
#include "../client/Client.hpp"
#include "../helpers/MsgBuilder.hpp"

class CommandInvite : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};



#endif
