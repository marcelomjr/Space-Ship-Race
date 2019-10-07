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


class Body
{
	private:
		coordinate position;
		coordinate speed;
		 
	public:
		void update(coordinate position, coordinate speed);
		
		coordinate get_position();
		coordinate get_speed();
		
//		Body();
//		~Body();
	
};



class Ship: public Body
{
public:
	void init(coordinate initial_position, coordinate initial_speed);
	double get_model_height();
	double get_model_width();
	std::vector<std::string> get_model();
	
private:
	std::vector<std::string> model;
	double model_height;
	double model_width;
	
	//Ship();
	
	//~Ship();
	
};



#endif