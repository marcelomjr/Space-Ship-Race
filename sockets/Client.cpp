#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <errno.h>

#include "Client.hpp"
#define IN_BUFFER_SZ 500

int socket_fd;
struct sockaddr_in target;

using namespace std;

void Client::init(bool* is_running) {

  this->is_running = is_running;
  
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  //printf("Socket created\n");

  target.sin_family = AF_INET;
  target.sin_port = htons(3001);
  inet_aton("127.0.0.1", &(target.sin_addr));
  
  if (connect(socket_fd, (struct sockaddr*)&target, sizeof(target)) != 0) {
    cout << "connect function failed\n";
    return;
  }
  std::this_thread::sleep_for (std::chrono::milliseconds(1000));
}

void Client::send_char(char character) {

    char buf[1];
    buf[0] = character;

    int status = send(socket_fd, buf, 1, MSG_NOSIGNAL);

    if (status == -1) {
      *(this->is_running) = false;
      cout << "Error in client" << errno << endl;

    }
}
void Client::input_handler() {

  /* Recebendo resposta */
  char reply[IN_BUFFER_SZ];
  int msg_len;
  int msg_num;
  msg_num = 0;

  while(1) {
  msg_len = recv(socket_fd, reply, IN_BUFFER_SZ, MSG_DONTWAIT);
    if (msg_len > 0) {
      printf("[%d][%d] RECEBI: aa%szz\n\n\n", msg_num, msg_len, reply);
      msg_num++;
    }
  
  }
}

void Client::stop() {
  
  close(socket_fd);
  cout << "Client is ended" << endl;
}