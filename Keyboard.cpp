#include <iostream>
#include <thread>
#include "Keyboard.hpp"

using namespace std;


void keyboard_handler() {
	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "estou na Keyboard_handler" << endl;	
	}
}



Keyboard::Keyboard() {}

Keyboard::~Keyboard() {}

void Keyboard::init() {
  // std::thread name() Accepts as parameters 1. callable function 2. args list
  std::thread keyboard_thread(keyboard_handler);

  // Save the thread reference before return from this function
  (this->kb_thread).swap(keyboard_thread);

}


void Keyboard::stop() {

  this->kb_thread.join();
}

char Keyboard::get_char() {
  
  return 'c';
}