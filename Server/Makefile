FLAGS = -std=c++11  -pthread -lncurses
SOCKET=/server/ServerSocket.cpp
SERVER_MANAGER=server/ServerManager.cpp
MODEL=/server/Model.cpp

run: $(SERVER_MANAGER) $(MODEL) $(SOCKET)
	g++  -o server $(SERVER_MANAGER) $(MODEL) $(SOCKET) $(FLAGS)

clean:
	rm server
