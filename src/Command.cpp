#include "../include/Server.hpp"

void	dispatch_cmd(std::string buffer, User *user, Server *server)
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
			user->answer = "";
			break;
		case NICK :
			std::cout << "Nick switch" << std::endl;
			command_nick(buffer, out, user);
			user->answer = "";
			break;
		case USER :
			std::cout << "User switch" << std::endl;
			command_user(buffer, out, user);
			user->answer = ""; 
			break;
		case JOIN :
			std::cout << "Join switch" << std::endl;
			command_join(buffer, out, user, server);
			break;
		case PRIVMSG :
			std::cout << "Privmsg switch" << std::endl;
			command_privmsg(buffer, out, user);
			user->answer = "";
			break;
		default :
			std::cout << "Unknow command" << std::endl;
	}
	if (user->get_name().size() != 0 && !user->wlcm_send)
	{
		user->answer = ":server 001 " + user->get_nickname() + " :Welcome to the Internet Relay Network " + user->get_nickname() + "!" + user->get_name() + "@" + server->get_address();
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

void	command_join(std::string buffer, std::vector<std::string> out, User *user, Server *server)
{
	std::cout << "command Join" << std::endl;
	Channel		*channel;
	std::string	channel_name;

	if (out[1][0] == '#')
	{
		channel_name = out[1].erase(0, 1);
		if ((channel = find_channel(server, out)) == NULL)
		{
			//creer le channel correspondant
			std::cout << "Push Back Channel car existe pas" << std::endl;
			if (!user->_channels)
				user->_channels = new std::vector<Channel>;
			channel = new Channel(user, channel_name);
			if (!server->_channels)
				server->_channels = new std::vector<Channel>;
			user->_channels->push_back(*channel);
			server->_channels->push_back(*channel);
			//user->answer = out[0] + " " + out[1];
			user->answer = user->get_nickname() + "!" + user->get_nickname() + "@irc.example.com JOIN #" + channel->get_name();
		}
		else
		{
			//join le channel qui existe deja avec channel
		}
	}
	else
	{
		user->answer = out[1] + " No such channel" + ENDLINE;
	}
}

void	command_privmsg(std::string buffer, std::vector<std::string> out, User *user)
{
	std::cout << "command Privmsg" << std::endl;
}

Channel	*find_channel(Server *server, std::vector<std::string> out)
{
	std::cout << "Find channel" << std::endl;
	std::cout << "out 1 = " << out[1] << std::endl;
	if (!server->_channels)
		return (NULL);
	// for (std::vector<Channel>::iterator it = server->_channels.begin(); it != server->_channels.end(); ++it)
	//     if ()
	std::cout << "FIN" <<std::endl;
}