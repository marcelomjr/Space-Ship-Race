#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/types.h>  // Constants
#include <sys/socket.h>	// socket, bind, listen
#include <iostream>		
#include <errno.h> 		// errno
#include <arpa/inet.h> 	// htons
#include <netinet/in.h>
#include <thread> 
#include <unistd.h> // closes

#include "../Interfaces.hpp"

#define PORT 3001
#define ADDRESS "127.0.0.1"
#define BUFFER_SIZE 1
#define MAX_CONNECTIONS 3


using namespace std;

class ServerSocket
{
private:
	int connections_fd[MAX_CONNECTIONS];
	bool is_free_connection[MAX_CONNECTIONS];

	int server_socket_fd;
	struct sockaddr_in my_address;

	/* Interface with ServerManager to check if the game still running 
	and a channel to stop the game in case of something gets wrong. */
	System_Control_Interface* system_control;

	/* Interface to send a buffer received by the socket to the ServerManager */
	Input_Handler_Interface* input_handler;

	// Thread to run the operations of receiving and send data to the clients
	thread server_loop_thread;

	// This thread will keep wait for new connections
	thread connection_creator_thread;

	// Private functions
	void server_loop();
	void wait_for_connections();
	bool add_connection(int connection_fd);
	void remove_connection(int position);


public:
	void init(System_Control_Interface* system_control, Input_Handler_Interface* input_handler);
	
	// Start to receive and send data
	void start();
	
	// Stops the flow of data and ends the threads
	void stop();
	
};

#endif