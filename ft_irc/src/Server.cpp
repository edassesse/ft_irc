#include "../include/Irc.hpp"

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
	server->_sockAddress.sin_family = AF_INET;
	server->_sockAddress.sin_addr.s_addr = INADDR_ANY;
	server->_sockAddress.sin_port = htons(server->_port);
	return;
}

void	Server::addSd(int socket, int events)
{
	struct pollfd	add;

	add.fd = socket;
	add.events = events;
	this->_clientSd.push_back(add);
}

void	Server::startServer(Server *server)
{
	int	opt = 1;

	if ((server->_masterSocket = socket(PF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cerr << "socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (setsockopt(server->_masterSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt))
	{
		std::cerr << "setsockopt failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (bind(server->_masterSocket, reinterpret_cast<struct sockaddr *>(&server->_sockAddress), sizeof(server->_sockAddress)) < 0)
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
	server->_users = new std::vector<User>;
	server->_channels = new std::vector<Channel>;
	server->_clientFd.push_back(server->_masterSocket);
	server->addSd(server->_masterSocket, POLLIN);
	server->set_address("127.0.0.1");
}

void	Server::newUser(Server *server, int newSocket)
{
	User	*user = new User();

	server->_clientAmount++;
	server->_users->push_back(*user);
	server->_clientFd.push_back(newSocket);
	server->addSd(newSocket, (POLLIN | POLLOUT)); /* MIGHT CHANGE */
}

void	Server::run(Server *server)
{
	struct	sockaddr	newClient;
	socklen_t			addrSize;
	int					events;
	int					newSocket;
	int					valread;
	int					newCo;
	char				buffer[1024];
	char				c = 0;

	while (TRUE)
	{
		newCo = 0;
		events = 0;
		events = poll(server->_clientSd.data(), server->_clientAmount, -1);
		if (server->_clientSd[0].revents == POLLIN)
		{
			addrSize = sizeof(newClient);
			newSocket = accept(server->_masterSocket, &newClient, &addrSize);
			std::cout << "New Connection: " << newSocket << std::endl;
			server->newUser(server, newSocket);
			std::cout << "PLS rentre pas ||||||" << std::endl;
			newCo = 1;
		}
		for (int i = 1; i < server->_clientAmount && events; i++)
		{
			if (newCo || server->_clientSd[i].revents)
			{
				valread = 0;
				while (read(server->_clientFd[i], &c, 1) > 0 && c != EOF && c != '\n')
				{
					buffer[valread] = c;
					valread++;
				}
				std::cout << "|||" << c << std::endl;
				if (valread == 0)
					std::cerr << "User disconnected" << std::endl; // a changer je sais 
				else
				{
					buffer[valread] = 0;
					std::cout << "Client " << server->_clientFd[i] << " sent:" << buffer << std::endl;
					dispatch_cmd(buffer,server, server->_users[i - 1].data());
				}
				if (server->_users[i - 1].data()->answer != "")
				{
					std::string answer = server->_users[i - 1].data()->answer + ENDLINE;
					std::cout << answer.c_str() << std::endl;
					send(server->_clientFd[i], answer.c_str(), answer.length(), 0);
					server->_users[i - 1].data()->answer = "";
				}
				events--;
			}
		}
	}
}
