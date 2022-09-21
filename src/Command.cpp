#include "../include/Server.hpp"

void	dispatch_cmd(std::string buffer, User *user)
{
    std::vector<std::string>	out;
	std::string					cmd_name[5] = {"NICK", "USER", "CAP", "JOIN", "PRIVMSG"};
	int							i;

	out = split_vector(buffer, " \r\n");
	std::cout << "Commande Split :" << std::endl;
	for (std::vector<std::string>::iterator it = out.begin(); it != out.end(); ++it)
		std::cout << "|" << *it << "|" << std::endl;
	for (i = 0; i < 5; i++)
	{
		if (cmd_name[i] == out[0])
			break ;
	}
	switch (i)
	{
		case CAP :
			std::cout << "Cap switch" << std::endl;
			command_cap(buffer, out);
			user->answer = CAP;
			break;
		case NICK :
			std::cout << "Nick switch" << std::endl;
			command_nick(buffer, out, user);
			user->answer = NICK;
			break;
		case USER :
			std::cout << "User switch" << std::endl;
			command_user(buffer, out, user);
			user->answer = USER; 
			break;
		case JOIN :
			std::cout << "Join switch" << std::endl;
			command_join(buffer, out, user);
			user->answer = JOIN;
			break;
		case PRIVMSG :
			std::cout << "Privmsg switch" << std::endl;
			command_privmsg(buffer, out, user);
			user->answer = PRIVMSG;
			break;
		default :
			std::cout << "Unknow command" << std::endl;
	}
	if (user->get_name().size() != 0 && !user->wlcm_send)
	{
		user->answer = ":irc.example.com 001 " + user->get_nickname() + " : Welcome to the Internet Relay Network " + user->get_nickname() + "!" + user->get_nickname() + "@irc.example.com" + ENDLINE;
		user->wlcm_send = 1;
	}
}

void	command_cap(std::string buffer, std::vector<std::string> out)
{
	std::cout << "command CAP" << std::endl;
}

void	command_nick(std::string buffer, std::vector<std::string> out, User *user)
{
	std::cout << "command Nick" << std::endl;
	//if (check_nickname() == 1)
		user->set_nickname(out[1]);
}

void	command_user(std::string buffer, std::vector<std::string> out, User *user)
{
	std::cout << "command User" << std::endl;
	user->set_name(out[1]);
}

void	command_join(std::string buffer, std::vector<std::string> out, User *user)
{
	std::cout << "command Join" << std::endl;
}

void	command_privmsg(std::string buffer, std::vector<std::string> out, User *user)
{
	std::cout << "command Privmsg" << std::endl;
}