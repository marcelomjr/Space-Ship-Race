#include "ServerManager.hpp"

using namespace std;

int main() {
	ServerManager manager;

	manager.start();
	return 0;
}

void ServerManager::start() {

	Model model;
	ServerSocket server;

	server.init(this, this);
	server.start();

	/*

		// create vector of players
	for (int i = 0; i < 6; i++) {
		float f = (float) i;
	    Player player = {to_string(i), "rocket", {f,f,f}, {f,f,f}};

	    model.add_player(player);  
	  }

	  // create planets
	  for (int i = 0; i < 2; i++) {
	  	float f = (float) i;
	    Planet new_planet = {"type" + to_string(i), {f,f,f}, 4.0};
	    model.add_planet(new_planet);
	  }

	  cout << "4: <<" << model.serialize_model("6") << ">>" << endl << endl;

	  cout << "2: <<" << model.serialize_model("2") << ">>" << endl << endl;;
	  model.remove_player("3");

	  cout << "2: <<" << model.serialize_model("2") << ">>" << endl << endl;;
	  */
	while (1);
}

bool ServerManager::is_running() {

	return true;
	
}
	
	
void ServerManager::receiving_handler(string buffer) {
}

