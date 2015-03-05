#ifndef GAME_PLAYER_CPP
#define GAME_PLAYER_CPP
#include "game_player.h"

//Constructor like things.
Game_Player::Game_Player() {}
Game_Player::~Game_Player() {}
void Game_Player::init(int& _N,int& _M,int& _K, float& _TL , int& _player) {
	N = _N;
	M = _M;
	K = _K;
	max_time = _TL;
	if ( _player == 1) {
		pn = PLAYER_1;
	} else {
		pn = PLAYER_2;
	}
}
//########## END OF CONSTRUCTOR LIKE THINGS.

//I/O Stuff.
void Game_Player::output_move(int& m , int& r , int& c) {
	user_input(m,r,c); //MAKE CHANGES HERE.
}

void Game_Player::user_input(int& m , int& r , int& c) { //Auxillary/Testing ke liye function.
	cin >> m >> r >> c ; //Get the input from the user.
}

void Game_Player::update_state(int& om , int& oro , int& oc , int& _d) {
	d = _d; //Game state.
	if ( d==1 ) {
		//Winnah!
	} else if ( d==2 ) {
		//Losah :(
	} else { //Game continues.
		if ( om == 0 ) {
			other_player.first = oro;
			other_player.second = oc;
		} else if ( om == 1 ) {
			pair<int , int> _temp = make_pair( oro , oc );
			wall_H.push_back(_temp);
		} else {
			pair<int , int> _temp = make_pair( oro , oc );
			wall_V.push_back(_temp);
		}
	}
	//ASSERT : Update complete.
}

//################SANDBOX FOLLOWS############

#endif
