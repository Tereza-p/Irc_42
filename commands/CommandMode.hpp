//
// Created by jazema on 01/04/2026.
//

#ifndef COMMANDMODE_HPP
#define COMMANDMODE_HPP
#include <string>

#include "ICommandExecutor.hpp"
#include "../client/UserModes.hpp"

class CommandMode : public ICommandExecutor
{
	private:
		enum ChannelModeParameter
		{
			C_INVITE_ONLY,
			C_TOPIC_RESTRICTIONS,
			C_KEY,
			C_OPERATOR_PRIVILEGES,
			C_LIMIT,
			C_UNKNOWN,
		};
		ChannelModeParameter	parseChannelModeParameter(char c) const;
		UserModes::UserMode		parseUserModeParameter(char c) const;
	public:
		void execute(Server &server, Client &client, std::vector<std::string> &args) const;
};

#endif
