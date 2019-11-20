#include <iostream>
#include <vector>
#include "Model.hpp"


void Model::player_data_to_json(json& j, Player player) {
	
	json j_player;

	j_player["ship_model"] = player.ship_model;

	j_player["position"] = player.position;

	j.push_back(j_player);
}

void Model::mapa_to_json(json& j, Planet planet) {
	
	json j_planet;

	j_planet["type"] = planet.type;

	j_planet["position"] = planet.position;

	j_planet["radius"] = planet.radius;

	j.push_back(j_planet);
}


string Model::serialize_model(string player_id) {


	// create vector of players
	string d;
	for (int i = 0; i < 10; i++) {
		Player player = {"id:" + to_string(i), "rocket", {1,2, 3}, {3,2,1}};

		this->players_data.push_back(player);
	}
	// create planets
	for (int i = 0; i < 5; i++) {
		Planet new_planet = {"type" + to_string(i), {3,2,1}, 4};
		this->game_map.push_back(new_planet);
	}

	json j;

	// It converts the players data to a json array
	json players;

	for (int i = 0; i < this->players_data.size(); i++) {
		this->player_data_to_json(players, this->players_data[i]);

	}

	// Add the players array to the main json
	j["players"] = players;

	// It converts the planets to a json array
	json j_planets;
	for (int i = 0; i < this->game_map.size(); i++) {
		this->mapa_to_json(j_planets, this->game_map[i]);
	}

	// Add the planets array to the main json
	j["map"] = j_planets;


	cout << j << endl << endl;

	cout << j["players"][0] << endl;

	return "";

}