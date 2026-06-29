//
// Created by jazema on 4/3/26.
//

#include "CommandNick.hpp"

#include <iostream>
#include <map>

#include "../helpers/MsgBuilder.hpp"
#include "../server/Server.hpp"

static bool validNick(const std::string &nickname)
{
    std::string special = "[]\\`_^{}|";

    if (nickname.length() > 9)
        return false;
    if (!isalpha(static_cast<unsigned char>(nickname[0])) && special.find(nickname[0])== std::string::npos)
        return false;
    for(unsigned int i = 1; i <nickname.size(); ++i)
    {
        if(!isalnum(nickname[i]) && special.find(nickname[i])== std::string::npos && nickname[i] != '-')
            return false;
    }
    return true;
}

void CommandNick::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

    if (args.empty() || args[0].empty())
    {
        client.sendMessage(msgBuilder.errNoNicknameGiven());
        return ;
    }
    std::string nickname = args[0];

    if (!validNick(nickname))
    {
        client.sendMessage(msgBuilder.errErroneousNickname(nickname));
        return ;
    }
    for (std::map<int, Client>::iterator it = server.getClients().begin(); it != server.getClients().end(); it++)
    {
        if (it->first != client.getClientFd() && it->second.getNickname() == nickname)
        {
            client.sendMessage(msgBuilder.errNicknameInUse(nickname));
            return ;
        }
    }

	if (client.isRegistered())
		client.sendMessage(":" + client.buildPrefix() + " NICK :" + args[0]);
    client.nickSet();
    client.setNickname(nickname);
}
