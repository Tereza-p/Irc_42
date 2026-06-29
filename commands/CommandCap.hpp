//
// Created by jazema on 02/04/2026.
//

#ifndef COMMANDCAP_HPP
#define COMMANDCAP_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandCap : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};



#endif
