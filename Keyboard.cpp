#include <iostream>
#include <ncurses.h>
#include "Keyboard.hpp"

using namespace std;

void Keyboard::keyboard_loop() {
	char input;
	
	while (*(this->is_reading)) {
		//cout << this->is_reading << endl;

		input = getch();
		

		if (input != ERR) {
			*(this->last_pressed_key) = input;
			this->send_command(input);
		
		} else {
			*(this->last_pressed_key) = 0;
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

void Keyboard::send_command(char command) {
	this->myself->send_char(command);

	if (command == 'q') {
		*(this->is_reading) = false;
	}
}

Keyboard::Keyboard() {}

Keyboard::~Keyboard() {}

void Keyboard::init(Client* client, bool* is_running, char* command) {

	this->myself = client;
	this->is_reading = is_running;
	this->last_pressed_key = command;
	
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
}