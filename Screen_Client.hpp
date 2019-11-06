#ifndef SCREEN_HP
#define SCREEN_HP

#include "Ship.hpp"
#include <string>

class Screen {
private:
	int max_x;
	int max_y;
	std::vector<Body*>* body_list_pointer;
	std::vector<Body> old_body_list;
	void apply_body_list(bool to_clean, coordinate ship_pos);
	string log;

public:
	
	void init();
	void stop();
	void update(char command);
	void log_message(string message);
};
#endif