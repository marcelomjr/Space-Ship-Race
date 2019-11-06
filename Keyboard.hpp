#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP


#include <thread>
#include "sockets/Client.hpp"

class Keyboard
{
	private:
		std::thread kb_thread;
		bool* is_reading;
		char* last_pressed_key;
		void keyboard_loop();
		Client* myself;
		

	public:
		void init(Client* client, bool* is_running, char* command);
		void start();
		void stop();
		void send_command(char command);
		Keyboard();
		~Keyboard();
	
};
#endif