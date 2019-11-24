FLAGS = -std=c++11  -pthread -lncurses
SOCKET=Server/ServerSocket.cpp
SERVER_MANAGER=Server/ServerManager.cpp
MODEL=Server/Model.cpp

run: $(SERVER_MANAGER) $(MODEL) $(SOCKET)
	g++  -o server $(SERVER_MANAGER) $(MODEL) $(SOCKET) $(FLAGS)
	g++ -o game view.cpp Keyboard.cpp sockets/Client.cpp Screen_Client.cpp $(FLAGS)
	

clean:
	rm game server

add:
	git add *.cpp *.hpp */*.hpp */*.cpp Makefile
	git status
