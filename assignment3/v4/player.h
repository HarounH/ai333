#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;
/*
(1,1) is the top left corner.
Player 1 is at the top.
Player 2 is at the bottom.
*/

//Change this definition to toggle state printing.
#define STATE_PRINTORNOTTOPRINT true
#define MOVE_PRINTORNOTTOPRINT true
//class Position replaces pair<int,int> FOR PLAYER ALONE. . Makes life easier.
class Position {
public:
	int r,c;
	Position() { r=0; c=0; }
	~Position() {} //Default destructor.
	Position(int _r , int _c) { r = _r ; c = _c; }
	Position( pair<int,int> x ) { r=x.first ; c=x.second; }
	Position& operator=(const pair<int,int>& _p) { r = _p.first; c = _p.second; return *this; }	
	Position& operator=(const Position& _p) { r = _p.r; c = _p.c; return *this; }
	//Position& operator-(Position& _p) { r = _p.r; c = _p.c; return *this; }
	bool operator==(const pair<int,int>& _p) { return ((this->r == _p.first) && (this->c == _p.second)); }
	bool operator==(const Position& _p) { return ((this->r == _p.r) && (this->c == _p.c)); }
	Position up() { Position p(r-1 , c); return p; }
	Position down() { Position p(r+1 , c); return p; }
	Position right() { Position p(r , c+1); return p; }
	Position left() { Position p(r , c-1); return p; }

	void print() { cout << "PosPrint: \t (" << r << "," << c << ")...\n"; }
}; //That should allow easy conversion between pair<int,int> and Position.

class Move {
public:
	int m,r,c; //Move TO
	int _pn , _pr , _pc; //Move FROM
	float eval;

	Move& operator=(const Move& _m) { m=_m.m; r=_m.r; c=_m.c; _pn=_m._pn; _pr=_m._pr; _pc=_m._pc; eval=_m.eval; return *this;}
	void print() { cout << "\tMovePrint (m,r,c)="<<m<<","<<r<<","<<c<<")\t (_pn,_pr,_pc,eval)="<<_pn<<","<<_pr<<","<<_pc<<","<<eval<<")...\n" ;}
};

class State {
public:
	int N,M,K;

	Position player_1 , player_2;
	int n_player_1_walls , n_player_2_walls;
	
	int present_player;
	Position pos_present_player;
	int n_present_player_walls;


	vector< vector <bool> > is_wall_H , is_wall_V; // is_wall_H tells me if there's a wall at [r][c] ((2<=r<=N+1) && (2<=c<=M+1))
	std::set< pair<int,int> > pos_wall_H , pos_wall_V; //Slower inserts, but faster removals. 2*log(K) v/s (1 + K )...

	State() {} //Default
	~State() {} //Default.
	void print(bool shouldiprint);
	State& operator=(const State& s);

	void init(int _N, int _M , int _K);
	void toggle_player() { 
		present_player = ((present_player%2==0)?(1):(2)) ; 
		if ( present_player == 1 ) {
			pos_present_player.r = player_1.r;
			pos_present_player.c = player_1.c;
			n_present_player_walls = n_player_1_walls;
		} else {
			pos_present_player.r = player_2.r;
			pos_present_player.c = player_2.c;
			n_present_player_walls = n_player_2_walls;
		}
	} //Toggles the player. hurrah.
	
	/* THINGS RELATED TO MOVES. */
	bool valid_jump(Move& m);
	bool valid_wall(Move& m);
	bool valid_move(Move& m);

	void apply_move(Move& m);
	void unapply_move(Move &m);

	/* THINGS RELATED TO STATE */
	bool is_endgame();

	/* THINGS FOR THE PLAYER */
	void get_all_moves(vector<Move>& moves);
};

class Player {
public:
	State gblState,locState;
	int player_num;
	float max_total_time;
	float remaining_time;
	int walls_left;


	Move best_move;

	
	/* FOR INTERACTION WITH CLIENT_CPP */
	void init( int _N , int _M , int _K , int _pn , float max_time );
	void read_time_left_from_client_cpp(float _t);
	void send_move_to_client_cpp(int& m , int& r , int& c);
	void read_move_from_client_cpp(int& m ,int& r, int& c);

	/* FOR MINIMAX? */

	
/*	Move minimax( int depth , float time_limit );
		int max_value(double alpha, double beta, int cutoff, int curDepth, float time_limit);
		int min_value(double alpha, double beta, int cutoff, int curDepth, float time_limit);
*/

};
#endif