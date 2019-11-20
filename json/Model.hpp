#ifndef MODEL_HPP
#define MODEL_HPP

#include "json.hpp"

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
	
public:
	//void add_new_player(ns2::user_data data);
	string serialize_model(string player_id); 
	void player_data_to_json(json& j, Player player);
	void mapa_to_json(json& j, Planet planet);
};

#endif