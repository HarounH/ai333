#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"

void State::apply_move(Move& mov) { // Assumes that the move is valid.
	if ( mov.m == 0 ) {
		//Change positions.
		if ( mov._pn == 1 ) {
			player_1 = make_pair(r,c);
		} else {
			player_2 = make_pair(r,c);
		}
	} else if ( mov.m == 1 ) {
		//Throw a wall_H into it.
		wall_H[r][c] = true;
	} else if ( mov.m == 2 ) {	
		wall_V[r][c] = true;
	}
	toggle_player();
}

void State::unapply_move(Move& mov) { // Assumes that the move is valid.
	if ( mov.m == 0 ) {
		//Change positions.
		if ( mov._pn == 1 ) {
			player_1 = make_pair(_pr,_pc);
		} else {
			player_2 = make_pair(_pr,_pc);
		}
	} else if ( mov.m == 1 ) {
		//Throw a wall_H into it.
		wall_H[r][c] = false;
	} else if ( mov.m == 2 ) {	
		wall_V[r][c] = false;
	}
	toggle_player();
}

bool State::valid_wall( int& _r , int& _c , bool hor) {
	if ( wall_V[_r][_c] || wall_H[_r][_c] ) {
		return false;
	} //There isnt already a wall there.
	//Avoids segfaults on the +1 side too.
	if (( hor && !wall_H[_r-1][_c] && ( (_r+1) <= N ) && (!wall_H[_r+1][_c] )) || ( (!hor) && !wall_V[_r][_c-1] && ( (_c+1) <= M ) && (!wall_V[_r][_c+1] )) ) {
		return true;
	} else {
		return false;
	}
}
#include "get_all_moves.cpp"
#endif