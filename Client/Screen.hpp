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
	void racing_screen(string place, float race_completed_percentage, float speed, VisualObject player, vector<VisualObject> map);
	void waiting_screen(int number_of_players);
	void game_over_screen(string names[]);
	void stop();

	
//	void log_message(string message);
};
#endif