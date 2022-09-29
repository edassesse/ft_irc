#include "../include/Server.hpp"

void	dispatch_cmd(std::string buffer, Server *server, User *user)
{
	std::vector<std::string>	out;
	std::string					cmd_name[7] = {"NICK", "USER", "CAP", "JOIN", "PRIVMSG", "PART", "TOPIC"};
	int							i;
	Command						command;

	out = split_vector(buffer, " \r\n,");
	print_infos(server);
	std::cout << "Commande Split :" << std::endl;
	for (std::vector<std::string>::iterator it = out.begin(); it != out.end(); ++it)
		std::cout << "|" << *it << "|" << std::endl;
	for (i = 0; i < 7; i++)
	{
		if (cmd_name[i] == out[0])
			break ;
	}
	switch (i)
	{
		case CAP :
			std::cout << "Cap switch" << std::endl;
			command.command_cap(out);
			user->answer = ENDLINE;
			break;
		case NICK :
			std::cout << "Nick switch" << std::endl;
			command.command_nick(out, user, server);
			break;
		case USER :
			std::cout << "User switch" << std::endl;
			command.command_user(out, server, user);
			user->answer = ENDLINE; 
			break;
		case JOIN :
			std::cout << "Join switch" << std::endl;
			command.command_join(out, user, server);
			break;
		case PRIVMSG :
			std::cout << "Privmsg switch" << std::endl;
			command.command_privmsg(out, user, server);
			break;
		case PART :
			std::cout << "Part switch" << std::endl;
			command.command_part(out, user, server);
			break;
		case TOPIC :
			std::cout << "Topic switch" << std::endl;
			command.command_topic(out, user, server);
			break;
		default :
			std::cout << "Unknow command" << std::endl;
	}
	if (user->get_name().size() != 0 && !user->wlcm_send)
	{
		user->answer = ":server 001 " + user->get_nickname() + " :Welcome to the Internet Relay Network " + user->get_nickname() + "!" + user->get_name() + "@" + server->get_address() + ENDLINE;
		user->wlcm_send = 1;
	}
	print_infos(server);
}

Command::Command(void)
{
	std::cout << "Constructor Command by default called" << std::endl;
}

Command::~Command(void)
{
	std::cout << "Destructor Command called" << std::endl;
}

void	print_infos(Server *server)
{
	std::cout << "\n-------Print Data-------" << std::endl;
	std::cout << "Channels" << std::endl;
	if (server->_channels->size() != 0)
	{
		for (std::vector<Channel>::iterator it = server->_channels->begin(); it != server->_channels->end(); it++)
		{
			std::cout << "\t" << it->get_name() << std::endl;
			std::cout << "\tOperator is : " << it->get_operator()->get_name() << std::endl;
			if (!server->_channels->data()->_users->empty())
			{
				std::cout << "\t\tUser in channel" << std::endl;
				for (std::vector<User>::iterator it = server->_channels->data()->_users->begin(); it != server->_channels->data()->_users->end(); it++)
					std::cout << "\t\t\t" << it->get_name() << std::endl;
			}
		}
	}
	else
		std::cout << "\tNo Channels" << std::endl;
	std::cout << "Users" << std::endl;
	if (server->_users)
	{
		for (std::vector<User>::iterator it = server->_users->begin(); it != server->_users->end(); it++)
		{
			std::cout << "\t" << it->get_name() << std::endl;
			if (it->get_nb_channel() != 0)
			{
				std::cout << "\t\tChannel in user" << std::endl;
				for (std::vector<Channel>::iterator ite = it->_channels->begin(); ite != it->_channels->end(); ite++)
					std::cout << "\t\t\t" << ite->get_name() << std::endl;
			}
		}
	}
	std::cout << "-------End Print-------\n" << std::endl;
}

void	Command::send_msg_to_channel_users(std::string msg, User *user, Channel *channel)
{
	for (std::vector<User>::iterator it = channel->_users->begin(); it != channel->_users->end(); it++)
	{
		//envoyer le message si l'user n'est pas en mode off ??
		std::cout << "message Send to User :" << it->get_name() << std::endl;
		it->answer = ":" + user->get_nickname() + "!" + user->get_name() + "@server PRIVMSG #" + channel->get_name() + " " + msg + ENDLINE;
		std::cout << it->answer << std::endl;
	}
}

void	Command::command_privmsg(std::vector<std::string> out, User *user, Server *server)
{
	std::cout << "command Privmsg" << std::endl;
	Channel		*channel;
	std::string	channel_name;

	//channel case
	if (out[1][0] == '#')
	{
		channel_name = out[1].erase(0, 1);
		if ((channel = find_channel(server, channel_name)) == NULL)
		{
			//Le channel n'existe pas
			user->answer = out[1] + " No such channel" + ENDLINE;
		}
		else
		{
			send_msg_to_channel_users(out[2], user, channel);
		}
	}
	//user case
	else
	{
		user->answer = out[1] + " No such channel" + ENDLINE;
	}
}

Channel	*find_channel(Server *server, std::string channel_name)
{
	size_t		size;
	// size_t		i;

	if (!server->_channels)
		return (NULL);
	size = server->_channels->size();
	// std::cout << "find channel size = " << size << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		// std::cout << "find channel i = " << i << std::endl;
		// std::cout << "find channel name = " << server->_channels->at(i).get_name() << std::endl;
		if (channel_name == server->_channels->at(i).get_name())
			return (&server->_channels->at(i));
	}
	return (NULL);
}
