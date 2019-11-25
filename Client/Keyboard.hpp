#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP


#include <thread>
#include "../Interfaces.hpp"

class Keyboard
{
	private:
		std::thread kb_thread;
		void keyboard_loop();
		GameManagerInterface* game_manager;
		KeyboardInterface* keyboard_inteface;
		

	public:
		void init(GameManagerInterface* game_manager, KeyboardInterface* keyboard_inteface);
		void stop();
		//void send_command(char command);
		Keyboard();
		~Keyboard();
	
};
#endif