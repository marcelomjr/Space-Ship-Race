#include <iostream>
#include <cmath>        // std::abs
#include "Model.hpp"
#include "Physics.hpp"

void Physics::init(float max_x,float max_y, float min_x, float min_y) {
	this->max_x = max_x;
	this->max_y = max_y;
	this->min_x = min_x;
	this->min_y = min_y;
}

bool Physics::has_colision(Coordinate point_1, Coordinate point_2, float  horizontal_limit, float vertical_limit) {
	double delta_x = abs(point_1.x - point_2.x);
	double delta_y = abs(point_1.y - point_2.y);
	
	if (delta_x < horizontal_limit && delta_y < vertical_limit) {
		return true;
	}
	
	return false;
	
}
std::vector<Player> Physics::update(double deltaT, std::vector<Player> players, std::vector<Planet> planets) {
	
	for (int body = 0; body < players.size(); body++){

		Coordinate pos;
		Coordinate speed = players[body].speed;

		pos.x = players[body].position.x + speed.x * deltaT;
		pos.y = players[body].position.y + speed.y * deltaT;

		if (pos.x > this->max_x) {
			pos.x = this->max_x;
			speed.x = 0;

		}
		else if (pos.x < this->min_x) {
			pos.x = this->min_x;
			speed.x = 0;
		}

		if (pos.y >this->max_y) {
			pos.y = this->max_y;
			speed.y = 0;
		}
		else if (pos.y < this->min_y) {
			pos.y = this->min_y;
			speed.y = 0;
		}

		players[body].position = pos;
		players[body].speed = speed;
		
		cout << "please:{" << players[body].position.y << "}" << endl;
		
		
	}

	
	for (int i = 0; i < players.size(); i++) {
		for (int j = i + 1; j < players.size(); j++) {
		
			if (has_colision(players[i].position, players[j].position, 5, 5)) {
				
				players[i].player_state = inactive;
				players[j].player_state = inactive;
			}
		}

		for (int j = 0; j < planets.size(); j++) {
		
			if (has_colision(players[i].position, planets[j].position, 9, 6)) {
				
				players[i].player_state = inactive;
			}
		}
	}
	
	return players;

}