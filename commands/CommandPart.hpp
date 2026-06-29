//
// Created by jazema on 4/4/26.
//

#ifndef COMMANDPART_HPP
#define COMMANDPART_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandPart : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
