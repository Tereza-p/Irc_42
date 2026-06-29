//
// Created by jazema on 4/4/26.
//

#ifndef COMMANDTOPIC_HPP
#define COMMANDTOPIC_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandTopic : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
