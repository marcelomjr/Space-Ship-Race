#include <iostream>
#include "Ship.hpp"


void Body::update(coordinate position, coordinate speed) {
		this->position = position;
		this->speed = speed;

		//cout << "Body: position:" << this->get_position().x << endl;
}
coordinate Body::get_position() {
	return this->position;
}

void Ship::init(coordinate initial_position, coordinate initial_speed) {
	
	std::vector<std::string> ship_model {
												" /\\",
												"/__\\",
												"|::|",
												"|::|",
												"/^^\\",
												"^^^^"};
	
	this->model = ship_model;
	
	
	this->model_height = 6;
	this->model_width = 5;
	
	 
									
	this->update(initial_position, initial_speed);
}

double Ship::get_model_height() {
	return this->model_height;
}
double Ship::get_model_width() {
	return this->model_width;
}
std::vector<std::string> Ship::get_model() {
	return this->model;
}