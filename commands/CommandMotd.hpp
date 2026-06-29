//
// Created by jazema on 4/4/26.
//

#ifndef COMMANDMOTD_HPP
#define COMMANDMOTD_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandMotd : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
