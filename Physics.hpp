#ifndef PHYSICS_HP
#define PHYSICS_HP

#include <vector>
#include "Ship.hpp"

class Physics
{
	private:
		std::vector<Body*>* body_list;

	public:
		void init(std::vector<Body*>* body_list);
		void update(double deltaT);
		//Physics();
		//~Physics();
	
};
#endif