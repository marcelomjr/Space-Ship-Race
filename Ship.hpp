#ifndef SHIP_HPP
#define SHIP_HPP

#include <vector>
#include <string>

using namespace std;
struct coordinate
{
	double x;
	double y;
	double z;
} typedef coordinate;

typedef std::vector<std::vector<char>> matrix;


class Body
{
	private:
		coordinate position;
		coordinate speed;
		std::vector<std::string> model;
		double max_absolut_x;
		double max_absolut_x_speed;
		double model_height;
		double model_width;
		 
	public:
		void init(coordinate initial_position, coordinate initial_speed);
		void update(coordinate position, coordinate speed);
		coordinate get_position();
		coordinate get_speed();
		double get_model_height();
		double get_model_width();
		std::vector<std::string> get_model();
		std::vector<std::string> get_delete_mask();
		void set_model(std::vector<std::string> new_model, double height, double width);	
};



class Ship: public Body
{
public:
	void init(coordinate initial_position, coordinate initial_speed);
	//Ship();
	
	//~Ship();
	
private:	
};

class Planet: public Body
{
public:
	//Planet();
	//~Planet();
	void init(coordinate initial_position, coordinate initial_speed, int type);
	
};


#endif