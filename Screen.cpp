#include <ncurses.h>
#include "Screen.hpp"
#include <vector>
#include <iostream>


/*
//  * Reference: https://invisible-island.net/ncurses/ncurses-intro.html#overview
 */
using namespace std;
void Screen::init(std::vector<Body*>* body_list) {
	initscr();			       /* Start curses mode 		*/
	raw();				         /* Line buffering disabled	*/
	curs_set(0);           /* Do not display cursor */

	this->max_x = 30;
	this->max_y = 100;

	this->body_list_pointer = body_list;
	this->log = "default";

	// Update reference vector
	for (int body = 0; body < (*(this->body_list_pointer)).size(); body++) {
		this->old_body_list.push_back(*((*(this->body_list_pointer))[body]));	
	}

	//for(int i=0;i<map.size(); i++) {for (int j=0;j<map[i].size(); j++){cout << map[i][j] << " ";}cout << endl;}
}

void Screen::stop() {
	endwin();
}

void add_model(matrix map, vector<string> model, coordinate pos) {
	for (int i = 0; i < model.size(); i++) {
		string row = model[i];
		
		for (int j = 0; j < row.length(); j++) {
			map[pos.x + i][pos.y + j] = row[j];
		}
	}
}


void Screen::apply_body_list(bool to_clean, coordinate ship_pos) {

	for (int body = 0; body < this->old_body_list.size(); body++) {

		std::vector<std::string> model;

		if (to_clean) {
			model = this->old_body_list[body].get_delete_mask();
		} else {
			model = this->old_body_list[body].get_model();
		}
		int _max_x = this->max_x;
		int _max_y = this->max_y;

		//Get thmessage3e real position of each body in the map
		coordinate real_pos = this->old_body_list[body].get_position();

		double delta_x = real_pos.x - ship_pos.x;
		double delta_y = real_pos.y - ship_pos.y;

		// Applay a coordinate transformation
		coordinate pos = {.x =((this->max_x/2) - delta_y), .y = ((this->max_y/2) + real_pos.x)};
		//cout << "normal        : " << to_clean<< " :"<< real_pos.x << " "<< real_pos.y << endl;	
		//cout << "transformation " << to_clean<< " :"<< pos.x << " "<< pos.y << endl;


		for (int i = 0; i < model.size(); i++) {
			string row = model[i];

			int x = pos.x + i;
			if (x >= 0 && x < _max_x) {

				for (int j = 0; j < row.length(); j++) {

			
					int y = pos.y + j;
					if (y >= 0 && y < _max_y) {
						move(x, y);
						echochar(row[j]);
					}
				}
			}
		}
	}
	
}
void Screen::update(Ship ship) {
	
	// get the old ship position in real map
	coordinate ship_pos = this->old_body_list[0].get_position();



	// Clear old image
	this->apply_body_list(true, ship_pos);

	// Clear vector
	this->old_body_list.clear();

	// Update reference vector
	for (int body = 0; body < (*(this->body_list_pointer)).size(); body++) {
		this->old_body_list.push_back(*((*(this->body_list_pointer))[body]));	
	}

	// get the ship position in real map
	ship_pos = this->old_body_list[0].get_position();

	this->apply_body_list(false, ship_pos);
	//while(1);

	// Prepare to display status
	coordinate ship_speed = this->old_body_list[0].get_speed();
	string status_speed = "speed: (" + to_string(ship_speed.x) + ", " + to_string(ship_speed.y) + ")";
	string status_pos = "position: (" + to_string(ship_pos.x) + ", " + to_string(ship_pos.y) + ")";

	move(0,0);
	addstr(status_pos.c_str());

	move(1,0);
	addstr(status_speed.c_str());
	
	move(2,0);
	addstr(this->log.c_str());


	refresh();
}

void Screen::log_message(string message) {
	this-> log = message;
}
