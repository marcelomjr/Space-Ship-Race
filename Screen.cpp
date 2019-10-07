#include <ncurses.h>
#include "Screen.hpp"

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
void Screen::update(int x, int y) {
	
	move(0,0);
	echochar('0');
	move(50, 0);echochar('x');
	move(0, 50);echochar('y');
	
	move(50,50);
	echochar('5');
	
	move(x,y);
	echochar('@');
	
	refresh();
}