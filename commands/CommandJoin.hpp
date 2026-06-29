//
// Created by jazema on 02/04/2026.
//

#ifndef COMMANDJOIN_HPP
#define COMMANDJOIN_HPP

#include <string>

#include "ICommandExecutor.hpp"

class CommandJoin : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
