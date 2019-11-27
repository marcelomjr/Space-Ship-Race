#include "Screen.hpp"

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

		//cout << map[i].position.x << ", " << map[i].position.y << ", "<< map[i].position.z <<": " << map[i].model << endl;
//		cout << this->old_map[i].position.x << ", " << this->old_map[i].position.y << ", "<< this->old_map[i].position.z <<": " << this->old_map[i].model << endl;
		//move(map[i].position[0],map[i].position[1]);
	}
	//cout << endl << endl;
	// Clear last frame
	//this->render_objects(this->old_map, old_player.position, true);
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

	move(1,0);
	//string percentage = "Completado: " + to_string(completed_percentage) + "%";
	//addstr(percentage.c_str());

	move(0,this->max_y - 19);
	string full_speed = "Velocidade: " + to_string((int)player_speed) + "km/h";
	addstr(full_speed.c_str());

	if (results.size() > 0) {
		move(2,this->max_y - 19);
		addstr("Podium:");
		for (int i = 0; i < results.size(); ++i) {
			move(0,this->max_y - 19);
			string podium = to_string(i + 1) + results[i];
			addstr(podium.c_str());
		
			
		}
	}
	
	refresh();

}

void Screen::waiting_screen(int number_of_players) {
	move(0,0);
	


	
	string message2 = "Quando todos os jogadores estiverem conectados, basta teclar 's'";
	addstr(message2.c_str());

	move(2,0);
	string message = "Há " + to_string(number_of_players) + " pessoas conectadas";
	addstr(message.c_str());

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
/*
void Screen::update(Ship ship) {
	
	// get the old ship position in real map
	Coordinate ship_pos = this->old_body_list[0].get_position();



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
	Coordinate ship_speed = this->old_body_list[0].get_speed();
	string status_speed = "speed: (" + to_string(ship_speed.x) + ", " + to_string(ship_speed.y) + ")";
	string status_pos = "position: (" + to_string(ship_pos.x) + ", " + to_string(ship_pos.y) + ")";

	move(0,0);
	addstr(status_pos.c_str());

	move(1,0);
	addstr(status_speed.c_str());
	
	move(2,0);
	//addstr(this->log.c_str());


	refresh();
}

void Screen::log_message(string message) {
	this-> log = message;
}
*/
