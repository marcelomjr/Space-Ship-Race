#ifndef PHYSICS_HP
#define PHYSICS_HP

#include <vector>
#include "Ship.hpp"
#include "Screen.hpp"

class Physics
{
	private:
		std::vector<Body*>* body_list;
		

	public:
		Screen* screen_reference;
		void init(std::vector<Body*>* body_list, Screen* screen_reference);
		void update(double deltaT);
		bool has_colision(coordinate point_1, coordinate point_2);
		//Physics();
		//~Physics();
	
};
#endif