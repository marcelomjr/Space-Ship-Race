#include <iostream>
#include <chrono>
#include <thread>
#include "Ship.hpp"
#include "Keyboard.hpp"

using namespace std;


int main() {
	Ship ship;
	coordinate speed;
	coordinate position;
	speed.x = 10;
	position.x = 0;


	Keyboard *keyboard = new Keyboard();
  	keyboard->init();


	while (position.x < 1) {
		
		position.x += 0.1;
		ship.update(position, speed);
		std::this_thread::sleep_for (std::chrono::milliseconds(100));

	}
	
	keyboard->stop();



	return 0;
}