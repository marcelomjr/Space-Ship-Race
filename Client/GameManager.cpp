#include "GameManager.hpp"

int main() {
	string name;
	cout << "Type your name or nickname: " ;
	cin >> name;

	GameManager game_manager;

	game_manager.start(name);

	//while(1);
}
void GameManager::start(string name) {

	this->is_running_flag = true;

	this->socket.init(this, this);
	this->socket.start();

	Keyboard keyboard;

	keyboard.init(this, this);

	this->screen.init(this);

	

	while(this->is_running()) {
		update_screen("string input_buffer");
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

	string place = "1/2";
	float percentage = 23;
	float speed = vel += 1;
	VisualObject player;
	std::vector<VisualObject> map;
	this->screen.racing_screen(place, percentage, speed, player,  map);
}

void GameManager::receiving_handler(string buffer) {

}

void GameManager::keystroke_handler(char key) {
	cout << "typde:" << key << endl;

	if (key == 'q') {
		this->is_running_flag = false;
	}

	// send to key to the server

}