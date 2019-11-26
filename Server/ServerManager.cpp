#include "ServerManager.hpp"

using namespace std;

int main() {
	ServerManager manager;

	manager.start();
	return 0;
}

void ServerManager::start() {

	this->is_running_flag = true;
	
	this->game_state = waiting;

	ServerSocket server;

	server.init(this, this);
	server.start();

	Physics physics;
	physics.init(10,100, -10, -5);


	while (this->is_running_flag) {
		while(this->game_state == waiting);


		this->is_input_blocked = true;

		//update the waiting list

		this->create_the_map();

		//TODO: Put timer
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		this->is_input_blocked = false;

		this->game_state = racing;

		while(this->game_state == racing) {

			std::vector<Player> players = physics.update(0.1, this->model.get_players());

			for (int i = 0; i < players.size(); ++i)
			{
				this->model.update_player(players[i].player_id, players[i]);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(25));

		}
	}
}

void ServerManager::create_the_map() {
	 // create planets
	  
	    Planet new_planet1 = {"planet1", {20,20,0}, 4.0}; model.add_planet(new_planet1);
	    Planet new_planet2 = {"planet1", {-20,20,0}, 4.0}; model.add_planet(new_planet2);
	    Planet new_planet3 = {"planet1", {40,40,0}, 4.0}; model.add_planet(new_planet3);
	    Planet new_planet4 = {"planet1", {-40,-40,0}, 4.0}; model.add_planet(new_planet4);
	
}


bool ServerManager::is_running() {

	return this->is_running_flag;
}
	
	
void ServerManager::receiving_handler(int id, string buffer) {

	this->game_state = racing;



	Player player = this->model.get_player(id);

	if (buffer.size() < 1) {
		return;
	}

	switch (buffer[0]) {
		case 'a':
			player.speed.x -= 5;
			break;
			
		case 'd':
			player.speed.x += 5;
			break;
		
		case 'w':
			player.speed.y += 1;
			break;
		
		case 's':
			player.speed.y -= 1;
			break;
		default:
			return;
	}
	this->model.update_player(id, player);



	

	
	// Converts the string to json
	cout << "Received:" << buffer << endl;
}

string ServerManager::get_the_updated_model(int player_id) {

	json j;

	j["game_state"] = this->game_state;

	string serialized_model = this->model.serialize_model(player_id, j);

	cout << serialized_model << endl;

	return serialized_model;
}

std::vector<int> wait_list;

void ServerManager::new_player_connected(int player_id) {

	if (this->game_state == racing) {
		wait_list.push_back(player_id);
		return;
	}

	cout << "Registrou " << player_id << endl;

	Player player;
	player.position.x = 0;
	player.position.y = 0;

	player.speed.y = 1;

	player.player_id = player_id;
	player.ship_model = "spaceship";

	this->model.add_player(player);
}

void ServerManager::player_desconnected(int player_id) {

	model.remove_player(player_id);
}
bool ServerManager::is_socket_active() {
	if (this->game_state == racing) {
		return true;
	}
	else return false;
}