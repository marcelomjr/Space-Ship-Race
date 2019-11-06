#include <iostream>

#include "Screen_Client.hpp"
#include "Keyboard.hpp"
#include "sockets/Client.hpp"
#include <thread>

using namespace std;


Screen* screen;
Keyboard* keyboard;
bool is_running;
char command = '.';

void run_view(Client* client) {

	screen = new Screen();
	screen->init();

	keyboard = new Keyboard();
  	keyboard->init(client, &is_running, &command);

	while (is_running) {
		screen->update(command);
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}

	screen->stop();
	keyboard->stop();
	cout << "Leaving run_view" << endl;
	
}

int main () {
	Client myself;
	is_running = true;
	
	char server_reply;
	cout << "client init" << endl;
	myself.init();

	run_view(&myself);
	myself.stop();
	
	return 0;
}