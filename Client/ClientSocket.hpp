#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <errno.h>
#include <cstring>
#include "../Interfaces.hpp"

#define IN_BUFFER_SZ 20000
#define ADDRESS "127.0.0.1"


class ClientSocket {

private:
	int socket_fd;

	struct sockaddr_in target;

	Input_Handler_Interface* input_handler;
	GameManagerInterface* game_manager;

	std::thread receiving_loop_thread;

public:
	void init(GameManagerInterface* game_manager, Input_Handler_Interface* input_handler);
	void start();
	void stop();
	void send_message(std::string message);
	void update_client();
	void receiving_loop();


};

#endif