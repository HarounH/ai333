#ifndef STATE_MOVES_STACK_CPP
#define STATE_MOVES_STACK_CPP
#endif
void State::get_all_walls_stack( std::stack<Move>& moves ) {
	Move mov;
	mov.pn = pn;
	mov.from = pos_present;
	for( int r = 2; r<=N; r++) {
		for(int c=2; c<=M; c++) {
				mov.to = make_pair(r,c);
				mov.r = r;
				mov.c = c;

				mov.m = 1;
				if ( (plies>50 or inLocality(r,c)) and valid_wall(mov) ) {
					moves.push(mov);
				
				}
				mov.m = 2;
				if ( (plies>50 or inLocality(r,c)) and valid_wall(mov) ) {
					moves.push(mov); 
			}
		}
	}
	return;	
}
void State::get_all_jumps_stack( std::stack<Move>& moves , Position& _from ) {
	Move mov;
		mov.m = 0;
		mov.pn = pn;
		mov.from = _from;

	bool flag = true;

	//Upward!
	if ( connected_up(mov.from) ) {
		mov.to = mov.from.up();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		moves.push(mov); 
	} else if ( flag ) {
		if ( connected_d_up(mov.from) ) {
			mov.to = mov.from.d_up();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			moves.push(mov); 
			flag = false;
		} else {
			if ( connected_up_right(mov.from) ) {
				mov.to = mov.from.up_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				moves.push(mov); 
				flag = false;
			}
			if ( connected_up_left(mov.from) ) {
				mov.to = mov.from.up_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				moves.push(mov); 
				flag = false;	
			}
		}
	}


	//Downward!
	if ( connected_down(mov.from) ) {
		mov.to = mov.from.down();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		moves.push(mov); 
	} else if ( flag ) {
		if ( connected_d_down(mov.from) ) {
			mov.to = mov.from.d_down();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			moves.push(mov); 
			flag = false;
		} else {
			if ( connected_down_right(mov.from) ) {
				mov.to = mov.from.down_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				moves.push(mov); 
				flag = false;
			}
			if ( connected_down_left(mov.from) ) {
				mov.to = mov.from.down_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				moves.push(mov); 
				flag = false;	
			}
		}
	}

	//Rightward!
	if ( connected_right(mov.from) ) {
		mov.to = mov.from.right();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		moves.push(mov); 
	} else if ( flag ) {
		if ( connected_d_right(mov.from) ) {
			mov.to = mov.from.d_right();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			moves.push(mov); 
			flag = false;
		} else {
			if ( connected_up_right(mov.from) ) {
				mov.to = mov.from.up_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				moves.push(mov); 
				flag = false;
			}
			if ( connected_down_right(mov.from) ) {
				mov.to = mov.from.down_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				moves.push(mov); 
				flag = false;	
			}
		}
	}

	//Leftward!
	if ( connected_left(mov.from) ) {
		mov.to = mov.from.left();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		moves.push(mov); 
	} else if ( flag ) {
		if ( connected_d_left(mov.from) ) {
			mov.to = mov.from.d_left();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			moves.push(mov); 
			flag = false;
		} else {
			if ( connected_up_left(mov.from) ) {
				mov.to = mov.from.up_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				moves.push(mov); 
				flag = false;
			}
			if ( connected_down_left(mov.from) ) {
				mov.to = mov.from.down_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				moves.push(mov); 
				flag = false;	
			}
		}
	}
	return;
}

/* All jumps for present */
void State::get_all_jumps_stack(std::stack<Move>& mov) {
	
	if (present_won()) { //He can pass.
		Move pas;
		pas.from = pos_present;
		pas.m = 0; pas.r=0; pas.c=0; pas.to=pas.from;
		mov.push(pas);
		return; 
	}
	else {
		get_all_jumps_stack(mov , pos_present);
		return;
	}
}