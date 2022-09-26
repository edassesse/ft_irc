#ifndef SERVER_HPP
# define SERVER_HPP

# include "Irc.h"

class	Server {

	public:

		/* CONSTRUCTOR  DESTRUCTOR */

		Server() : _clientAmount(0)				{};
		~Server()								{};
		
		 /* SETTER */

		void	setPw(std::string pw)			{_pw = pw;};
		void	setPort(int port)				{_port = port;};
		void	setMasterSocket(int i)			{_masterSocket = i;};
		void	setAddrlen(int len)				{_addrlen = len;};
		void	setMaxSd(int sd)				{_maxSd = sd;};

		 /* GETTER */
		
		std::string	getPw()						{return _pw;};
		int			getPort()					{return _port;};
		sockaddr_in	getAddress()				{return _address;};
		int			getMasterSocket()			{return _masterSocket;};
		int			getMaxSd()					{return _maxSd;};
		int			getClientAmount()			{return _clientAmount;};

		/* MEMBER FCTS */

		void	startServer(Server *server);
		void	initServer(Server *server, int ac, char **av);
		void	run(Server *server);

	private:

		std::string			_pw;
		int					_port;
		int					_masterSocket;
		struct	sockaddr_in	_address;
		int					_addrlen;
		int					_maxSd;
		int					_clientAmount;
		fd_set				_readfds;

};

#endif
