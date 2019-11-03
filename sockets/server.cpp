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


#define PORT 3001
#define ADDRESS "127.0.0.1"
#define BUFFER_SIZE 10


using namespace std;

void server_connection(int connection_fd) {
	

}
void server_setup() {

	int socket_fd, connection_fd;
	struct sockaddr_in my_address;
	socklen_t addrlen = (socklen_t) sizeof(my_address);

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
	cout << "I'm waiting for a connection" << endl;
	/*
	It extracts the first connection request on the queue of pending connections for the listening socket,
	socket_fd, creates a new connected socket, and returns a new file descriptor referring to that socket.
	*/
	connection_fd = accept(socket_fd, (struct sockaddr *) &my_address, &addrlen);
	if (connection_fd == -1) {
		cout << "Accept failed! Error number:" << errno << endl;
		return;
	}

	char buffer[BUFFER_SIZE]; 

	while(1) {

		// recv() is used to receive messages from a socket. 
		
		if (recv(connection_fd, &buffer, BUFFER_SIZE, 0) == -1) {
			cout << "recv failed! Error number:" << errno << endl;
			return;
		}

		cout << buffer  << endl;
		if (send(connection_fd, "const void *buf", BUFFER_SIZE, 0) == -1) {
			cout << "send failed! Error number:" << errno << endl;
			return;
		}
	}

	return;
}

int main() {

	server_setup();

	return 0;
}

