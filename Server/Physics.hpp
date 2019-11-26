#ifndef PHYSICS_HP
#define PHYSICS_HP

#include <vector>
#include "../Interfaces.hpp"
#include "Model.hpp"

class Physics
{
	private:
		Model* model;
		

	public:
		//void init(Model* model);
		std::vector<Player> update(double deltaT, std::vector<Player> players);
		bool has_colision(Coordinate point_1, Coordinate point_2);
		//Physics();
		//~Physics();
	
};
#endif