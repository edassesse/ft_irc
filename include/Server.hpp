#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <vector>
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include "Command.hpp"
#include "User.hpp"
#include "Channel.hpp"

#define ENDLINE "\r\n"

class Server
{
   public:

		Server();
		~Server();
		std::vector<Channel>	*_channels;
		std::vector<User>   	*_users;
		std::string				get_address();
		void					set_address(std::string addr);
		User					*init_data(Server *server);

	private :

		std::string				_address;
};

std::vector<std::string>	split_vector(std::string s, std::string delimiter);
void						dispatch_cmd(std::string buffer, Server *server);
Channel						*find_channel(Server *server, std::vector<std::string> out, std::string channel_name);
void						add_channel_in_user(Channel *channel, User *user);
bool						check_nickname(std::string nickname, Server *server);
void						print_infos(Server *server, User *user);

#endif