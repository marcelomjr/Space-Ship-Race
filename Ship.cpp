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

std::vector<std::string> Body::get_model() {
	return this->model;
}

std::vector<std::string> Body::get_delete_mask() {
	
	string blanks (this->model_width, ' ');
	vector<string> mask(this->model_height, blanks);

	return mask;
}

void Body::set_model(std::vector<std::string> new_model, double height, double width) {
	this->model_height = height;
	this->model_width = width;
	this->model = new_model;
}

double Body::get_model_height() {
	return this->model_height;
}
double Body::get_model_width() {
	return this->model_width;
}


void Body::init(coordinate initial_position, coordinate initial_speed) {
	this->update(initial_position, initial_speed);
}

void Ship::init(coordinate initial_position, coordinate initial_speed) {
	
	Body::init(initial_position, initial_speed);

	std::vector<std::string> ship_model {
												" /\\",
												"/__\\",
												"|::|",
												"|::|",
												"/^^\\",
												"^^^^"};
	
	this->set_model(ship_model, 6, 5);									
}
Ship::Ship() {

}

Ship::~Ship() {
	
}


