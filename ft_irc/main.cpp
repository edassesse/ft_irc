#include "server.hpp"
#include "Irc.h"

int main(int ac, char **av)
{
	Server	*server = new Server();

	checkParams(server, ac, av);
}
