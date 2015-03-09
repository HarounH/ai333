#ifndef GAME_PLAYER_CPP
#define GAME_PLAYER_CPP
#include "game_player.h"
#include "graph.cpp"

//Constructor like things.
Game_Player::Game_Player() {}
Game_Player::~Game_Player() {}
void Game_Player::init(int& _N,int& _M,int& _K, float& _TL , int& _player) {
	N = _N;
	M = _M;
	K = _K;
	max_total_time = _TL; //Total time for all given moves. 
	if ( _player == 1) {
		pn = PLAYER_1;
		// Initialize game state.
		gbl_us = make_pair(N,(M/2));
		gbl_them = make_pair(0,(M/2));
	} else {
		pn = PLAYER_2;
		// Initialize game state.
		gbl_us = make_pair(0,(M/2));
		gbl_them = make_pair(N,(M/2));
	}
	my_walls = K;
	other_walls = K;

	gbl_wall_H.resize(0);
	gbl_wall_V.resize(0);
	reset_local_state();
}

//Convenience function for H.
void reset_local_state() {
	/*
	Make copies.
	*/
	loc_us = gbl_us;
	loc_them = gbl_them;
	loc_wall_H = gbl_wall_H;
	loc_wall_V = gbl_wall_V;
	return;
}

//########## END OF CONSTRUCTOR LIKE THINGS.

//I/O Stuff.
void Game_Player::output_move(int& m , int& r , int& c) {
	Move my_move = user_input(); //MAKE CHANGES HERE.
	m = my_move.m;
	r = my_move.r;
	c = my_move.c;
	//And we're done.
	apply_m
}

Move Game_Player::user_input() { //Auxillary/Testing ke liye function.
	Move x;
	cin >> x.m >> x.r >> x.c ; //Get the input from the user.
	return x;
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

double Game_Player::eval_move(Move& move) {
	double f=0.0; //f is the evaluation of the move.

//TODO : Write code here.

	move.eval = f;
	return f;
}

<template Container>
void Game_Player::get_moves( Container& moves ) { //Use as get_moves<Container>

	/*
		Get valid moves of each type, and put it into the Container.
	*/

	//GENERATE JUMPY MOVES

	//ITERATE THROUGH ALL POSSIBLE WALLS. IF WALL EXISTS, IGNORE, ELSE, PUSH INTO THE CONTAINER.

	return;
}
#endif
