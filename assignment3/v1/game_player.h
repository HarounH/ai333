#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;
#define BIG_FLOAT 100000.0

enum PLAYER_NUM { PLAYER_1 = 1 , PLAYER_2 = 2 };

struct Move {
	int m , r , c ; //Move type, row and column.
	double eval;		//evaluation of the state reached.
	//+AUX DATA
	pair<int , int> us , them;
};

class Graph { //The Graph tells me if two cells are adjacent to each other.

	int N,M;
	//N - M States and booleans connecting them.
	vector< vector< bool > > down_adjacent; //down_adjacent[i][j] tells me if there is a wall just below node  
	vector< vector< bool > > right_adjacent;//right_adjacent[i][j] tells me if there is a wall just to the right of the node.
	Graph(); //Does Nothing.
	void init( int& _N , int& _M ); //Resizes the matrices.

	void apply_move(Move& m); //if the move is of type 1 or 2 , make appropriate changes.
	bool is_adjacent( int& x1, int& y1 , int& x2,int& y2); //Tells me if (x1,y1) - (x2,y2) are adjacent
	bool is_connected( int& x1 , int& y1 , int& x2 , int& y2); //Tells me if they are connected. Does a bfs for this?

};

class Game_Player {
public:
	//Constructor things.
	Game_Player(); //Does nothing

	void init(int& _N,int& _M , int& _K , float& _TL , int& _player); //Take a guess!
	void reset_local_state(); //Sets local state to global state.
	
	~Game_Player(); //Does Nothing

	void idle_state(); //Unimplemented. Future plans are for this to calculate stuff in the background...i.e, do the other player's calculation.
	
	PLAYER_NUM pn; //Stores whether I'm player 1 or player 2.
	int N,M,K; // Length, Width and number of walls.
	int d; //Stores game state in client. (d=3 --> continues) (d=1 --> you win.) (d=2--> you lose.)
	float max_total_time;
	float remaining_time;
	/*
		Game Copy of things
	*/
	pair<int , int> gbl_us , gbl_them;
	int gbl_our_walls, gbl_their_walls;
	std::vector< pair<int , int> > gbl_wall_H , gbl_wall_V; //Horizontal walls - saved by their centre.
	/*
		Local Copy of things - DFS manipulates things.
	*/

	pair<int , int> loc_us , loc_them;
	int loc_our_walls,loc_their_walls;
	std::vector< pair<int , int> > loc_wall_H, loc_wall_V;
	

	/**  ######################
		+AUX DATA
	######################## */


	void output_move(int& m , int& r , int& c); //Called by client.cpp
		Move user_input(int& m , int& r , int& c);

	
	void update_time_left(float tl);
	void update_state_other_player(int& om , int& oro , int& oc , int& _d); //Called by client.cpp

	/*
	Our formulation : 
	Graphs it is.
		Every move is an edge, represented by three integers for completeness, and auxillary data.
		State of the game is the positions and locations of walls.
		However, we also need the graph.
	*/


	/*
		Dealing with edges.
	*/
	<template Container>
	void get_all_valid_moves(Container& _moves); //Puts all valid moves into
	void loc_apply_move(Move& m); //Applies changes to local copy of state.
	void gbl_apply_move(Move& m);

	double eval_state(Move& move);

	Move minimax( int depth = 10 , float tl = BIG_FLOAT ); //Does minimax( alpha-beta, ) with time limit, takes care of minimaxing and shit.
};
//################################# END OF CLASS DECLARATION ########################
#endif