#ifndef PHYSICS_HP
#define PHYSICS_HP

#include <vector>
#include "../Interfaces.hpp"
#include "Model.hpp"

class Physics
{
	private:
		Model* model;
		float max_x;
		float max_y;
		float min_y;
		float min_x;
		

	public:
		void init(float max_x,float max_y, float min_x, float min_y);
		std::vector<Player> update(double deltaT, std::vector<Player> players, std::vector<Planet> planets);
		bool has_colision(Coordinate point_1, Coordinate point_2, float vertical_limit, float horizontal_limit);

		
	
};
#endif