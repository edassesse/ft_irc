#ifndef USER_HPP
#define USER_HPP

# include <iostream>
# include <string>
# include <vector>
# include "Channel.hpp"

class	User
{
	public:

		User();
		User(User &cpy);
		~User();
		User	&operator=(User const &src);
		std::string		get_nickname();
		std::string		get_name();
		std::string		get_password();
		void			set_nickname(std::string nickname);
		void			set_name(std::string name);
		void			set_password(std::string password);
		bool			wlcm_send;
		std::string		answer;

	private:

		std::string				_nickname;
		std::string				_name;
		std::string				_password;
		std::vector<int>		*_operator;
		std::vector<Channel>	*_channels;
};

#endif