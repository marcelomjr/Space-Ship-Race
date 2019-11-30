#include "RacingController.hpp"


bool is_player1_ahead(Player player1, Player player2) {

	if (player1.position.y >= player2.position.y) {
		return true;
	}
	return false;

}

std::vector<Player> RacingController::update(std::vector<Player> players, float finish_line, std::vector<string>& results) {

	std::sort(players.begin(), players.end(), is_player1_ahead);

	for (int i = 0; i < players.size(); ++i)
	{
		// Update the place in racing
		players[i].place = i + 1;

		if (players[i].position.y > finish_line) {
			if (players[i].player_state != finished) {
				results.push_back(players[i].name);
				players[i].player_state = finished;
			}
			
		}
	}

	return players;

}