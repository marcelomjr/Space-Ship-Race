FLAGS = -std=c++11  -pthread

run: main.cpp Ship.cpp
	g++ $(FLAGS) main.cpp Ship.cpp Keyboard.cpp -o game