
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include "Keyboard.hpp"

void send_command(char command) {
	
}

int main() {
  int socket_fd;
  struct sockaddr_in target;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket criado\n");

  target.sin_family = AF_INET;
  target.sin_port = htons(3001);
  inet_aton("127.0.0.1", &(target.sin_addr));
  printf("Tentando conectar\n");
  if (connect(socket_fd, (struct sockaddr*)&target, sizeof(target)) != 0) {
    printf("Problemas na conexao\n");
    return 0;
  }
	printf("Conectei ao servidor\n");
  
	Keyboard* keyboard = new Keyboard();
	//keyboard->init();

  char command[1];
  
  while(1) {
    printf("estou aqui1\n");
		command[0] = keyboard->get_last_pressed_key();
    
		 printf("Error!%d\n", (int) send(socket_fd, command, 10, MSG_NOSIGNAL));
	 
    //printf("%c\n", command[0]);
    
  }
  
  close(socket_fd);
  keyboard->stop();
  return 0;
}
