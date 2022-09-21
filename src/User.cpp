#include "../include/User.hpp"

User::User(void) : wlcm_send(0)
{
	std::cout << "Constructor User by default called" << std::endl;
}

User::User(User &cpy) : wlcm_send(0)
{
	*this = cpy;
}

User::~User(void)
{
	std::cout << "Destructor User called" << std::endl;
}

User	&User::operator=(User const &src)
{
	this->_name = src._name;
	this->_nickname = src._nickname;
	this->_password = src._password;
	this->answer = src.answer;
	this->wlcm_send = src.wlcm_send;
	return (*this);
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
	// std::cout << "Set NickName" << std::endl;
	if (_nickname != nickname)
		_nickname = nickname;
}

void			User::set_name(std::string name)
{
	// std::cout << "Set Name = |" << name << "|" << std::endl;
	if (_name != name)
		_name = name;
}

void			User::set_password(std::string password)
{
	// std::cout << "Set Password" << std::endl;
	if (_password != password)
		_password = password;
}