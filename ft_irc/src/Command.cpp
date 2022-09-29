#include "../include/Server.hpp"

void	dispatch_cmd(std::string buffer, Server *server, User *user)
{
	std::vector<std::string>	out;
	std::string					cmd_name[7] = {"NICK", "USER", "CAP", "JOIN", "PRIVMSG", "PART", "TOPIC"};
	int							i;
	Command						command;

	out = split_vector(buffer, " \r\n");
	/* print_infos(server); */
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
			user->answer = "";
			break;
		case NICK :
			std::cout << "Nick switch" << std::endl;
			command.command_nick(out, user, server);
			break;
		case USER :
			std::cout << "User switch" << std::endl;
			command.command_user(out, server, user);
			user->answer = ""; 
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
		user->answer = ":server 001 " + user->get_nickname() + " :Welcome to the Internet Relay Network " + user->get_nickname() + "!" + user->get_name() + "@" + server->get_address();
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
			std::cout << "\taddr = " << &it << std::endl;
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
			std::cout << "\t" << it->get_nickname() << std::endl;
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

void	Command::command_cap(std::vector<std::string> out)
{
	std::cout << "command CAP" << std::endl;
}

void	Command::change_topic(std::string topic, std::string user, Channel *channel)
{
	char			time_test[300];
	time_t timestamp = time( NULL );
    struct tm * pTime = localtime( & timestamp );
	strftime(time_test, 300, "%a, %d %h %G %T", pTime);
	std::string		time_string(time_test);
	channel->set_topic(topic);
	channel->set_topic_user(user);
	channel->set_topic_time(time_string);
}

void	Command::command_topic(std::vector<std::string> out, User *user, Server *server)
{
	std::cout << "command TOPIC" << std::endl;
	Channel		*channel;
	std::string	channel_name;

	if (out[1][0] == '#')
	{
		channel_name = out[1].erase(0, 1);
		if ((channel = find_channel(server, out, channel_name)) == NULL)
			user->answer = out[1] + " No such channel" + ENDLINE;
		else
		{
			if (out.size() <= 2)
			{
				if (channel->get_topic() == "")
					user->answer = ":server 331 " +  user->get_name() + " #" + channel->get_name() + " :No topic is set";
				else
					user->answer = ":server 332 " +  user->get_name() + " #" + channel->get_name() + " :" + channel->get_topic() + ENDLINE + ":server 333 " +  user->get_name() + " #" + channel->get_name() + " " + channel->get_topic_user() + " " + channel->get_topic_time();
			}
			else if (out[2][0] != ':')
				user->answer = "ERR_NEEDMOREPARAMS";
			else
			{
				change_topic(out[2].erase(0, 1), user->get_name(), channel);
				user->answer = ":server 332 " +  user->get_name() + " #" + channel->get_name() + " :" + channel->get_topic();
			}
		}
	}
	else
	{
		user->answer = out[1] + " No such channel" + ENDLINE;
	}
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
			user->answer = ":" + old_nick + "!" + user->get_name() + "@server NICK " + user->get_nickname();
	}
	else
	{
		user->answer = ":server 433 " + out[1] + ":Nickname is already in use";
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

void	Command::command_join(std::vector<std::string> out, User *user, Server *server)
{
	std::cout << "command Join" << std::endl;
	Channel		*channel;
	std::string	channel_name;

	if (out[1][0] == '#')
	{
		channel_name = out[1].erase(0, 1);
		if ((channel = find_channel(server, out, channel_name)) == NULL)
		{
			//creer le channel si il existe pas correspondant
			channel = new Channel(user, channel_name);
			std::cout << &channel << std::endl;
			std::cout << channel << std::endl;
			//add channel in server
			std::cout << "push back name = " << channel->get_name() << std::endl;
			server->_channels->push_back(*channel);
			std::cout << "1" << std::endl;
			// print_infos(server);
		}
		std::cout << "2" << std::endl;
		add_channel_in_user(channel, user);
		std::cout << "3" << std::endl;
		user->answer = ":" + user->get_nickname() + "!" + user->get_nickname() + "@server JOIN #" + channel->get_name();
	}
	else
	{
		user->answer = out[1] + " No such channel" + ENDLINE;
	}
	std::cout << "4" << std::endl;
}

void	add_channel_in_user(Channel *channel, User *user)
{
	//add channel in user
	user->_channels->push_back(*channel);
	user->set_nb_channel(user->get_nb_channel() + 1);
}

void	Command::send_msg_to_channel_users(std::string msg, User *user, Channel *channel)
{
	for (std::vector<User>::iterator it = channel->_users->begin(); it != channel->_users->end(); it++)
	{
		//envoyer le message si l'user n'est pas en mode off ??
		std::cout << "message Send to User :" << it->get_name() << std::endl;
		it->answer = ":" + user->get_nickname() + "!" + user->get_name() + "@server PRIVMSG #" + channel->get_name() + " " + msg;
		std::cout << it->answer << std::endl;
	}
}

void	Command::command_privmsg(std::vector<std::string> out, User *user, Server *server)
{
	std::cout << "command Privmsg" << std::endl;
	Channel		*channel;
	std::string	channel_name;

	//envoie d'un message
	// user->answer = ":" + user->get_nickname() + "!" + user->get_name() + "@server PRIVMSG #coucou :bonjour a tous";
	//channel case
	if (out[1][0] == '#')
	{
		channel_name = out[1].erase(0, 1);
		if ((channel = find_channel(server, out, channel_name)) == NULL)
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

Channel	*find_channel(Server *server, std::vector<std::string> out, std::string channel_name)
{
	size_t		size;
	// size_t		i;

	if (!server->_channels)
		return (NULL);
	size = server->_channels->size();
	std::cout << "find channel size = " << size << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "find channel i = " << i << std::endl;
		std::cout << "find channel name = " << server->_channels->at(i).get_name() << std::endl;
		if (channel_name == server->_channels->at(i).get_name())
			return (&server->_channels->at(i));
	}
	return (NULL);
}

void	delete_channel(Channel *channel, Server *server)
{
	std::cout << "delete channel" << std::endl;

	for (size_t i = 0; i < server->_channels->size(); i++)
	{
		if (channel->get_name() == server->_channels->at(i).get_name())
		{
			// std::cout << "channel name : " << server->_channels->at(i).get_name() << std::endl;
			server->_channels->erase(server->_channels->begin() + i);
			break ;
		}
	}
	// std::cout << "channel name delete : " << channel->get_name() << std::endl;
	// delete channel;
}

void	remove_user_of_channel(Channel *channel, User *user, Server *server)
{
	int		i = 0;
	//supprimer le channel dans user
	for (std::vector<Channel>::iterator ite = user->_channels->begin(); ite != user->_channels->end(); ite++, i++)
		if (ite->get_name() == channel->get_name())
			break ;
	user->_channels->erase(user->_channels->begin() + i);
	//supprimer le user dans channel
	i = 0;
	for (std::vector<User>::iterator ite = channel->_users->begin(); ite != channel->_users->end(); ite++, i++)
		if (ite->get_name() == user->get_name())
			break ;
	channel->_users->erase(channel->_users->begin() + i);
	//supprimer le channel si 0 users
	if (channel->_users->empty())
		delete_channel(channel, server);
}

void	Command::command_part(std::vector<std::string> out, User *user, Server *server)
{
	std::cout << "command Part" << std::endl;
	Channel		*channel;
	std::string	channel_name;

	if (out[1][0] == '#')
	{
		channel_name = out[1].erase(0, 1);
		if ((channel = find_channel(server, out, channel_name)) == NULL)
		{
			//Le channel n'existe pas => Pas de message d'erreurs ?
			std::cout << "No Channel found" << std::endl;
			user->answer = out[1] + " No such channel" + ENDLINE;
		}
		else
		{
			//quit le channel qui existe deja
			remove_user_of_channel(channel, user, server);
			user->answer = ":" + user->get_nickname() + "!" + user->get_name() + "@server PART #" + channel->get_name();
			std::cout << "send = " << user->answer << std::endl;
		}
	}
	else
	{
		user->answer = out[1] + " No such channel" + ENDLINE;
	}
}
