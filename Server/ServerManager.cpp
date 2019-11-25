#include "ServerManager.hpp"

using namespace std;

int main() {
	ServerManager manager;

	manager.start();
	return 0;
}

void ServerManager::start() {

	ServerSocket server;

	server.init(this, this);
	server.start();

	/*

		// create vector of players
	for (int i = 0; i < 6; i++) {
		

/*
	    
	  }

	  // create planets
	  for (int i = 0; i < 2; i++) {
	  	float f = (float) i;
	    Planet new_planet = {"type" + to_string(i), {f,f,f}, 4.0};
	    model.add_planet(new_planet);
	  }

	  cout << "4: <<" << model.serialize_model("6") << ">>" << endl << endl;

	  cout << "2: <<" << model.serialize_model("2") << ">>" << endl << endl;;

	  cout << "2: <<" << model.serialize_model("2") << ">>" << endl << endl;;
	  */
	while (1);
}

bool ServerManager::is_running() {

	return true;
	
}
	
	
void ServerManager::receiving_handler(string buffer) {
	cout << "Received:" << buffer << endl;
}

string ServerManager::get_the_updated_model(int player_id) {

	return this->model.serialize_model(player_id);
}

void ServerManager::new_player_connected(int player_id) {
	cout << "Registrou " << player_id << endl;

	Player player = {player_id, "", {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};

	this->model.add_player(player);
}

void ServerManager::player_desconnected(int player_id) {

	model.remove_player(player_id);
}