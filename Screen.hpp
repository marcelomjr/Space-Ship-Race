#ifndef SCREEN_HP
#define SCREEN_HP

#include "Ship.hpp"

class Screen {
private:
public:
	void init();
	void stop();
	void update(Ship ship);
};
#endif