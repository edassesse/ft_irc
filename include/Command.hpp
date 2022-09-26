#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "User.hpp"
#include <iostream>
#include <vector>

class Server;

enum	Command_lst
{
	NICK,
	USER,
	CAP,
	JOIN,
	PRIVMSG,
	PART
};

class Command
{
	public:

			Command();
			~Command();
	void	command_cap(std::vector<std::string> out);
	void	command_nick(std::vector<std::string> out, User *user, Server *server);
	void	command_user(std::vector<std::string> out, Server *server);
	void	command_join(std::vector<std::string> out, User *user, Server *server);
	void	command_privmsg(std::vector<std::string> out, User *user);
	void	command_part(std::vector<std::string> out, User *user, Server *server);
};


#include "Server.hpp"

#endif