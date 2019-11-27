#include <iostream>
#include <vector>
#include "Model.hpp"

void Model::add_planet(Planet planet) {
	
	this->game_map.push_back(planet);
}

void Model::add_player(Player player) {
	
	this->players_data.push_back(player);
}

void Model::remove_player(int player_id) {
	bool found = false;

	for (int i = 0; i < this->players_data.size() && !found; i++) {
		if (this->players_data[i].player_id == player_id) {

			found = true;

			// remove the found player
			this->players_data.erase(this->players_data.begin() + i);

		}
	}
	cout << "apóx excluir o " << player_id << endl;
	for (int i = 0; i < this->players_data.size(); i++) {
		cout << this->players_data[i].player_id << " ";
	}
	cout << endl;

}

string Model::serialize_model(int player_id, json& j) {

	bool was_the_player_found = false;
	
	// JSON for the current player
	json current_player;

	// JSON to the array of other players
	json j_players = json::array();

	// JSON to the array of planets
	json j_planets = json::array();

	// It converts all the players objects to JSON
	for (int i = 0; i < this->players_data.size(); i++) {


		// Put the current player in a different JSON.
		if (this->players_data[i].player_id == player_id) {
			// Converts the player to JSON
			this->player_to_json(this->players_data[i], current_player);
			// Sends the player state as well
			current_player["name"] = this->players_data[i].name;
			current_player["player_state"] = this->players_data[i].player_state;
			current_player["place"] = this->players_data[i].place;
			current_player["speed"]["x"] = round(this->players_data[i].speed.x);
			current_player["speed"]["y"] = round(this->players_data[i].speed.y);
			current_player["speed"]["z"] = round(this->players_data[i].speed.z);


			was_the_player_found = true;
		}

		// Put the others players in a array (j_players)
		else {
			// Just send active players
			if (this->players_data[i].player_state != inactive) {

				json j_player;

				// Converts the player to JSON
				this->player_to_json(this->players_data[i], j_player);

				// add the new JSON to the array
				j_players.push_back(j_player);
			}
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


	j["results"] = this->results;


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

	j_player["player_id"] = player.player_id;

	j_player["model"] = player.ship_model;

	j_player["position"]["x"] = round(player.position.x);
	j_player["position"]["y"] = round(player.position.y);
	j_player["position"]["z"] = round(player.position.z);

}

void Model::planet_to_json(Planet planet, json& j_planet) {

	j_planet["model"] = planet.type;

	j_planet["position"]["x"] = round(planet.position.x);
	j_planet["position"]["y"] = round(planet.position.y);
	j_planet["position"]["z"] = round(planet.position.z);
}

Player Model::get_player(int player_id) {
	for (int i = 0; i < this->players_data.size(); ++i)
	{
		if (this->players_data[i].player_id == player_id) {
			return this->players_data[i];
		}
	}
	cout << "Not found this player:" << player_id << endl;
}

void Model::update_player(int player_id, Player player) {
	for (int i = 0; i < this->players_data.size(); ++i)
	{
		if (this->players_data[i].player_id == player_id) {
			this->players_data[i] = player;
			return;
		}
	}
	cout << "In update player, not found this player:" << player_id << endl;
}

std::vector<Player> Model::get_players() {
	return this->players_data;
}

std::vector<Planet> Model::get_planets() {
	return this->game_map;	
}

void Model::activate_players() {
	for (int i = 0; i < this->players_data.size(); ++i)
	{
		this->players_data[i].player_state = active;
	}
}

void Model::update_results(std::vector<string> results) {
	this->results = results;
}

std::vector<string> Model::get_results(){
	return this->results;
}