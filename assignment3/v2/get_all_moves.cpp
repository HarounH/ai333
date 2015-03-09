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