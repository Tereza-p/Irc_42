//
// Created by jazema on 02/04/2026.
//

#ifndef COMMANDPASS_HPP
#define COMMANDPASS_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandPass : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
