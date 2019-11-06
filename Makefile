FLAGS = -std=c++11  -pthread -lncurses

run: main.cpp Ship.cpp
	g++  -o server main.cpp Ship.cpp Physics.cpp sockets/Server.cpp Screen.cpp $(FLAGS)
	g++ -o game view.cpp Keyboard.cpp sockets/Client.cpp Screen_Client.cpp $(FLAGS)

clean:
	rm game server

add:
	git add *.cpp *.hpp */*.hpp */*.cpp Makefile
	git status