#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <iostream>
#include "Model.hpp"
#include "ServerSocket.hpp"
#include "../Interfaces.hpp"
#include "../json.hpp"


class ServerManager: public System_Control_Interface, public Input_Handler_Interface
{
public:
	void start();
	bool is_running();
	void receiving_handler(string buffer);
	std::string get_the_updated_model(int player_id);
	void new_player_connected(int player_id);
	void player_desconnected(int player_id);

private:
	Model model;
	GameState game_state;

	// Ignore commands from users
	bool is_input_blocked;
	void create_the_map();
};

#endif