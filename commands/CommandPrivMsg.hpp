//
// Created by jazema on 01/04/2026.
//

#ifndef COMMANDPRIVMSG_HPP
#define COMMANDPRIVMSG_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandPrivMsg : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
