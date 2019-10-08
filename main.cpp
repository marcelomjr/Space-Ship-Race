#include <iostream>
#include <chrono>
#include <thread>
#include "Ship.hpp"
#include "Keyboard.hpp"
#include "Screen.hpp"

using namespace std;


int main() {
	
	Ship ship;
	coordinate speed = {.x =0, .y = 0, .z = 0};
	coordinate position = {.x =10, .y = 10, .z = 0};
	std::vector<Body*> body_list {&ship};
	
	// Initialize the ship
	ship.init(position, speed);
	
	Screen* screen = new Screen();
	screen->init(&body_list);
	
	Keyboard* keyboard = new Keyboard();
  	keyboard->init();
	
	
	
	bool running = true;
	char c;
	while (running) {		
		
		c = keyboard->get_last_pressed_key();
		coordinate pos = ship.get_position();
		
		//pos.y += 0.5;
		if (c == 'q') break;
		else if (c == 'a') {
			pos.x -= 1;
		}
		else if (c == 'd'){
			pos.x += 1;
		}
		else if (c == 'w') {
			pos.y += 1;
		}
		else if (c == 's') {
			pos.y -= 1;
		}
		
		
		ship.update(pos, speed);
		screen->update(ship);
		std::this_thread::sleep_for (std::chrono::milliseconds(50));
	}
	
	keyboard->stop();
	screen->stop();
        
	cout << "end program" << endl;


	return 0;
}