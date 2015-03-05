#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

class Game_Player {
public:
	pair<int , int> player_1; //Player 1
	pair<int , int> player_2; //Player 2
	vector< pair<int , int> > wall_H; //Horizontal walls - saved by their centre.
	std::vector< pair<int , int> > wall_V;  //vertical walls - saved by their centre

	void getMove(int& m , int& r , int& c); //Called by client.cpp
	void updateState(int& om , int& or , int& oc); //Called by client.cpp
}