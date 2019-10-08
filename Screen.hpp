#ifndef SCREEN_HP
#define SCREEN_HP

#include "Ship.hpp"

class Screen {
private:
	int max_x;
	int max_y;
	std::vector<Body*>* body_list_pointer;
	std::vector<Body> old_body_list;
	std::vector<std::vector<char>> blank_map;
	void apply_body_list(bool to_clean);

public:
	
	void init(std::vector<Body*>* body_list);
	void stop();
	void update(Ship ship);
};
#endif