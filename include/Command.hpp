#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "User.hpp"
#include <iostream>
#include <vector>

enum	Command  
{
	NICK,
	USER,
	CAP,
	JOIN,
	PRIVMSG
};

void	command_cap(std::string buffer, std::vector<std::string> out);
void	command_nick(std::string buffer, std::vector<std::string> out, User *user);
void	command_user(std::string buffer, std::vector<std::string> out, User *user);
void	command_join(std::string buffer, std::vector<std::string> out, User *user);
void	command_privmsg(std::string buffer, std::vector<std::string> out, User *user);

#endif