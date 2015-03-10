#ifndef PLAYER_CPP
#define PLAYER_CPP
#include "player.h"
void State::init(int _N , int _M , int_K) {
	N = _N; M=_M; K=_K;
		Position top(1 , ((M+1)/2) );
	player_2 = top;
		top.r = N;
	player_1 = top;

	present_player = 1;
	n_player_2_walls = K; n_player_1_walls = K;

	is_wall_H.resize(N+3); //Extra size to allow for easy life later on.
	is_wall_V.resize(N+3); //Extra size to allow for easy life later on.
	for(int i = 0; i<N+2; ++i) {
		is_wall_V[i].resize(M+3,false); //Extra size to allow for easy life later on.
		is_wall_H[i].resize(M+3,false); //Extra size to allow for easy life later on.
	}
/*	pos_wall_V.resize(0);
	pos_wall_H.resize(0);*/ //Not necessary because sets.
	return;
}
bool is_endgame() { return ( (player_1.r == N)||(player_2.r == 1) ); }

bool valid_wall(Move& m) {
	if ( m.m == 0) { //Not a wall. //########## CORNER CASE 
		return true;
	} else if ( m.m > 2 ){ //########## CORNER CASE 
		return false;
	} else { //wall.
		//################## FUNCTIONING PART OF CODE ###############################
		if ( is_wall_H[m.r][m.c] || is_wall_V[m.r][m.c] ) {
			return false;
		}
		if ( (m.m == 1) && (m.r>=2) && (!is_wall_H[m.r-1][m.c]) && (m.r<=N) && (!is_wall_H[m.r+1][m.c]) ) {
			return true;
		} else if ( (m.m == 2) && (m.c>=2) && (!is_wall_V[m.r][m.c-1]) && (m.c<=M) && (!is_wall_V[m.r][m.c+1])) {
			return true;
		} else {
			return false;
		}
		//##################### END OF FUNCTIONING PART OF CODE####################
	}
	return false; //########### ALL OTHER CASES.
}

bool valid_jump(Move& m) { //Assumes that it is from a valid state.
	//Checking bounds.
	if ( (m._pr <=0) || (m._pc<=0) || (m._pr>N) || (m._pc>M) 
		|| (m.r <=0) || (m.c <= 0) || (m.r >N) || (m.c>M) ) {
		return false;
	}

	if ( present_player == m._pn ) {
		if ( m.m == 0 ) {
			//Case 1 : Plain up move.
			if ( present_player == 1 ) {
				if ( (player_1.r == m._pr) && (player_1.c == m._pc) ) { //Ensure that the move is from the present state.
					//############# FUNCTIONING PART OF CODE #######################

					//12 cases.

					//Case1 : Single Up. Within bounds, no blocking player, no blocking wall.
					if ( (m.r == player_1.r-1) && (player_1.c==m.c) // Jump Up Request?
						&& (player_2.r!=m.r) && (player_2.c!=m.c) 	// Not blocked by player 2.
						&& (!is_wall_H[player_1.r][player_1.c]) && (!is_wall_H[player_1.r][player_1.c+1]) //Not blocked by a wall.
						) {
						return true;
					}

					//Case2 : Single Down. Requested, No Blocking Player, No Blocking Wall.
					if ((m.r == player_1.r+1) && (player_1.c==m.c) // Jump Down Request?
						&& (player_2.r!=m.r) && (player_2.c!=m.c) 	// Not blocked by player 2.
						&& (!is_wall_H[player_1.r+1][player_1.c]) && (!is_wall_H[player_1.r+1][player_1.c+1]) //Not blocked by a wall.
						) {
						return true;
					}

					//Case3 : Single Right. Requested, No Blocking Player , No Blocking Wall.
					if ((m.r == player_1.r) && (player_1.c+1==m.c) // Jump Right Request?
						&& (player_2.r!=m.r) && (player_2.c!=m.c) 	// Not blocked by player 2.
						&& (!is_wall_V[player_1.r][player_1.c+1]) && (!is_wall_V[player_1.r+1][player_1.c+1]) //Not blocked by walls.
						) {
						return true;
					}

					//Case4 : Single Left. Requested, No Blocking Player.
					if ((m.r == player_1.r) && (player_1.c-1==m.c) // Jump Left Request?
						&& (player_2.r!=m.r) && (player_2.c!=m.c) 	// Not blocked by player 2.
						&& (!is_wall_V[player_1.r][player_1.c]) && (!is_wall_V[player_1.r+1][player_1.c]) //Not blocked by walls.
						) {
						return true;
					}

					//Case5 : Double Up. Requested. Player Blocks above. No Walls blocking.
					if ( (( m.r==(player_1.r-2) )) && (m.c==player_1.c)  //Requested.
						&& ( ((player_1.r+1)==player_2.r) ) && (player_1.c==player_2.c)  //Player 2 is blocking aptly.
						&& (!is_wall_H[player_1.r-1][player_1.c]) && (!is_wall_H[player_1.r-1][player_1.c+1]) //No Blocking part1
						&& (!is_wall_H[player_1.r][player_1.c]) && (!is_wall_H[player_1.r][player_1.c+1]) //Not blocked by a wall part2
						) {
						return true;
					}

					//Case6 : Double Down. Requested, Player Blocks Below, No walls blocking.
					if ( (( m.r==(player_1.r+2) )) && (m.c==player_1.c)  //Requested.
						&& ( ((player_1.r-1)==player_2.r) ) && (player_1.c==player_2.c)  //Player 2 is blocking aptly.
						&& (!is_wall_H[player_1.r+2][player_1.c]) && (!is_wall_H[player_1.r+2][player_1.c+1]) //Not blocked by a wall, part1
						&& (!is_wall_H[player_1.r+1][player_1.c]) && (!is_wall_H[player_1.r+1][player_1.c+1]) //Not blocked by a wall part2
						) {
						return true;
					}

					//Case7 : Double RIght. Requested, Player Blocks To The Right, No Walls Blocking.
					if ( (( m.r==(player_1.r) )) && (m.c==(player_1.c+2))  //Requested.
						&& ( ((player_1.r)==player_2.r) ) && ((player_1.c+1)==player_2.c)  //Player 2 is blocking aptly.
						&& (!is_wall_H[player_1.r][player_1.c+2]) && (!is_wall_H[player_1.r+1][player_1.c+2]) //Not blocked by walls. part1.
						&& (!is_wall_V[player_1.r][player_1.c+1]) && (!is_wall_V[player_1.r+1][player_1.c+1]) //Not blocked by walls. part2
						) {
						return true;
					}

					//Case8 : Double left. Requested, Player Blocks To The Left, No Walls Blocking.
					if ( (( m.r==(player_1.r) )) && (m.c==(player_1.c-2))  //Requested.
						&& ( ((player_1.r)==player_2.r) ) && ((player_1.c-1)==player_2.c)  //Player 2 is blocking aptly.
						&& (!is_wall_H[player_1.r][player_1.c-2]) && (!is_wall_H[player_1.r+1][player_1.c-2]) //Not blocked by walls. part1.
						&& (!is_wall_V[player_1.r][player_1.c-1]) && (!is_wall_V[player_1.r+1][player_1.c-1]) //Not blocked by walls. part2
						) {
						return true;
					}


					/*Case9 : Up and right - part1 : from up and part2 : from right. 
						
					*/

					//$$$$$$$$ END OF SINGLE JUMP MOVES. $$$$$$$$$$$$$$$$


					//############# END OF FUNCTIONING CODE ########################
				} else {
					return false;
				}
			} else { //present_player==2.
				//TODO IMPORTANT
			}
		} else { //Wall Stuff.
			return true;
		}
	}
	return false;
}

#include "move_generator.cpp"
#include "minimax.cpp"
#include "eval.cpp"

#endif