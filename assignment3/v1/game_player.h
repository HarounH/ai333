#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

enum PLAYER_NUM { PLAYER_1 = 1 , PLAYER_2 = 2 };

class Game_Player {
public:
	PLAYER_NUM pn; //Stores whether I'm player 1 or player 2.
	int N,M,K; // Length, Width and number of walls.
	int d; //Stores game state in client. (d=3 --> continues) (d=1 --> you win.) (d=2--> you lose.)
	float max_time;
	
	pair<int , int> my_player; //Player 1
	pair<int , int> other_player; //Player 2
	vector< pair<int , int> > wall_H; //Horizontal walls - saved by their centre.
	std::vector< pair<int , int> > wall_V;  //vertical walls - saved by their centre

	//+ AUX DATA.

	Game_Player(); //Does nothing
	void init(int& _N,int& _M , int& _K , float& _TL , int& _player);
	~Game_Player(); //Does Nothing

	void output_move(int& m , int& r , int& c); //Called by client.cpp
		void user_input(int& m , int& r , int& c);

	void idle_state(); //Unimplemented. Future plans are for this to calculate stuff in the background...i.e, do the other player's calculation.
	void update_state(int& om , int& oro , int& oc , int& _d); //Called by client.cpp

};
//################################# END OF CLASS DECLARATION ########################
#endif