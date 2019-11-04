#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>  // rand
#include <time.h> // to rand works
#include "Ship.hpp"
#include "Keyboard.hpp"
#include "Screen.hpp"
#include "Physics.hpp"
#include "sockets/server.hpp"

using namespace std;


int main() {
	
	Ship ship;
	coordinate speed = {.x =0, .y = 10, .z = 0};
	coordinate position = {.x =0, .y = 0, .z = 0};
	
	ship.init(position, speed);
	std::vector<Body*> body_list {&ship};
	
	Input_Interface input_interface;

	
	position.x = -50;
	position.y = 10;
	position.z = 0;
	speed.x = 0;
	speed.y = 0;
	speed.z = 0;

	srand ( time(NULL) );

	// Create the planets
	int number_of_planets = 100;

	std::vector<Planet> planets(number_of_planets);


	for (int i = 0; i < number_of_planets; i++)	{

		if (position.x > 40) {
			position.x = -50;
		}
		
		position.x += double ((rand() % 11) + 15);
		
		position.y += double ((rand() % 21) + 10);

		planets[i].init(position, speed, 2);

		body_list.push_back(&planets[i]);
		//cout << planets[i].get_position().x << " "<< planets[i].get_position().y << endl;
	}
	//while(1);

	Screen* screen = new Screen();
	screen->init(&body_list);
	
	Keyboard* keyboard = new Keyboard();
  	keyboard->init();

  	Physics* physics = new Physics();
  	physics->init(&body_list, screen);
	
	// Start the server
	std::thread server_thread(run_server, &input_interface);
	
	bool running = true, won = false;
	char c;

	double last_planet_y = planets[number_of_planets - 1].get_position().y;

	while (running) {		
		// get the pressed key
		if (!input_interface.was_read) {
			
			// To avoid read twice the same command
			input_interface.was_read = true;
			
			// Use the new command
			switch (input_interface.key) {
				case 'q':
					running = false;
					break;
				
				case 'a':
					speed.x -= 5;
					break;
					
				case 'd':
					speed.x += 5;
					break;
				
				case 'w':
					speed.y += 1;
					break;
				
				case 's':
					speed.y -= 1;
					break;
			}
		}

		// get the current position and speed of the ship
		coordinate pos = ship.get_position();
		coordinate speed = ship.get_speed();
	
		if (pos.y > last_planet_y + 15) {
			won = true;
			break;
		}

		// update the ship speed
		ship.update(pos, speed);

		// update the physics speed and position
		physics->update(0.1);
		
		
		//cout << "speed" << body_list[0]->get_speed().x << "ship da main: " << ship.get_speed().x << endl;
		//cout << "posicoes" << body_list[0]->get_position().x << "ship da main: " << ship.get_position().x << endl;
		screen->update(ship);
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}
	
	keyboard->stop();
	screen->stop();
    if (won){
    	cout << "You Win!!!!" << endl;
    } else {
    	cout << "Game Over" << endl;
    }
	


	return 0;
}