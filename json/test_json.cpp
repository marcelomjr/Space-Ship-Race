#include <iostream>
#include "json.hpp"
#include <vector>
#include "../Ship.hpp"

using namespace std;
using json = nlohmann::json;



void add_pessoa(string id, coordinate position, coordinate speed) {
	json j;
	j["position"] = {position.x, position.y, position.z};
	j["speed"] = {speed.x, speed.y, speed.z};
	j["player_id"] = id;

	json t;
	t["outro"] = j;
	cout << t << endl


}
int main() {
	json j;
	j["nome"] = "Marcelo";
	j["idade"] = 25;
	j["matérias"] = {1, 3,5};

	std::vector<int> v;
	v.push_back(10);
	v.push_back(01);
	v.push_back(11);
	v.push_back(00);

	j["notas"] = v;

	std::vector<pessoa> p;

	cout << j << endl;

	cout << "_________________" << endl;

	// create JSON arrays
    json j_no_init_list = json::array();
    json j_empty_init_list = json::array({});
    json j_nonempty_init_list = json::array({1, 2, 3, 4});
    json j_list_of_pairs = json::array({{"position", {1,2,3}}, {"y", 2} });
//    j_list_of_pairs.push_back("player_id", {{"position", {1.0, 3.34, 10.3}}, {"speed", {1.0, 3.34, 10.3}}});

    // serialize the JSON arrays
    std::cout << j_no_init_list << '\n';
    std::cout << j_empty_init_list << '\n';
    std::cout << j_nonempty_init_list << '\n';
    std::cout << j_list_of_pairs << '\n';

	cout << "_________________" << endl;
	coordinate vetor = {1.0, 2.2, 2};
	add_pessoa("23123", vetor, vetor);
	return 0;
}

