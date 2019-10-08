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
	
	ship.init(position, speed);
	std::vector<Body*> body_list {&ship};

	
	std::vector<Ship> planets(10);

	for (int i = 0; i < planets.size(); i++)	{
		position.x += 5;
		planets[i].init(position, speed);
		body_list.push_back(&planets[i]);


	}


/*

	// Initialize the ship
	std::vector<Ship> rocks;
	
	position.x = 0;
	for (int i = 0; i < 5; i++)	{
		body_list.push_back(new Body());
	}

	cout <<"oid"<< body_list.size()<<endl;
	for (int i = 1; i < body_list.size(); i++) {
		position.x += 5;
		body_list[i]->init(position, speed);
	}
	while(1);

	/*position.y = 5;position.x = 5; Ship s1; s1.init(position, speed); body_list.push_back(&s1);
	position.y = 12;position.x = 11; Ship s2; s2.init(position, speed); body_list.push_back(&s2);
	position.y = 24;position.x = 24; Ship s3; s3.init(position, speed); body_list.push_back(&s3);*/
		

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
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}
	
	keyboard->stop();
	screen->stop();
        
	cout << "end program" << endl;


	return 0;
}