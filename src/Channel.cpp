#include "../include/Channel.hpp"

Channel::Channel(void) : _topic("")
{
	std::cout << "Constructor Channel by default called" << std::endl;
}

Channel::Channel(User *creator, std::string name) : _topic("")
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

void					Channel::set_name(std::string name)
{
	_name = name;
}

std::string				Channel::get_name()
{
	return (_name);
}

void					Channel::set_topic(std::string topic)
{
	_topic = topic;
}

std::string				Channel::get_topic()
{
	return (_topic);
}

void					Channel::set_topic_user(std::string topic_user)
{
	_topic_user = topic_user;
}

std::string				Channel::get_topic_user()
{
	return (_topic_user);
}

void					Channel::set_topic_time(std::string topic_time)
{
	_topic_time = topic_time;
}

std::string				Channel::get_topic_time()
{
	return (_topic_time);
}