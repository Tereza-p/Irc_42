/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nardis <nardis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:14:56 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/03 12:07:39 by nardis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"
#include "Command.hpp"

#include <iomanip>
#include <sstream>

#include "../helpers/StringHelper.hpp"

void	Command::printCmd(Command	&cmd)
{
	int	i = 1;

	std::cerr << red << std::string(30, '-') << yellow << std::endl;
	StringHelper::printCentered(cmd.cmd, 30, ' ');

	for (std::vector<std::string>::iterator it = cmd.params.begin(); it != cmd.params.end(); ++it)
	{
		std::cerr << reset << std::string(30, '-') << std::endl;
		std::cerr << std::setw(14) << std::left << "param " << i;
		std::cerr << "->";
		std::cerr << std::setw(14) << std::right << (*it) << std::endl;
		i++;
	}
	std::cerr << red << std::string(30, '-') << reset << std::endl;
	std::cerr << std::endl;
}

Command::Command(const std::string &command)
{
	std::string line = command;
	std::string trailing;
	size_t pos;

	pos = line.find(" :");
	if (pos != std::string::npos)
	{
		trailing = line.substr(pos + 2);
		line = line.substr(0, pos);
	}

	std::istringstream iss(line);
	std::string token;

	if (!(iss >> cmd))
		return;

	while (iss >> token)
	{
		params.push_back(token);
	}

	if (!trailing.empty())
		params.push_back(trailing);
	printCmd(*this);
}
