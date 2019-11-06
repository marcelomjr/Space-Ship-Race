#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client {

private:
	bool* is_running;
	
public:
	void init(bool* is_running);
	void stop();
	void send_char(char character);
	void update_client();
};

#endif