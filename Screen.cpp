#include <ncurses.h>
#include "Screen.hpp"
#include <vector>
#include <iostream>


/*
//  * Reference: https://invisible-island.net/ncurses/ncurses-intro.html#overview
 */

void Screen::init() {
	initscr();			       /* Start curses mode 		*/
	raw();				         /* Line buffering disabled	*/
	curs_set(0);           /* Do not display cursor */
}

void Screen::stop() {
	endwin();
}
void Screen::update(Ship ship) {
	
	move(0,0);
	echochar('0');
	move(50, 0);echochar('x');
	move(0, 50);echochar('y');
	
	move(50,50);
	echochar('5');
	
	coordinate pos = ship.get_position();
	//pos.x = 10;
	//pos.y = 10;
	move(pos.x, pos.y);
	
	std::vector<std::string> ship_model = ship.get_model();
	
	//cout << "df" << ship_model.size() << endl;
	
	for (int i = 0; i < ship_model.size(); i++) {
		string row = ship_model[i];
		move(pos.x + i, pos.y);
		
		
		for (int j = 0; j < row.length(); j++) {
			echochar(row[j]);
		}
	}
	
		
	refresh();
}