#include "../include/Server.hpp"

#define TRUE   1 
#define FALSE  0 
#define PORT 8888 

Server::Server(void)
{
	std::cout << "Constructor Server by default called" << std::endl;
}

Server::~Server(void)
{
	std::cout << "Destructor Server called" << std::endl;
}

void		Server::set_address(std::string addr)
{
	_address = addr;
}

std::string		Server::get_address()
{
	return (_address);
}		

int		main(int argc , char *argv[])
{
	int		opt = TRUE;  
	int		master_socket , addrlen , new_socket , client_socket[30] , 	max_clients = 30 , activity, i , valread , sd;  
	int		max_sd;
	struct sockaddr_in address;
	User	*user = new User();
	Server	*server = new Server();
	char buffer[1025];
	fd_set readfds;
	// char *message = ":bar.example.com 001 amy : Welcome to the Internet Relay Network amy!amy@foo.example.com\r\n";
	for (i = 0; i < max_clients; i++)  
		client_socket[i] = 0;  
	if((master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
	{  
		perror("socket failed");  
		exit(EXIT_FAILURE);  
	}
	if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
	{  
		perror("bind failed");  
		exit(EXIT_FAILURE);  
	}  
	std::cout << "Listener on port " << PORT << std::endl;
	if (listen(master_socket, 3) < 0)  
	{  
		perror("listen");  
		exit(EXIT_FAILURE);  
	}
	user = server->init_data(server);
	addrlen = sizeof(address);
	puts("Waiting for connections ...");  
	std::cout << "DEBUT BOUCLE WHILE TRUE" << std::endl;
	while(TRUE)  
	{
		FD_ZERO(&readfds);
		FD_SET(master_socket, &readfds);  
		max_sd = master_socket;
		for ( i = 0 ; i < max_clients ; i++)  
		{
			sd = client_socket[i];
			if(sd > 0)  
				FD_SET( sd , &readfds);
			if(sd > max_sd)  
				max_sd = sd;  
		}
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
		if ((activity < 0) && (errno!=EINTR))  
				std::cout << "Select ERROR" << std::endl;
		if (FD_ISSET(master_socket, &readfds))  
		{  
			if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
			{  
				perror("accept");  
				exit(EXIT_FAILURE);  
			}  
			//inform user of socket number - used in send and receive commands 
			std::cout << "New connection , socket fd is " << new_socket << " , ip is : " << inet_ntoa(address.sin_addr) << " , port : " << ntohs(address.sin_port) << std::endl;
			//send new connection greeting message 
			// if( send(new_socket, message, strlen(message), 0) != strlen(message) )  
			// 	perror("send");
			for (i = 0; i < max_clients; i++)
			{
				//if position is empty 
				if( client_socket[i] == 0 )
				{
					client_socket[i] = new_socket;
					break;
				}
			}
		}
		//else its some IO operation on some other socket
		for (i = 0; i < max_clients; i++)  
		{
			sd = client_socket[i];
			if (FD_ISSET( sd , &readfds))
			{
				char c;
				valread = 0;
				while (read(sd, &c, 1) > 0 && c != EOF && c != '\n')
				{
					buffer[valread] = c;
					valread++;
				}
				if (valread == 0)
				{
					getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
					std::cout << "Host disconnected , ip " << inet_ntoa(address.sin_addr) << " , port " << ntohs(address.sin_port) << std::endl;
					close(sd);
					client_socket[i] = 0;
				}
				else
				{
					buffer[valread] = '\0';
					std::cout << "\t recu = " << buffer << std::endl;
					std::string	mess;
					server->set_address(inet_ntoa(address.sin_addr));
					dispatch_cmd(buffer, server);
					user = server->_users->data();
					std::cout << "\tSend = |" << user->answer.c_str() << "|" << std::endl;
					// std::cout << "\tSend = |" << message << "|" << std::endl;
					if (user->answer != "")
						send(sd , (user->answer + "\r\n").c_str() , (user->answer + "\r\n").length() , 0);
					user->answer = "";
				}
			}
		}
	}
	return 0;
}  

User	*Server::init_data(Server *server)
{
	std::cout << "Init server" << std::endl;
	server->_users = new std::vector<User>;
	server->_channels = new std::vector<Channel>;
	User		*user = new User;
	server->_users->push_back(*user);
	std::cout << "Fin Init server" << std::endl;
}