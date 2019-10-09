#include "Physics.hpp"
#include <iostream>

void Physics::init(std::vector<Body*>* body_list) {
	this->body_list = body_list;
}

void Physics::update(double deltaT){
	
	for (int body = 0; body < this->body_list->size(); body++){

		coordinate pos =   (*this->body_list)[body]->get_position();
		coordinate speed = (*this->body_list)[body]->get_speed();

		pos.x = pos.x + speed.x * deltaT;
		pos.y = pos.y + speed.y * deltaT;

		(*this->body_list)[body]->update(pos, speed);
	}

}