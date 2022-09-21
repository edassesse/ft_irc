#include "../include/Channel.hpp"

Channel::Channel(void)
{
	std::cout << "Constructor Channel by default called" << std::endl;
}

Channel::Channel(User *creator)
{
	std::cout << "Constructor Channel by default called" << std::endl;
	_operator_nickname = creator->get_nickname();
	_users->push_back(*creator);
}

Channel::~Channel(void)
{
	std::cout << "Destructor Channel called" << std::endl;
}
