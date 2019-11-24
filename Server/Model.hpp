#ifndef MODEL_HPP
#define MODEL_HPP

#include "../json.hpp"

using namespace std;

using json = nlohmann::json;

struct Player
{
	string player_id;
	string ship_model;
	float position[3];
	float speed[3];
};

struct Planet
{	string type;
	float position[3];
	float radius;
};

class Model
{
private:
	//map current_map;
	vector<Player> players_data;
	vector<Planet> game_map;

	// Private functions
	void player_to_json( Player player, json& j_player);

	void planet_to_json(Planet planet, json& j_planet);
	
public:
	
	void add_planet(Planet planet);
		
	void add_player(Player player);

	void remove_player(string player_id);

	string serialize_model(string player_id);
};

#endif