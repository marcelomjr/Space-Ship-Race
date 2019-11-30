#include "ClientSocket.hpp"

using namespace std;

void ClientSocket::init(GameManagerInterface* game_manager, Input_Handler_Interface* input_handler) {

  this->game_manager = game_manager;
  this->input_handler = input_handler;

  
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  //printf("Socket created\n");

  target.sin_family = AF_INET;
  target.sin_port = htons(3001);
  inet_aton(ADDRESS, &(target.sin_addr));
  
  bool is_connected = false;
  while (!is_connected) {

    int status = connect(socket_fd, (struct sockaddr*)&target, sizeof(target));

    if (status == 0) {
      is_connected = true;
    } else {
      cout << "connect function failed! (errno: "<< errno << ") Trying again!\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }
}

void ClientSocket::send_message(string message) {

    // Get the buffer size (JSON + '\0')
    int buffer_size = message.length()+1;

    // It Converts the std::string to a c string
    char * output_buffer = new char [buffer_size];
    std::strcpy (output_buffer, message.c_str());
	 

    int status = send(socket_fd, output_buffer, buffer_size, MSG_NOSIGNAL);

    if (status == -1) {
      cout << "Error in client" << errno << endl;

    }
}
void ClientSocket::receiving_loop() {

  
  char input_buffer[IN_BUFFER_SZ];
  int msg_len;
  
  // While game is running
  while(this->game_manager->is_running()) {
  msg_len = recv(this->socket_fd, input_buffer, IN_BUFFER_SZ, MSG_DONTWAIT);
    if (msg_len > 0) {
      //printf("[%d][%s]\n\n", msg_len, input_buffer);
		
      this->input_handler->receiving_handler(0, input_buffer);
    }
  
  }
}

void ClientSocket::start() {

  if (!(this->game_manager->is_running())){
    cout << "Error the game is not running!";
    return;
  } 

  // Creates a new thread for receiving new connections
  std::thread receiving_thread(&ClientSocket::receiving_loop, this);


  // Save the thread reference before return from this function
  this->receiving_loop_thread.swap(receiving_thread);


}

void ClientSocket::stop() {
  
  close(socket_fd);
  
  // It waits the thread ends
  this->receiving_loop_thread.join();
  cout << "ClientSocket was stopped" << endl;

}
