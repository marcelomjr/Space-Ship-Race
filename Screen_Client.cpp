#include <ncurses.h>
#include "Screen_Client.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>



/*
//  * Reference: https://invisible-island.net/ncurses/ncurses-intro.html#overview
 */
using namespace std;
void Screen::init() {
	initscr();			       /* Start curses mode 		*/
	raw();				         /* Line buffering disabled	*/
	curs_set(0);           /* Do not display cursor */

	this->max_x = 30;
	this->max_y = 100;

	this->log = "default";
}

void Screen::stop() {
	endwin();
}

void Screen::update(char command) {

	for (int i= 0 ; i < 10; i++) {
		move(i, 0);
		addstr("                                       ");

	}
	
	move(0,0); addstr("Comandos:");
	move(2,0); addstr("w: Aumenta velocidade");
	move(3,0); addstr("s: Reduz velocidade");
	move(4,0); addstr("a: Move para esquerda");
	move(5,0); addstr("d: Move para direita");
	move(6,0); addstr("q: Encerra o jogo");

	
	char typed_command[30];
	sprintf(typed_command, "Comando digitado: [%c].", command);

	move(8,0); 
	//addstr(typed_command);

	refresh();
}

void Screen::log_message(string message) {
	this-> log = message;
}
