#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

void keyboard_handler(bool *is_reading, char* last_pressed_key);

class Keyboard
{
	private:
		std::thread kb_thread;
		bool is_reading;
		char last_pressed_key;
		

	public:
		void init();
		void stop();
		char get_last_pressed_key();
		Keyboard();
		~Keyboard();
	
};
#endif