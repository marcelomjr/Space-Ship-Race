#ifndef RACING_CONTROLLER_HP
#define RACING_CONTROLLER_HP


#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include "Model.hpp"

class RacingController
{
	private:

	public:
		std::vector<Player> update(std::vector<Player> players, float finish_line, std::vector<string>& results);

};
#endif