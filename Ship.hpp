#ifndef SHIP_HPP
#define SHIP_HPP

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
	
	//Ship();
	
	//~Ship();
	
};



#endif