//
// Created by jazema on 4/4/26.
//

#include "UserModes.hpp"

#include <algorithm>
#include <string>

UserModes::UserModes()
{
}

void UserModes::addMode(const UserMode mode)
{
	this->_modes.push_back(mode);
}

void UserModes::removeMode(const UserMode mode)
{
	std::remove(this->_modes.begin(), this->_modes.end(), mode);
}

bool UserModes::hasMode(const UserMode mode)
{
	return (std::find(this->_modes.begin(), this->_modes.end(), mode) != this->_modes.end());
}

std::string UserModes::toString()
{
	std::string result;

	for (std::vector<UserMode>::iterator it = this->_modes.begin(); it != this->_modes.end(); ++it)
	{
		switch (*it)
		{
			case U_AWAY:
				result += "a";
				continue;
			case U_INVISIBLE:
				result += "i";
				continue;
			case U_OPERATOR:
				result += "o";
				continue;
			case U_UNKNOWN:
				;
		}
	}
	return ('+' + result);
}
