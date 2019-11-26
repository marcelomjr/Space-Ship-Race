#include "GameManager.hpp"

int main() {
	string name;
	cout << "Type your name or nickname: " ;
	cin >> name;

	GameManager game_manager;

	game_manager.start(name);

}
void GameManager::start(string name) {

	this->is_running_flag = true;

	this->socket.init(this, this);
	this->socket.start();

	Keyboard keyboard;

	keyboard.init(this, this);

	this->screen.init(this);

	

	while(this->is_running()) {
		
	}

	
	keyboard.stop();
	this->screen.stop();
	this->socket.stop();

	



}

bool GameManager::is_running() {
	return this->is_running_flag;

}

float vel = 0;
void GameManager::update_screen(string input_buffer) {

	json j = json::parse(input_buffer);

	std::vector<ns::VisualObject> map;

	GameState game_state = racing;
	//j.at("game_state").get_to(game_state);




	switch(game_state) {
		case racing:{

			ns::VisualObject player;
			
			j["player"].at("model").get_to(player.model);	
			j["player"]["position"].at("x").get_to(player.position.x);
			j["player"]["position"].at("y").get_to(player.position.y);
			j["player"]["position"].at("z").get_to(player.position.z);

			map.push_back(player);

			// If there is at least one other player
			if (!j["players"][0].is_null()) {
				

				int number_of_opponents = j["players"].size();

				for (int i = 0; i < number_of_opponents; i++) {
					
					ns::VisualObject opponent;
					
					j["players"][i]["position"].at("x").get_to(opponent.position.x);
					j["players"][i]["position"].at("y").get_to(opponent.position.y);
					j["players"][i]["position"].at("z").get_to(opponent.position.z);

					j["players"][i].at("model").get_to(opponent.model);

					map.push_back(opponent);
				}
			}

			// If there is at least one other planet
			if (!j["map"][0].is_null()) {

				int number_of_planets = j["map"].size();

				for (int i = 0; i < number_of_planets; i++) {
					ns::VisualObject planet;
					
					j["map"][i]["position"].at("x").get_to(planet.position.x);
					j["map"][i]["position"].at("x").get_to(planet.position.y);
					j["map"][i]["position"].at("x").get_to(planet.position.z);

					j["map"][i].at("model").get_to(planet.model);

					map.push_back(planet);
				}
			}

			string place;
			//j.at("place").get_to(place);

			float percentage;
			//j.at("completed_percentage").get_to(percentage);

			float speed;
			//j.at("player_speed").get_to(speed);


			this->screen.racing_screen(place, percentage, speed, player, map);
			//racing_screen(string place, float completed_percentage, float player_speed, VisualObject player, vector<VisualObject> map);

			break;

		}
	}


	
}

void GameManager::receiving_handler(int id, string buffer) {

	//cout << buffer << endl;

	this->update_screen(buffer);

}

void GameManager::keystroke_handler(char key) {
	cout << "typde:" << key << endl;

	if (key == 'q') {
		this->is_running_flag = false;
	}
	string buffer(1, key);

	// send to key to the server
	this->socket.send_message(buffer);

}