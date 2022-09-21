#include "../include/Channel.hpp"

Channel::Channel(void)
{
	std::cout << "Constructor Channel by default called" << std::endl;
}

Channel::Channel(User *creator, std::string name)
{
	std::cout << "Constructor Channel by default called" << std::endl;
	_operator = creator;
	_name = name;
	_users = new std::vector<User>;
	_users->push_back(*creator);
}

Channel::~Channel(void)
{
	std::cout << "Destructor Channel called" << std::endl;
}

std::string				Channel::get_name()
{
	return (_name);
}

std::string				Channel::get_topic()
{
	return (_topic);
}

void					Channel::set_name(std::string name)
{
	_name = name;
}

void					Channel::set_topic(std::string topic)
{
	_topic = topic;
}