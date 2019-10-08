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
	this->max_y = 60;
	this->body_list_pointer = body_list;

	vector<char> row (this->max_y, ' ');
	vector<vector<char>> map(this->max_x, row);
	this->blank_map = map;

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


void Screen::apply_body_list(bool to_clean) {

	for (int body = 0; body < this->old_body_list.size(); body++) {

		std::vector<std::string> model;

		if (to_clean) {
			model = this->old_body_list[body].get_delete_mask();
		} else {
			model = this->old_body_list[body].get_model();
		}
		int _max_x = this->max_x;
		int _max_y = this->max_y;
		for (int i = 0; i < model.size(); i++) {
			string row = model[i];

			coordinate pos = this->old_body_list[body].get_position();
			
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
	
	// Gets a fresh blank map
	//vector<vector<char>> new_map = this->blank_map;

	
	coordinate real_pos = ship.get_position();
	coordinate pos = real_pos;//{.x = (30 - real_pos.y), .y = (50 +real_pos.x)};

	// Clear old image
	this->apply_body_list(true);

	// Clear vector
	this->old_body_list.clear();

	// Update reference vector
	for (int body = 0; body < (*(this->body_list_pointer)).size(); body++) {
		this->old_body_list.push_back(*((*(this->body_list_pointer))[body]));	
	}

	this->apply_body_list(false);


	refresh();

	
	
}

