#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Irc.hpp"

class	User;

class	Channel
{
	public:

		Channel();
		Channel(User *creator, std::string name);
		~Channel();
		std::string				get_name();
		std::string				get_topic();
		void					set_name(std::string name);
		void					set_topic(std::string topic);
		std::vector<User>		*_users;

	private:

		std::string				_name;
		User					*_operator;
		std::string				_topic;
};

#endif
