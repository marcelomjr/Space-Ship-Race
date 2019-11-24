#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include <string>

class System_Control_Interface
{
public:
	virtual bool is_running() = 0;
	//virtual void stop_game();
	
};
class Input_Handler_Interface
{
public:
	virtual void receiving_handler(std::string buffer) = 0;
	
};

#endif