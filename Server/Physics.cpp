#include <iostream>
#include <cmath>        // std::abs
#include "Model.hpp"
#include "Physics.hpp"

//void Physics::init(Model* model) {}

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


		players[body].position.x += players[body].speed.x * deltaT;
		players[body].position.y += players[body].speed.y * deltaT;
		
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