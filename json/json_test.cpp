
#include <iostream>
#include <string>
#include "Model.hpp"

using namespace std;

int main() {

  Model model;

  // create vector of players
  for (int i = 0; i < 6; i++) {
    Player player = {to_string(i), "rocket", {i,2*i, 3*i}, {3*i,2,1}};

    model.add_player(player);  
  }

  // create planets
  for (int i = 0; i < 2; i++) {
    Planet new_planet = {"type" + to_string(i), {i,i*i,1}, 4};
    model.add_planet(new_planet);
  }

  cout << "4: <<" << model.serialize_model("6") << ">>" << endl << endl;

  cout << "2: <<" << model.serialize_model("2") << ">>" << endl << endl;;
  model.remove_player("3");

  cout << "2: <<" << model.serialize_model("2") << ">>" << endl << endl;;

  return 0;
}
