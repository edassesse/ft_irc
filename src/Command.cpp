#include "../include/Command.hpp"
#include "../include/User.hpp"
 
void split(std::string const &str, const char* delim, std::vector<std::string> &out)
{
    char *token = strtok(const_cast<char*>(str.c_str()), delim);
    while (token != nullptr)
    {
        out.push_back(std::string(token));
        token = strtok(nullptr, delim);
    }
}

void	dispatch_cmd(std::string buffer)
{
    std::vector<std::string>	out;
    std::string					s = buffer;
	std::string					cmd_name[3] = {"NICK", "USER", "CAP"};
    const char*					delim = " ";
	int							i;
	User						*user;

    split(s, delim, out);
	std::cout << "Commande Split :" << std::endl;
	for (std::vector<std::string>::iterator it = out.begin(); it != out.end(); ++it)
		std::cout << *it << std::endl;
	for (i = 0; i < 2; i++)
	{
		if (cmd_name[i] == out[0])
			break ;
	}
	switch (i)
	{
		case CAP :
			std::cout << "Cap switch" << std::endl;
			user = command_cap(buffer, out);
			break;
		case NICK :
			std::cout << "Nick switch" << std::endl;
			command_nick(buffer, out);
			break;
		case USER :
			std::cout << "User switch" << std::endl;
			command_user(buffer, out);
			break;
		default :
			std::cout << "Unknow command" << std::endl;
	}
}

User	*command_cap(std::string buffer, std::vector<std::string> out)
{
	User	*user;

	return (user);
}

User	*command_nick(std::string buffer, std::vector<std::string> out, User *user)
{
	set_nickname(out[2]);
	return (user);
}

User	*command_user(std::string buffer, std::vector<std::string> out, User *user)
{
	set_name(out[2]);
	return (user);
}