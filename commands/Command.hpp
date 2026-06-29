/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nardis <nardis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:11:13 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/03 12:50:53 by nardis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

#include "../Irc.hpp"

class Command
{
	public:
		Command(const std::string &command);

		std::string              cmd;
		std::vector<std::string> params;

		void		printCmd(Command &cmd);
};


