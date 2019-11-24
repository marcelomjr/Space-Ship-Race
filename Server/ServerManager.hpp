#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <iostream>
#include "Model.hpp"
#include "ServerSocket.hpp"
#include "../Interfaces.hpp"


class ServerManager: public System_Control_Interface, public Input_Handler_Interface
{
public:
	void start();
	bool is_running();
	void receiving_handler(string buffer);
	
};

#endif