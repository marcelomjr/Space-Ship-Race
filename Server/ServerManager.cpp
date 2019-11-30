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


	while (this->is_running_flag) {
		while(this->game_state == waiting);


		this->is_input_blocked = true;

		//update the waiting list

		this->create_the_map();

		//TODO: Put timer
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		this->is_input_blocked = false;

		this->model.activate_players();

		this->game_state = racing;

		while(this->game_state == racing) {

			std::vector<Player> players = this->model.get_players();

			players = physics.update(0.1, players, this->model.get_planets());

			std::vector<string> results = this->model.get_results();

			players = racing_controller.update(players, this->finish_line, results);

			this->model.update_results(results);

			for (int i = 0; i < players.size(); ++i)
			{
				this->model.update_player(players[i].player_id, players[i]);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(25));

		}
	}
}

void ServerManager::create_the_map() {
		
	// Define the limits of the space
	float min_x = -100;
	float max_x = 100;
	float min_y = -10;
	float max_y = 1000;
	this->finish_line = max_y - 15;

	this->physics.init(min_x, max_x, min_y, max_y);

	// create planets
	float y = 30;
	float x = min_y;

	float horizontal_distance = 20;

	for (int i = min_x; i < max_x; i += 20)
	{
		Planet start_line;
		start_line.position = {(float) i, 10.0, 0.0};
		start_line.type = "start_line";
		start_line.can_collide = false;
		
		model.add_planet(start_line);
		
	}

	for (int i = min_x; i < max_x; i += 20)
	{
		Planet finish_line_object;
		finish_line_object.position = {(float) i, this->finish_line, 0.0};
		finish_line_object.type = "finish_line";
		finish_line_object.can_collide = false;
		
		model.add_planet(finish_line_object);
		
	}
	
	srand ( time(NULL) );
	
	x = min_x -10;
	while (y < this->finish_line) {

		while (x < max_x) {
			x += float ((rand() % (int) horizontal_distance) + 5);
		
			y += float ((rand() % 15) + 10);

			// New Planet
			Planet new_planet;
			new_planet.position = {x,y,0.0};
			new_planet.type = "planet1";
			new_planet.can_collide = true;
			model.add_planet(new_planet);
		}
		x = min_x -10;
		horizontal_distance = horizontal_distance * 0.8;
	}
	    
    std::vector<Player> players = this->model.get_players();

    float spawn_x = (max_x - min_x) / (players.size() + 1);

    for (int i = 0; i < players.size(); ++i)
    {
    	players[i].position.x = min_x + spawn_x * (players[i].player_id + 1);
    	players[i].speed.y = 0;

    	this->model.update_player(players[i].player_id, players[i]);

    }	
}


bool ServerManager::is_running() {

	return this->is_running_flag;
}
	
	
void ServerManager::receiving_handler(int id, string buffer) {
			
	if (this->game_state == waiting) {

		if (buffer.size() == 1 && buffer[0] == 's') {
			this->game_state = racing;
			return;
		}

		else if (buffer.size() > 1) {

			json j = json::parse(buffer);

			if (!j["name"].is_null()) {
				Player player = this->model.get_player(id);
				j["name"].get_to(player.name);

				this->model.update_player(id, player);
			} 
		}
		return;
	}


	float max_y_speed = 15;
	float max_x_speed = 6;



	Player player = this->model.get_player(id);

	if (buffer.size() < 1) {
		return;
	}

	switch (buffer[0]) {
		case 'a':
			player.speed.x -= 3;
			if (player.speed.x < -max_x_speed) {
				player.speed.x = -max_x_speed;
			}
			break;
			
		case 'd':
			player.speed.x += 3;
			if (player.speed.x > max_x_speed) {
				player.speed.x = max_x_speed;
			}
			break;
		
		case 'w':
			player.speed.y += 1;
			if (player.speed.y > max_y_speed) {
				player.speed.y = max_y_speed;
			}
			break;
		
		case 's':
			player.speed.y -= 1;
			if (player.speed.y < -max_y_speed) {
				player.speed.y = -max_y_speed;
			}
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

	//cout << serialized_model << endl;

	return serialized_model;
}

std::vector<int> wait_list;

void ServerManager::new_player_connected(int player_id) {

	if (this->game_state != waiting) {
		wait_list.push_back(player_id);
		return;
	}

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
