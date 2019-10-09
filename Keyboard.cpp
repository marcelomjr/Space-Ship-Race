#include <iostream>
#include <ncurses.h>
#include <thread>
#include "Keyboard.hpp"

using namespace std;


void keyboard_handler(bool *is_reading, char* last_pressed_key) {
	char input;
	while (*is_reading) {

		input = getch();
				

		if (input != ERR) {
			*last_pressed_key = input;
		} else {
			*last_pressed_key = 0;
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}



Keyboard::Keyboard() {}

Keyboard::~Keyboard() {}

void Keyboard::init() {
	
	raw();				         // Line buffering disabled
	//keypad(stdscr, TRUE);	 	// We get F1, F2 etc..		
	noecho();			         // Don't echo() while we do getch
	curs_set(0);           		//Do not display cursor
	nodelay(stdscr, TRUE);		// Do not wait until a key is hit
	//cbreak();						// each key the user hits is returned immediately by getch()
	
	// Flag initialization
	this->is_reading = true;
	// std::thread name() Accepts as parameters 1. callable function 2. args list
	std::thread keyboard_thread(keyboard_handler, &this->is_reading, &this->last_pressed_key);

	// Save the thread reference before return from this function
	(this->kb_thread).swap(keyboard_thread);

}


void Keyboard::stop() {
	// It changes the boolean that holds the keyboard thread working
	this->is_reading = false;
	// It waits the thread ends
	this->kb_thread.join();
}

char Keyboard::get_last_pressed_key() {
  char key = this->last_pressed_key;
  this->last_pressed_key = 0;
  return key;
}