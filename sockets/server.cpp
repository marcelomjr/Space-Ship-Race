/* 
Sources:
	-> https://github.com/EAxxx/EA872/tree/master/examples/sockets
	-> https://www.geeksforgeeks.org/socket-programming-cc/
	-> Ubuntu's man page
*/
#include <sys/types.h>  // Constants
#include <sys/socket.h>	// socket, bind, listen
#include <iostream>		
#include <errno.h> 		// errno
#include <arpa/inet.h> 	// htons
#include <netinet/in.h>
#include <pthread.h> // pthread_create
#include <unistd.h> // closes

#include "server.hpp"

#define PORT 3001
#define ADDRESS "127.0.0.1"
#define BUFFER_SIZE 1
#define MAX_CONNECTIONS 3

int connections_fd[MAX_CONNECTIONS];
bool free_connection[MAX_CONNECTIONS];
bool is_running;
int socket_fd;
struct sockaddr_in my_address;
socklen_t addrlen;

using namespace std;

/*
	Find a free connection position and put the new connection
	Return true if found it or false if all the positions are busy.
*/
bool add_connection(int connection_fd) {

	for (int i = 0; i < MAX_CONNECTIONS; i++) {
		if (free_connection[i]) {
			free_connection[i] = false;
			connections_fd[i] = connection_fd;
			return true;
		}
	}
	return false;
}

void remove_connection(int position) {
	// Check if there is really an active connection in this position
	if (!free_connection[position]) {
		free_connection[position] = true;
		close(connections_fd[position]);
		cout << "Connection " << position << "was removed" << endl;
	}
}

// Run a loop waiting for new connections
void* wait_connections(void* param) {

	while (is_running) {

		//cout << "waiting connection" << endl;
		// Waits for the next connection request in the queue of pending connections
		int connection_fd = accept(socket_fd, (struct sockaddr *) &my_address, &addrlen);

		if (connection_fd == -1) {
			cout << "Accept failed! Error number:" << errno << endl;
		} 
		else if (!add_connection(connection_fd)) {
			cout << "Error! Exceeded the number of connections!" << endl;
		}
	}
}

void* update_model_clients(void* param) {
	while(is_running) {
		// Pass for all connections checking if they sent something.
		for (int connection = 0; connection < MAX_CONNECTIONS; connection++) {
			// Check only if there is an active connection in this position
			if (!free_connection[connection]) {
	
				if (send(connections_fd[connection], "const void *buf", BUFFER_SIZE, MSG_NOSIGNAL) == -1) {
					cout << "Client " << connection << ": " << "send failed! Error number:" << errno << endl;
					remove_connection(connection);
				}
			}
		}
	}
}

void run_server(void* params) {

	Input_Interface* interface = (Input_Interface*) params;
	pthread_t connection_creator_thread;
	char in_buffer[BUFFER_SIZE]; 
	int msglen;

	addrlen = (socklen_t) sizeof(my_address);

	for (int i = 0; i < MAX_CONNECTIONS; i++) {
		free_connection[i] = true;
	}

	// It creates a new socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Verify new socket
	if (socket_fd == -1) {
		cout << "Socket failed" << endl;
		cout << "Error number:" << errno << endl;
		return;
	}
	
	//address family
	my_address.sin_family = AF_INET;

	/* The htons function converts the unsigned short integer hostshort 
	from host byte order to network byte order.
	*/
	my_address.sin_port	= htons(PORT);	// port in network byte order

	/* It converts the Internet host address cp from the IPv4 numbers-and-dots notation into binary 
	form (in network byte order) and stores it in the structure that inp points to */
	inet_aton(ADDRESS, &(my_address.sin_addr));


	// It binds the socket to the address and port number
	if (bind(socket_fd, (struct sockaddr *) &my_address, sizeof(sockaddr_in)) == -1 ) {
		cout << "Bind failed" << endl;
		cout << "Error number:" << errno << endl;
		return;
	}

	/* listen() marks the socket referred to by socket_fd as a passive socket, 
	   that is, as a socket that will be used to accept incoming connection requests using accept(). */
	if (listen(socket_fd, 2) == -1) {
		cout << "Listen failed" << endl;
		cout << "Error number:" << errno << endl;
		return;


	}
	// It allows receiving connections
	is_running = true;

	// Creates a new thread for receiving new connections	
	if (pthread_create(&connection_creator_thread, NULL, wait_connections, NULL) != 0) {
		cout << "Error in connection_creator_thread creation" << endl;
	}
	

	while(is_running) {
		// Pass for all connections checking if they sent something.
		for (int connection = 0; connection < MAX_CONNECTIONS; connection++) {
			// Check only if there is an active connection in this position
			if (!free_connection[connection]) {

				// recv() is used to receive messages from a socket. 
				// Don't wait until receive a menssage
				msglen = recv(connections_fd[connection], &in_buffer, BUFFER_SIZE, MSG_DONTWAIT);
		
				// recv change errno to EAGAIN when no message is received.
				if (msglen == -1 && errno != EAGAIN) {
					cout << "Client " << connection << ": " << "recv failed! errno:" << errno << endl;
					remove_connection(connection);
				}
				
				else if (msglen > 0) {
					//cout << "Client " << connection << ": "<< in_buffer  << endl;
					interface->key = in_buffer[0];
					interface->was_read = false;
				}
			}
		}
	}

	// Remove all connections before end the program
	for (int pos = 0; pos < MAX_CONNECTIONS; pos++) {
		remove_connection(pos);
	}

	pthread_join(connection_creator_thread, NULL);

	return;
}

