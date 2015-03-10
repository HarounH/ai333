#ifndef MOVE_GENERATOR_CPP
#define MOVE_GENERATOR_CPP

#include "valid_move.cpp"

void State::get_all_moves(std::vector<Move>& moves) {
	Move mov;
		mov._pn = present_player;
		mov._pr = pos_present_player.r;
		mov._pc = pos_present_player.c;
		mov.eval = -1.0;	
	//Part1 : 12 Moves.
	mov.m = 0; //Jumps!
	bool flag = true; // This flag tells you if the move related to a double jump has been taken care of.
	//CASE1 : Move UP.
	mov.r = pos_present_player.r - 1;
	mov.c = pos_present_player.c    ;
	if ( valid_jump(mov) ) {
		moves.push_back(mov);
	} else {
		mov.r -= 1;
		if ( flag && valid_jump(mov)) {
			moves.push_back(mov);
			flag = false;
		}
	}
	//CASE2 : Move DOWN.
	mov.r = pos_present_player.r + 1;
	mov.c = pos_present_player.c    ;
	if ( valid_jump(mov) ) {
		moves.push_back(mov);
	} else {
		mov.r += 1;
		if ( flag &&  valid_jump(mov)) {
			moves.push_back(mov);
			flag = false;
		}
	}
	//CASE3 : Move RIGHT.
	mov.r = pos_present_player.r;
	mov.c = pos_present_player.c+1;
	if ( valid_jump(mov) ) {
		moves.push_back(mov);
	} else {
		mov.c += 1;
		if ( flag &&  valid_jump(mov)) {
			moves.push_back(mov);
			flag = false;
		}
	}
	//CASE4 : Move LEFT.
	mov.r = pos_present_player.r;
	mov.c = pos_present_player.c-1;
	if ( valid_jump(mov) ) {
		moves.push_back(mov);
	} else {
		mov.c -= 1;
		if ( flag &&  valid_jump(mov)) {
			moves.push_back(mov);
			flag = false;
		}
	}

	//CASE5 : UP&RIGHT
	
	mov.r = pos_present_player.r-1;
	mov.c = pos_present_player.c+1;
	if ( flag && valid_jump(mov) ) {
		moves.push_back(mov);
		flag = false;
	}
	//CASE6 : UP&LEFT
	mov.r = pos_present_player.r-1;
	mov.c = pos_present_player.c-1;
	if ( flag && valid_jump(mov) ) {
		moves.push_back(mov);
		flag = false;
	}
	//CASE7 : DOWN&RIGHT
	mov.r = pos_present_player.r+1;
	mov.c = pos_present_player.c+1;
	if ( flag && valid_jump(mov) ) {
		moves.push_back(mov);
		flag = false;
	}
	//CASE8 : DOWN&LEFT
	mov.r = pos_present_player.r+1;
	mov.c = pos_present_player.c-1;
	if ( flag && valid_jump(mov) ) {
		moves.push_back(mov);
		flag = false;
	}

	//part2 : Wall moves.
	if ( n_present_player_walls>0 ) {
		for( int _r = 2 ; _r <= N ; ++_r) {
				for( int _c = 2; _c <= M ; ++ _c ) {
					mov.r = _r;
					mov.c = _c;

					//Horizontal Wall.
					mov.m = 1; //Horizontal wall.
					if ( valid_wall( mov ) ) {
						moves.push_back(mov);
					}
					//Vertical Wall.
					mov.m = 2;
					if ( valid_wall( mov ) ) {
						moves.push_back(mov);
					}
	
				}
			}
	}
}
#endif