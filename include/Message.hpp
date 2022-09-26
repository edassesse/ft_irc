#ifndef MESSAGE_HPP
#define MESSAGE_HPP

# include <iostream>
# include <string>

class	Message
{
	public:

		Message();
		~Message();

	private:

		std::string		_sender;
		std::string		_receiver;
};

#endif