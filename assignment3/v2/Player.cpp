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

void State::get_all_moves(vector<Move>& moves) { //Assumes that the vector has been resized.
	//Write code to generate all moves.
	
	Move mov;
		mov._pn = present_player;
		mov.m = 0;
	if ( present_player == 1 ) {
		mov._pr = player_1.first;
		mov._pc = player_1.second;
		int nr,nc;
			nr = player_1.first;
			nc = player_1.second;
		//PART 1 ::::::::::: GET JUMPY MOVES.
		// y+1 Move.
			//No other player at given spot, and no wall between me and that new spot.
		if 
		// y-1 Move.
		// x+1 Move.
		// x-1 Move.
		
		//PART 2 :::::::::: PLACE WALLS.
		if ( n_player_1_walls > 0 ) { //Check if he CAN place walls.
			for( int _r = 2 ; _r <= N ; ++_r) {
				for( int _c = 2; _c <= M ; ++ _c ) {
					//Horizontal Wall.
					if ( valid_wall( _r , _c , true ) ) {
						mov.m = 1; //Horizontal wall.
						mov.r = _r;
						mov.c = _c;
						moves.push_back(mov);
					}
					//Vertical Wall.
					if ( valid_wall( _r , _ c , false) ) {
						mov.m = 2; //vertical wall.
						mov.r = _r;
						mov.c = _c;
						moves.push_back(mov);	
					}

				}
			}
		}

	} else { //Player_2's moves.
		mov._pr = player_2.first;
		mov._pc = player_2.second;
		int nr,nc;
			nr = player_2.first;
			nc = player_2.second;
	}
}


#endif