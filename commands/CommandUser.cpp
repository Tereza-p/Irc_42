//
// Created by jazema on 02/04/2026.
//

#include "CommandUser.hpp"
#include "../server/Server.hpp"

#include "../helpers/StringHelper.hpp"
#include "../Irc.hpp"

#include "../client/Client.hpp"
#include "../helpers/MsgBuilder.hpp"

void CommandUser::execute(Server &server, Client &client, std::vector<std::string> &args) const
{
	//<USER><MODE><UNUSED><REALNAME>
	MsgBuilder	msgBuilder(server.getServerData().getServerName(), client.getNickname());

	if (args.size() < 4)
	{
		client.sendMessage(msgBuilder.errNeedMoreParams("USER"));
		return;
	}
	if (client.isRegistered())
	{
		client.sendMessage(msgBuilder.errArlreadyRegistered());
		return;
	}
	if (!client.isPasswordValid())
	{
		client.sendMessage(msgBuilder.format(ERR_PASSWDMISMATCH, ":Password incorrect"));
		server.closeClient(client);
		return;
	}
	if (!client.isNickSet())
	{
		client.sendMessage(msgBuilder.format(451, ":You have not registered"));
		return;
	}
	std::string userName = args[0];

	//On va venir remplacer les caracteres interdits par des '_' //todo voir si cest necessaire ou si on refuse le mec
	StringHelper::replaceChars(userName, "@ \r\n", '_');

	client.setUsername(userName);
	client.setRealname(args[3]);
	client.userSet();
	client.sendMessage(msgBuilder.welcomeMsg(client.getUsername(), "localhost"));

	client.sendMessage(msgBuilder.hostMsg());
	client.sendMessage(msgBuilder.createMsg());
	client.sendMessage(msgBuilder.infoMsg());

	client.sendMessage(msgBuilder.motdStart());
	client.sendMessage(msgBuilder.motdMsg());
	client.sendMessage(msgBuilder.format(376, ":End of /MOTD command"));
}