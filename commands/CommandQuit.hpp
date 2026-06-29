//
// Created by jazema on 4/4/26.
//

#ifndef COMMANDQUIT_HPP
#define COMMANDQUIT_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandQuit : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
