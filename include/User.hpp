#ifndef USER_HPP
#define USER_HPP

# include <iostream>
# include <string>

class	User
{
	public:

		User();
		~User();

	private:

		std::string		_nickname;
		std::string		_name;
		std::string		_password;
};

#endif