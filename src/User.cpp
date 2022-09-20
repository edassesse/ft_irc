#include "../include/User.hpp"

User::User(void)
{
	std::cout << "Constructor User by default called" << std::endl;
} 

User::~User(void)
{
	std::cout << "Destructor User called" << std::endl;
}

std::string		User::get_nickname()
{
	return (_nickname);
}

std::string		User::get_name()
{
	return (_name);
}

std::string		User::get_password()
{
	return (_password);
}

void			User::set_nickname(std::string nickname)
{
	if (_nickname != nickname)
		_nickname = nickname;
}

void			User::set_name(std::string name)
{
	if (_name != name)
		_name = name;
}

void			User::set_password(std::string password)
{
	if (_password != password)
		_password = password;
}