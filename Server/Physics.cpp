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

bool Physics::has_colision(Coordinate point_1, Coordinate point_2) {
	double delta_x = abs(point_1.x - point_2.x - 5);
	double delta_y = abs(point_1.y - point_2.y);
	
	if (delta_x < 8.0 && delta_y < 4.0) {
		return true;
	}
	
	return false;
	
}
std::vector<Player> Physics::update(double deltaT, std::vector<Player> players) {
	
	for (int body = 0; body < players.size(); body++){

		Coordinate pos;
		Coordinate speed = players[body].speed;

		pos.x = players[body].position.x + players[body].speed.x * deltaT;
		pos.y = players[body].position.y + players[body].speed.y * deltaT;

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
		//this->model->update_player(players[body].player_id, ;
		
	}

	return players;
	/*
	for (int body = 1; body < this->body_list->size(); body++){
		
		if (has_colision((*this->body_list)[0]->get_position(), (*this->body_list)[body]->get_position())) {
			
			Coordinate zero = {.x = 0, .y =0 };
			Coordinate speed = {.x = 0, .y =10 };
			(*this->body_list)[0]->update(zero, speed);
		}
		
	}*/
	

}