//
// Created by jazema on 01/04/2026.
//

#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include <map>
#include <string>

#include "ICommandExecutor.hpp"

class CommandManager
{
	private:
		std::map<std::string, ICommandExecutor *> _commands;
	public:
		~CommandManager();

		template <typename T>
		void registerCommand(const std::string &commandName)
		{
			if (this->_commands.find(commandName) != this->_commands.end())
				return;
			this->_commands.insert(std::make_pair(commandName, new T()));
		}

		ICommandExecutor *getCommandExecutor(const std::string &commandName);
};

#endif
