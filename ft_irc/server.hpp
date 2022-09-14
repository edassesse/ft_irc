#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>

class	Server {

	public:

		/* CONSTRUCTOR  DESTRUCTOR */

		Server()					{};
		~Server()					{};
		
		 /* SETTER */

		void	setPw(std::string pw)		{_pw = pw;};
		void	setPort(int port)			{_port = port;};

		 /* GETTER */
		
		std::string	getPw()						{return _pw;};
		int			getPort()					{return _port;};

	private:

		std::string	_pw;
		int			_port;

};

#endif
