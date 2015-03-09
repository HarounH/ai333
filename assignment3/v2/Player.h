#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;
class Move;
class State;
class Player;

class Move {
	int m,r,c; //Move To/ Place WALL at
	int _pn , _pr , _pc;
	float eval; //Remember the best move.
	Move() {
		m = -1;
		r = -1;
		c = -1;
		eval = -1.0;
	} //Creates an invalid move. Take care of it bro.
	Move() { eval = -1.0; }
};

class State {
	int N,M,K;
	pair<int , int> player_1 , player_2;
	int n_player_1_walls , n_player_2_walls;
	vector< vector<bool> > wall_H;
	vector< vector<bool> > wall_V;
	int present_player;
		void toggle_player() { present_player = ((present_player%2==0)?(1):(2)) ; } //Toggles the player. hurrah.
	
	void init();
	void apply_move(Move m);
	void unapply_move(Move m);

	void get_all_moves(vector<Move> _moves); //Returns all the moves from a given state.
		bool valid_wall( int& _r , int& _c , bool hor ); //Returns if the given wall placement at _r,_c is valid.
	//	bool valid_jump( pair<int,int>& oldpos , pair<int,int>& newpos); //Returns if the given jump from oldpos to newpos is valid or not. get the present player from the State.
	double eval_state();
};

class Player {
	State gbl,loc;
	int player_num;
	float max_total_time;
	float remaining_time;

	Move minimax( int depth , float time_limit );
};

void State::init(int& _N , int& _M , int& _K) {
	N = _N;
	M = _M;
	K = _K;
	wall_H.resize( N+1 );
	wall_V.resize( N+1 );
	for(int _c = 0 ; _c < (M+1) ; ++_c ) {
		wall_H.resize( M+1 );
		wall_V.resize( M+1 );
	}

	present_player = 1;
	n_player_1_walls = K;
	n_player_2_walls = K;
}

#endif