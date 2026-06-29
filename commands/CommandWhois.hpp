//
// Created by jazema on 03/04/2026.
//

#ifndef COMMANDWHOIS_HPP
#define COMMANDWHOIS_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandWhois : public ICommandExecutor
{
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
