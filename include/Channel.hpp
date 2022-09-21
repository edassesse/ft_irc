#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>
# include "User.hpp"

class	Channel
{
	public:

		Channel();
		Channel(User *creator);
		~Channel();

	private:

		std::string				_name;
		
		std::string				_operator_nickname;
		std::vector<User>		*_users;
};

#endif