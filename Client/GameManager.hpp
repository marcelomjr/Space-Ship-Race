#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <iostream>
#include "../Interfaces.hpp"
#include "ClientSocket.hpp"
#include "Screen.hpp"
#include "Keyboard.hpp"

class GameManager: public Input_Handler_Interface, public GameManagerInterface, public KeyboardInterface
{
public:
	void start(string name);
	bool is_running();
	void update_screen(string input_buffer);
	void receiving_handler(string buffer);
	void keystroke_handler(char key);

private:
	Screen screen;
	ClientSocket socket;
	bool is_running_flag;
	
};

#endif