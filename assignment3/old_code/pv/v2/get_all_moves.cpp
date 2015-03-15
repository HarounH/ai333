#ifndef GET_ALL_MOVES_CPP
#define GET_ALL_MOVES_CPP

void State::get_all_moves(vector<Move>& moves) { //Assumes that the vector has been resized.
	//Write code to generate all moves.
	
	Move mov;
		mov._pn = present_player;
		mov.m = 0;
	if ( present_player == 1 ) {
		mov._pr = player_1.first;
		mov._pc = player_1.second;
		int nr,nc; // the 'n' prefix is for "No_reason" - nerdy/geeky jokes hurrah!
			nr = player_1.first;
			nc = player_1.second;
		//PART 1 ::::::::::: GET JUMPY MOVES.
		// c+1 Move.
			//No other player at given spot, and no wall between me and that new spot.
		if ( nc+1 < M ) {
			if ( (player_2.first == nr) && (player_2.second == nc+1) ) { //Player blocks
				//Try to jump.
				//Try to jump to nc+2, if thats possible, then great! , else, jump left and right if those are blocked, try nr-1 and nr+1 
			} else if ( !wall_V[][] ) { //Wall blocks.
				//Do Nothing about this.
			} else { //Player doesnt block, wall doesn't block, 
				mov.r = nr;
				mov.c = nc+1
				mov.m=0;
				moves.push_back(mov);
			}
		}
		// c-1 Move.
		// r+1 Move.
		// r-1 Move.
		
		//PART 2 :::::::::: PLACE WALLS.
		if ( n_player_1_walls > 0 ) { //Check if he CAN place walls.
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