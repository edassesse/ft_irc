#ifndef USER_HPP
#define USER_HPP

# include <iostream>
# include <string>
# include <map>

class	User : public std::map<int, std::string>
{
	public:

		User();
		~User();
		std::string		get_nickname();
		std::string		get_name();
		std::string		get_password();
		void			set_nickname(std::string nickname);
		void			set_name(std::string name);
		void			set_password(std::string password);

	private:

		std::string		_nickname;
		std::string		_name;
		std::string		_password;
};

#endif