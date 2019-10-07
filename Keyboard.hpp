#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

void keyboard_handler();

class Keyboard
{
	private:
		std::thread kb_thread;
		

	public:
		void init();
		void stop();
		char get_char();
		Keyboard();
		~Keyboard();
	
};
#endif