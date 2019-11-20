
#include <iostream>
#include <string>
#include "serializable.hpp"
#include "Model.hpp"

int main() {
  RelevantData D1(50, 80);
  RelevantData D2(100, 90);
  std::string buffer;

  std::cout << "Originais:\n";
  D1.dump();
  D2.dump();

  buffer = D1.serialize();

  std::cout << "Recuperado:\n";
  D2.unserialize(buffer);

  D2.dump();

  cout << "_____________________" << endl;


  // create vector of players
  /*
  string d;
  for (int i = 0; i < 10; i++) {
    Player player = {to_string(i), "rocket", {1,2, 3}, {3,2,1}};

    this->players_data.push_back(player);
  }
  // create planets
  for (int i = 0; i < 5; i++) {
    Planet new_planet = {"type" + to_string(i), {3,2,1}, 4};
    this->game_map.push_back(new_planet);
  }

  cout << "players: [" << this->players_data[1].player_id << "]" << endl;
*/
  Model model;
  Player p;
  model.add_player(p);
  model.serialize_model("1");

  return 0;
}
