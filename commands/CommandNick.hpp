//
// Created by jazema on 4/3/26.
//

#ifndef COMMANDNICK_HPP
#define COMMANDNICK_HPP
#include <string>

#include "ICommandExecutor.hpp"

class CommandNick : public ICommandExecutor
{
    public:
        void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
