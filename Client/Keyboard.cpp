#include <iostream>
#include <ncurses.h>
#include "Keyboard.hpp"

using namespace std;

void Keyboard::keyboard_loop() {
	char input;
	
	while (this->game_manager->is_running()) {
		//cout << this->is_reading << endl;

		input = getch();
		

		if (input != ERR) {
			//*(this->last_pressed_key) = input;
			this->keyboard_inteface->keystroke_handler(input);
		
		} else {
			//*(this->last_pressed_key) = 0;
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

Keyboard::Keyboard() {}

Keyboard::~Keyboard() {}

void Keyboard::init(GameManagerInterface* game_manager, KeyboardInterface* keyboard_inteface) {

	this->game_manager = game_manager;
	this->keyboard_inteface = keyboard_inteface;
	
	raw();				         // Line buffering disabled
	//keypad(stdscr, TRUE);	 	// We get F1, F2 etc..		
	noecho();			         // Don't echo() while we do getch
	curs_set(0);           		//Do not display cursor
	//nodelay(stdscr, TRUE);		// Do not wait until a key is hit
	//cbreak();						// each key the user hits is returned immediately by getch()
	
	std::thread keyboard_thread(&Keyboard::keyboard_loop, this);

	// Save the thread reference before return from this function
	(this->kb_thread).swap(keyboard_thread);
}


void Keyboard::stop() {
	// It waits the thread ends
	this->kb_thread.join();
	cout << "Keyboard was stopped" << endl;
}