#ifndef SCREEN_HP
#define SCREEN_HP

#include <vector>
#include <ncurses.h>
#include <iostream>
#include <sys/ioctl.h> // Get terminal size
#include "../Interfaces.hpp"

class Screen {
private:
	int max_x;
	int max_y;
	GameManagerInterface* game_manager;
	std::vector<VisualObject> old_map;
	VisualObject old_player;
	
	
//	string log;

public:
	void init(GameManagerInterface* game_manager);
	void racing_screen(int place, float completed_percentage, float player_speed, 
					   VisualObject player, vector<VisualObject> map, std::vector<string> v);

	void waiting_screen(int number_of_players);
	void game_over_screen(string names[]);
	void stop();

	void render_objects(vector<VisualObject> map, Coordinate player_position, bool clear_mode);

	
//	void log_message(string message);
};
#endif