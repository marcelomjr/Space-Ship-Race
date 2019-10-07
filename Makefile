FLAGS = -std=c++11  -pthread -lncurses

run: main.cpp Ship.cpp
	g++  -o game main.cpp Ship.cpp Keyboard.cpp Screen.cpp $(FLAGS)