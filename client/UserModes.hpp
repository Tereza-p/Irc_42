//
// Created by jazema on 4/4/26.
//

#ifndef USERMODES_HPP
#define USERMODES_HPP

#include <vector>
#include <string>

class UserModes
{
	public:
		enum UserMode
		{
			U_AWAY,
			U_INVISIBLE,
			U_OPERATOR,
			U_UNKNOWN,
		};
	private:
		std::vector<UserMode> _modes;
	public:
		UserModes();

		bool hasMode(UserMode mode);
		void addMode(UserMode mode);
		void removeMode(UserMode mode);

		std::string toString();
};

#endif
