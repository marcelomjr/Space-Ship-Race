#include <iostream>
#include <vector>
#include "Model.hpp"

void Model::add_planet(Planet planet) {
	
	this->game_map.push_back(planet);
}

void Model::add_player(Player player) {
	
	this->players_data.push_back(player);
}

void Model::remove_player(string player_id) {
	bool found = false;

	for (int i = 0; i < this->players_data.size() && !found; i++) {
		if (this->players_data[i].player_id == player_id) {

			found = true;

			// remove the found player
			this->players_data.erase(this->players_data.begin() + i);

		}
	}

}

string Model::serialize_model(string player_id) {

	bool was_the_player_found = false;

	// Final JSON
	json j;
	
	// JSON for the current player
	json current_player;

	// JSON to the array of other players
	json j_players;

	// JSON to the array of planets
	json j_planets;

	// It converts all the players objects to JSON
	for (int i = 0; i < this->players_data.size(); i++) {


		// Put the current player in a different JSON.
		if (this->players_data[i].player_id == player_id) {
			// Converts the player to JSON
			this->player_to_json( this->players_data[i], current_player);


			was_the_player_found = true;
		}

		// Put the others players in a array (j_players)
		else {
			json j_player;
			// Converts the player to JSON
			this->player_to_json(this->players_data[i], j_player);
			// add the new JSON to the array
			j_players.push_back(j_player);
		}
	}

	if (!was_the_player_found) {
		cout << "Error! Not found player with this player_id: " << player_id << endl;
		return "";
	}

	// It converts the planets to a JSON array
	
	for (int i = 0; i < this->game_map.size(); i++) {
		json j_planet;
		this->planet_to_json(this->game_map[i], j_planet);
		j_planets.push_back(j_planet);
	}

	// Add the current player JSON to the final JSON
	j["player"] = current_player;


	// Add the players array to the final JSON
	j["players"] = j_players;


	// Add the planets array to the main JSON
	j["map"] = j_planets;

	// Converts the JSON to string and returns
	return j.dump();
}

void Model::player_to_json( Player player, json& j_player) {

	j_player["ship_model"] = player.ship_model;

	j_player["position"] = player.position;
}

void Model::planet_to_json(Planet planet, json& j_planet) {

	j_planet["type"] = planet.type;

	j_planet["position"] = planet.position;

	j_planet["radius"] = planet.radius;
}