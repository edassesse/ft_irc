#include "../include/Server.hpp"

void	Command::command_cap(std::vector<std::string> out)
{
	std::cout << "command CAP" << std::endl;
}

void	Command::command_nick(std::vector<std::string> out, User *user, Server *server)
{
	std::string		old_nick;
	std::cout << "command Nick" << std::endl;
	old_nick = user->get_nickname();
	if (check_nickname(out[1], server))
	{
		user->set_nickname(out[1]);
		if (user->wlcm_send == true)
			user->answer = ":" + old_nick + "!" + user->get_name() + "@server NICK " + user->get_nickname() + ENDLINE;
	}
	else
	{
		user->answer = ":server 433 " + out[1] + ":Nickname is already in use" + ENDLINE;
	}
	//ajouter si quelqu'un a deja le nickname
}

bool	check_nickname(std::string nickname, Server *server)
{
	for (std::vector<User>::iterator it = server->_users->begin(); it != server->_users->end(); it++)
		if (it->get_nickname() == nickname)
			return (false);
	return (true);
}

void	Command::command_user(std::vector<std::string> out, Server *server, User *user)
{
	std::cout << "command User" << std::endl;
	user->set_name(out[1]);
}

