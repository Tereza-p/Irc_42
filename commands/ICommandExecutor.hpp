//
// Created by jazema on 01/04/2026.
//

#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP
#include <vector>

class Server;
class Client;

class ICommandExecutor
{
	public:
		virtual      ~ICommandExecutor() {}
		virtual void execute(Server &server, Client &client, std::vector<std::string> &args) const = 0;
};

#endif
