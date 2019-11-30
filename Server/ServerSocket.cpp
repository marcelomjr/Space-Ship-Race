/* 
Sources:
	-> https://github.com/EAxxx/EA872/tree/master/examples/sockets
	-> https://www.geeksforgeeks.org/socket-programming-cc/
	-> Ubuntu's man page
*/

#include "ServerSocket.hpp"
#include <stdio.h>


/*
	Find a free connection position and put the new connection
	Return true if found it or false if all the positions are busy.
*/
bool ServerSocket::add_connection(int connection_fd) {

	for (int i = 0; i < MAX_CONNECTIONS; i++) {
		if (this->is_free_connection[i]) {
			this->is_free_connection[i] = false;
			this->connections_fd[i] = connection_fd;

			// Add this player in the model
			this->system_control->new_player_connected(i);

			return true;
		}
	}
	return false;
}

// TODO: Test this
void ServerSocket::remove_connection(int position) {
	// Check if there is really an active connection in this position
	if (!this->is_free_connection[position]) {
		this->is_free_connection[position] = true;
		close(this->connections_fd[position]);

		// Remove this player from the model
		this->system_control->player_desconnected(position);

		//cout << "Connection " << position << "was removed" << endl;
	}
}

// Run a loop waiting for new connections
void ServerSocket::wait_for_connections() {

	 // size of my_address
	socklen_t addrlen = (socklen_t) sizeof(this->my_address);

	while(this->system_control->is_running()) {
		
		//cout << "waiting connection" << endl;
		// Waits for the next connection request in the queue of pending connections
		int connection_fd = accept(this->server_socket_fd, (struct sockaddr *) &this->my_address, &addrlen);
		//cout << "after connection" << endl;


		if (connection_fd == -1) {
			cout << "Accept failed! Error number:" << errno << endl;
		} 
		else if (!add_connection(connection_fd)) {
			cout << "New connection denied! Exceeded the number of connections!" << endl;
		}
		
	}
	cout << "End this->wait_for_connections" << endl;
}

//TODO: Need to test the interfaces if it are passing reference and not value.
void ServerSocket::init(System_Control_Interface* system_control, Input_Handler_Interface* input_handler) {

	// Set the interfaces
	this->system_control = system_control;
	this->input_handler = input_handler;
	this->output_buffer_size = 10000;


	// Set all the connection positions as free
	for (int i = 0; i < MAX_CONNECTIONS; i++) {
		this->is_free_connection[i] = true;
	}

	// It creates a new socket
	this->server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Verify new socket
	if (this->server_socket_fd == -1) {
		cout << "Socket failed" << endl;
		cout << "Error number:" << errno << endl;
		return;
	}
	
	//address family
	this->my_address.sin_family = AF_INET;

	/* The htons function converts the unsigned short integer hostshort 
	from host byte order to network byte order.
	*/
	this->my_address.sin_port = htons(PORT);	// port in network byte order

	/* It converts the Internet host address cp from the IPv4 numbers-and-dots notation into binary 
	form (in network byte order) and stores it in the structure that inp points to */
	inet_aton(ADDRESS, &(this->my_address.sin_addr));

	bool is_bonded = false;
	// It binds the socket to the address and port number
	while (!is_bonded) {
		if (bind(this->server_socket_fd, (struct sockaddr *) &this->my_address, sizeof(sockaddr_in)) == -1 ) {
			cout << "Bind failed! [errno: " << errno;
			cout << "]. Wait while we try again." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		else {
			is_bonded = true;
			cout << "Bonded with success!" << endl;
		}
	}

	/* listen() marks the socket referred to by this->server_socket_fd as a passive socket, 
	   that is, as a socket that will be used to accept incoming connection requests using accept(). */
	if (listen(this->server_socket_fd, 2) == -1) {
		cout << "Listen failed" << endl;
		cout << "Error number:" << errno << endl;
		return;
	}

}

/*	This function starts the thread of creation of connections and start
	the loop thread to receive and send data
*/
void ServerSocket::start() {

	if (!(this->system_control->is_running())){
		return;
	}

	// Creates a new thread for receiving new connections
	std::thread connection_creator(&ServerSocket::wait_for_connections, this);

	// Save the thread reference before return from this function
	this->connection_creator_thread.swap(connection_creator);


	// Creates a new thread for receiving and sending messages from/to clients
	std::thread loop_thread (&ServerSocket::server_loop, this);

	// Save the thread reference before return from this function
	this->server_loop_thread.swap(loop_thread);

	
	return;
}
void ServerSocket::server_loop() {

	char in_buffer[BUFFER_SIZE]; 
	int msglen;

	while(this->system_control->is_running()) {
		
		// Pass for all connections checking if they sent something.
		for (int connection = 0; connection < MAX_CONNECTIONS; connection++) {

			// Checks it only if there is an active connection in this position
			if (!this->is_free_connection[connection]) {

				/*	recv() is used to receive messages from a socket. 
				 	Flag MSG_DONTWAIT: The function doesn't block the execution
					recv returns:
						1) Number of bytes received.
						2) -1 if some error ocurred.
						3) 0 if the connection is closed
				*/
				msglen = recv(this->connections_fd[connection], &in_buffer, BUFFER_SIZE, MSG_DONTWAIT);


				for (int i = 0; i < MAX_CONNECTIONS; i++) {
					cout << "[" << this->is_free_connection[i] << "] ";
				}


				/*	recv change errno to EAGAIN when no message is received, and it is ok, 
					but if errno != EAGAIN, there is actual problem.
				*/
				if (msglen == -1 && errno != EAGAIN) {
					cout << "Client " << connection << ": " << "recv failed! errno:" << errno << endl;
					remove_connection(connection);
				}
				
				else if (msglen > 0) {
					// Sends to appropriate interface to handle with the message.
					this->input_handler->receiving_handler(connection, in_buffer);
				}

				/*
				it sends the updated model to player.
				*/

				// Get the updated model
				string output_buffer = this->system_control->get_the_updated_model(connection);

				// Get the buffer size (JSON + '\0')
				int buffer_size = output_buffer.length()+1;

				// It Converts the std::string to a c string
				char * output_buffer_c = new char [buffer_size];
  				std::strcpy (output_buffer_c, output_buffer.c_str());

  				//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				
				cout << "Sent buffer size: " << buffer_size << endl;
				//printf("(%s)\n", output_buffer_c);
				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

				if (buffer_size > 0) {

					// send return the number of sent characteres or -1 in case of error
					int status = send(this->connections_fd[connection], output_buffer_c, buffer_size, MSG_NOSIGNAL);

   						if (status == -1) {
      						cout << "Client " << connection << ": " << "send failed! errno:" << errno << endl;
							remove_connection(connection);

    				}
				}



				std::this_thread::sleep_for(std::chrono::milliseconds(25));
			}
		}

	}

	return;

}
// TODO: Improve the ending threads processes
void ServerSocket::stop() {

	// Remove all connections before end the program
	for (int pos = 0; pos < MAX_CONNECTIONS; pos++) {
		remove_connection(pos);
	}

	cout << "I'll wait for the thread end" << endl;
	
	// Waits for both threads
	//this->connection_creator_thread.join();
	cout << "thread ended" << endl;

	close(this->server_socket_fd);
}

