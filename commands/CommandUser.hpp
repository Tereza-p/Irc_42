//
// Created by jazema on 02/04/2026.
//

#ifndef COMMANDUSER_HPP
#define COMMANDUSER_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandUser : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
