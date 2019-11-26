#ifndef SCREEN_HP
#define SCREEN_HP

#include <vector>
#include <ncurses.h>
#include <iostream>
#include "../Interfaces.hpp"

class Screen {
private:
	int max_x;
	int max_y;
	GameManagerInterface* game_manager;
	
	
//	string log;

public:
	void init(GameManagerInterface* game_manager);
	void racing_screen(string place, float completed_percentage, float player_speed, ns::VisualObject player, vector<ns::VisualObject> map);
	void waiting_screen(int number_of_players);
	void game_over_screen(string names[]);
	void stop();

	void render_objects(vector<ns::VisualObject> map, Coordinate player_position);

	
//	void log_message(string message);
};
#endif