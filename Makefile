FLAGS = -std=c++11  -pthread -lncurses
SOCKET=Server/ServerSocket.cpp
SERVER_MANAGER=Server/ServerManager.cpp
MODEL=Server/Model.cpp
CLIENT_SOCKET=Client/ClientSocket.cpp
GAME_MANAGER=Client/GameManager.cpp
KEYBOARD=Client/Keyboard.cpp
SCREEN=Client/Screen.cpp
PHYSICS=Server/Physics.cpp
RACING_CONTROLLER=Server/RacingController.cpp


server: $(SERVER_MANAGER) $(MODEL) $(SOCKET) $(PHYSICS) $(RACING_CONTROLLER)
	g++  -o server $(SERVER_MANAGER) $(MODEL) $(SOCKET) $(PHYSICS) $(RACING_CONTROLLER) $(FLAGS)	

game: $(GAME_MANAGER) $(CLIENT_SOCKET) $(SCREEN) $(KEYBOARD) 
	g++ -o game $(GAME_MANAGER) $(CLIENT_SOCKET) $(SCREEN) $(KEYBOARD) $(FLAGS)
	

clean:
	rm game server old_game

add:
	git add *.cpp *.hpp */*.hpp */*.cpp Makefile
	git status
