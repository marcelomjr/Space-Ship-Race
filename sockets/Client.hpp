#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client {

private:
	bool (*command_interface)(char);
	
public:
	void init();
	void stop();
	void send_char(char character);
	void update_client();
};

#endif