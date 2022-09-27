#include "Server.hpp"
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

void	Server::addSd(int socket, int events)
{
	struct pollfd	add;

	add.fd = socket;
	add.events = events;
	this->_clientSd->push_back(add);
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
	server->_clientFd = new std::vector<int>;
	server->_clientFd->push_back(server->_masterSocket);
	server->_clientSd = new std::vector<struct pollfd>;
	server->addSd(server->_masterSocket, POLLIN | POLLOUT);
}

void	Server::newUser(Server *server, int newSocket)
{
	User	*user = new User;

	server->_user->push_back(*user);
	server->_clientFd->push_back(newSocket);
	server->addSd(newSocket, POLLIN | POLLOUT); /* MIGHT CHANGE */
}

void	Server::run(Server *server)
{
	struct	sockaddr	*newClient;
	int					events;
	int					newSocket;
	int					valread;
	char				buffer[1024];
	char				c = 0;

	while (TRUE)
	{
		events = 0;
		events = poll(server->_clientSd->data(), server->_clientAmount, -1);
		for (int i = 0; i < server->_clientAmount && events; i++)
		{
			if (server->_clientSd[i].data()->revents)
			{
				if (server->_clientSd[i].data()->fd == server->_masterSocket)
				{
					newSocket = accept(server->_masterSocket, newClient, (socklen_t *)sizeof server->_address);
					server->newUser(server, newSocket);
				}
				else
				{
					valread = 0;
					while (read(*server->_clientFd[i].data(), &c, 1) > 0 && c != EOF && c != '\n')
					{
						buffer[valread] = c;
						valread++;
					}
					if (valread == 0)
						std::cerr << "User disconnected" << std::endl; // a changer je sais 
					else
					{
						buffer[valread] = 0;
						std::cout << "Client " << server->_clientFd[i].data() << " sent:" << buffer << std::endl;
						dispatch_cmd(buffer,server);
					}
				}
				for (int j = 0; j < server->_clientAmount; j++)
				{
					if (server->_user[i]->answer != "")
					{
						std::string answer = server->_user[i]->answer + "\r\n";
						send(*server->_clientFd[i].data(), answer.c_str(), answer.length(), 0);
						server->_user[i]->answer = "";
					}
				}
				events--;
			}
		}
	}
}
