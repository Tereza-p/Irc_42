//
// Created by jazema on 01/04/2026.
//

#include "CommandManager.hpp"
#include "Irc.hpp"

CommandManager::~CommandManager()
{
	std::map<std::string, ICommandExecutor *>::iterator it;

	it = this->_commands.begin();
	while (it != this->_commands.end())
	{
		delete (it->second);
		++it;
	}
}

ICommandExecutor *CommandManager::getCommandExecutor(const std::string &commandName)
{
	std::map<std::string, ICommandExecutor*>::iterator it;

	it = this->_commands.find(commandName);
	if (it == this->_commands.end())
		return (NULL);
	return (it->second);
}
