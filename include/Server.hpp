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

void						split(std::string const &str, const char* delim, std::vector<std::string> &out);
std::vector<std::string>	split_vector(std::string s, std::string delimiter);
void						dispatch_cmd(std::string buffer, User *user);

#endif