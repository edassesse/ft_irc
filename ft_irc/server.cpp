#include "Irc.h"


void	Server::initServer(Server *server, int ac, char **av)
{ 
	std::string pw;
	std::string port;

	if (ac != 3)
	{
		std::cout << "Error: \"./ircserv <port> <password>\"" << std::endl;
		exit(0);
	}
	pw = av[2];
	port = av[1];
	if (!pw.length())
	{
		std::cout << "Error: Wrong password" << std::endl;
		exit(0);
	}
	for (int i = 0; port[i]; i++)
	{
		if (!isdigit(port[i]))
		{
			std::cerr << "Error: Wrong port" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	server->_pw = pw;
	server->_port = std::stod(port);
	server->_address.sin_family = AF_INET;
	server->_address.sin_addr.s_addr = INADDR_ANY;
	server->_address.sin_port = htons(server->_port);
	return;
}

void	Server::startServer(Server *server)
{
	int	opt = 1;

	if ((server->_masterSocket = socket(PF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cerr << "socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (bind(server->_masterSocket, reinterpret_cast<struct sockaddr *>(&server->_address), sizeof(server->_address)) < 0)
	{
		std::cerr << "bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (listen(server->getMasterSocket(), 3) < 0)
	{
		std::cerr << "listen failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	server->_addrlen = sizeof(server->_address);
	std::cout << "Waiting for connections ... " << std::endl;
	if (setsockopt(server->_masterSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt))
	{
		std::cerr << "setsockopt failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Server::run(Server *server)
{
	struct	sockaddr	*newClient;
	int					events;
	while (TRUE)
	{
		events = 0;
		/* new_socket = accept(server->_masterSocket, newClient, sizeof server->_address); */
		accept(server->_masterSocket, newClient, sizeof server->_address);
		events = poll(VECTOR OF USERS, AMOUNT OF USERS, -1);
	}
}
