#ifndef SERVER_HPP
#define SERVER_HPP

struct {
	char key;
	bool was_read;
} typedef Input_Interface;

void run_server(void* params);

#endif