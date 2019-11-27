#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include <string>
using namespace std;

struct Coordinate
{
	float x;
	float y;
	float z;
};

// a simple struct to model a person
struct VisualObject
{
	Coordinate position;
	string model;
};

enum GameState
{
	waiting,
	racing,
	game_over
};

enum PlayerState
{
	active,
	inactive,
	collided,
	finished

};

class System_Control_Interface
{
public:
	virtual bool is_running() = 0;
	virtual string get_the_updated_model(int player_id) = 0;
	virtual void new_player_connected(int player_id) = 0;
	virtual void player_desconnected(int player_id) = 0;
	virtual bool is_socket_active() = 0;

	//virtual void stop_game();
	
};
class Input_Handler_Interface
{
public:
	virtual void receiving_handler(int id, string buffer) = 0;
	
};

class GameManagerInterface
{
public:
	virtual bool is_running() = 0;
	
	
};

class KeyboardInterface
{
public:
	virtual void keystroke_handler(char key) = 0;
	
};



#endif