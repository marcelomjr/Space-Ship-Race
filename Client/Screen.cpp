#include "Screen.hpp"
#include <math.h>       /* round, floor, ceil, trunc */


/*
//  * Reference: https://invisible-island.net/ncurses/ncurses-intro.html#overview
 */
using namespace std;

void Screen::init(GameManagerInterface* game_manager) {

	this->game_manager = game_manager;

	initscr();		/* Start curses mode 		*/
	noecho();			         // Don't echo() while we do getch

	raw();			/* Line buffering disabled	*/
	curs_set(0);    /* Do not display cursor */

	// Get terminal size
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

	this->max_x = w.ws_row;
	this->max_y = w.ws_col;
}

void Screen::racing_screen(int place, float completed_percentage, float player_speed, VisualObject player, vector<VisualObject> map, std::vector<string> results) {

	

	for (int i = -50; i < 1050; ++i)
	{
		VisualObject left;
		left.position = {-102.0, (float) i, 0.0};
		left.model = "border";
		map.push_back(left);

		VisualObject right;
		right.position = {102.0, (float) i, 0.0};
		right.model = "border";
		map.push_back(right);
	}

	
	// Clear last frame
	erase();

	move(0,0);
	// Create new frame
	this->render_objects(map, player.position, false);

	// Save the current map	to use it after to clean the screen
	this->old_map = map;
	this->old_player = player;

	move(1, this->max_y - 19);
	string place_str = "Place: " + to_string((int)place);
	addstr(place_str.c_str());


	move(0,20);
	//string position = "x: " + to_string(player.position.x) + ", y: " + to_string(player.position.y);
	//addstr(position.c_str());

	move(0,0);
	string percentage = "Completed: " + to_string((int) round(player.position.y)/10) + "%";
	addstr(percentage.c_str());

	move(0,this->max_y - 19);
	string full_speed = "Speed: " + to_string((int)player_speed) + "km/h";
	addstr(full_speed.c_str());

	if (results.size() > 0) {
		move(2,this->max_y - 19);
		addstr("Podium:");
		for (int i = 0; i < results.size(); ++i) {
			move(3 + i,this->max_y - 19);
			string podium = to_string(i + 1) + ": " + results[i];
			addstr(podium.c_str());
		
			
		}
	}
	
	refresh();

}

void Screen::waiting_screen(int number_of_players) {
	move(0,0);
	


	
	string message2 = "When all the players are ready press 's'";
	addstr(message2.c_str());

	refresh();

}

void Screen::game_over_screen(string names[]) {
	

}
void Screen::debug(string buffer) {
	move(0,0);

	erase();

	addstr(buffer.c_str());

	refresh();

}

void Screen::stop() {
	endwin();
}


std::vector<string> get_model(string model, bool clear_mask) {


	if (model == "spaceship") {
		if (clear_mask) {
			return {
				"    ",
				"    ",
				"    ",
				"    ",
				"    "
			};

		}

		return {

			" /^\\ ",
			"/:::\\",
		   "\\___/",
			"/^^^\\",
			"^^^^^"
		};
	}

	
	if (model == "planet1") {
		if (clear_mask) {
			return {
				"             ",  
				"             ",
				"             ",
				"             ",
				"             ",
				"             ",
				"             "
			};

		}

		return {
			"   ooooooo   ",  
			" o         o ",
			"o           o",
			"o           o",
			"o           o",
			" o         o ",
			"   ooooooo   "
		};
	}

	if (model == "dot") {
		return{"O"};

	}
	if (model == "border") {
		return{"|"};

	}
	if (model == "start_line") {
		return {":::::::::::::::START"};
	}
	if (model == "finish_line") {
		return {"::::::::::::::FINISH"};
	}


	return {"ERROR"};
}

void Screen::render_objects(vector<VisualObject> map, Coordinate player_position, bool clear_mode) {


	for (int body = map.size() - 1; body > -1; body--) {

		std::vector<string> model;

		model =	get_model(map[body].model, clear_mode);

		int _max_x = this->max_x;
		int _max_y = this->max_y;

		//Get thmessage3e real position of each body in the map
		Coordinate real_pos = map[body].position;

		float delta_x = real_pos.x - player_position.x;
		float delta_y = real_pos.y - player_position.y;


		// Correction of position
		if (map[body].model == "planet1") {
			delta_x -= 6;
			delta_y += 3;
		}
		else if (map[body].model == "spaceship")  {
			// Correction
			delta_x -= 2;
			delta_y += 2;
		}

		// Apply a Coordinate transformation
		Coordinate pos = {.x =((this->max_x/2) - delta_y + 10), .y = ((this->max_y/2) + delta_x)};

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