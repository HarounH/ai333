#ifndef STATE_MOVES
#define STATE_MOVES
/* All functions that return moves from a state (sometimes,given a position.) */

/* Function edite so that the jumps are returned in the up-right-left-down order. */
/* All jumps from a specific starting point. */
void State::get_all_walls( std::vector<Move>& moves ) {
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
					mov.eval = -1;
					apply_move(mov);
					mov.my_shortest_path=shortest_path(mypn);
					mov.op_shortest_path=shortest_path(opn);
					causal_moves.pop();
					causal_moves.push(mov);
//					mov.eval = evaluate();
					unapply_move(mov);
					moves.push_back(mov);
				
				}
				mov.m = 2;
				if ( (plies>50 or inLocality(r,c)) and valid_wall(mov) ) {
					mov.eval = -1;
					apply_move(mov);
					mov.my_shortest_path=shortest_path(mypn);
					mov.op_shortest_path=shortest_path(opn);
					causal_moves.pop();
					causal_moves.push(mov);
//					mov.eval = evaluate();
					unapply_move(mov);

					moves.push_back(mov); 
			}
		}
	}
	return;	
}
void State::get_all_jumps( std::vector<Move>& moves , Position& _from ) {
	Move mov;
		mov.m = 0;
		mov.pn = pn;
		mov.from = _from;

	bool flag = true;
	Position temp=pos_other;
	if (i_lost()) {
		pos_other.r = 0;
		pos_other.c = 0;
	}
	//Upward!
	if ( connected_up(mov.from) ) {
		mov.to = mov.from.up();
		mov.r = mov.to.r;
		mov.c = mov.to.c;

		moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_up(mov.from) ) {
			mov.to = mov.from.d_up();
			mov.r = mov.to.r;
			mov.c=mov.to.c;

			moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_up_right(mov.from) ) {
				mov.to = mov.from.up_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;

				moves.push_back(mov); 
				flag = false;
			}
			if ( connected_up_left(mov.from) ) {
				mov.to = mov.from.up_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;

				moves.push_back(mov); 
				flag = false;	
			}
		}
	}

	//Rightward!
	if ( connected_right(mov.from) ) {
		mov.to = mov.from.right();
		mov.r = mov.to.r;
		mov.c = mov.to.c;

		moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_right(mov.from) ) {
			mov.to = mov.from.d_right();
			mov.r = mov.to.r;
			mov.c=mov.to.c;

			moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_up_right(mov.from) ) {
				mov.to = mov.from.up_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;

				moves.push_back(mov); 
				flag = false;
			}
			if ( connected_down_right(mov.from) ) {
				mov.to = mov.from.down_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;

				moves.push_back(mov); 
				flag = false;	
			}
		}
	}

	//Leftward!
	if ( connected_left(mov.from) ) {
		mov.to = mov.from.left();
		mov.r = mov.to.r;
		mov.c = mov.to.c;

		moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_left(mov.from) ) {
			mov.to = mov.from.d_left();
			mov.r = mov.to.r;
			mov.c=mov.to.c;

			moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_up_left(mov.from) ) {
				mov.to = mov.from.up_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;

				moves.push_back(mov); 
				flag = false;
			}
			if ( connected_down_left(mov.from) ) {
				mov.to = mov.from.down_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;

				moves.push_back(mov); 
				flag = false;	
			}
		}
	}

	//Downward!
	if ( connected_down(mov.from) ) {
		mov.to = mov.from.down();
		mov.r = mov.to.r;
		mov.c = mov.to.c;

		moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_down(mov.from) ) {
			mov.to = mov.from.d_down();
			mov.r = mov.to.r;
			mov.c=mov.to.c;

			moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_down_right(mov.from) ) {
				mov.to = mov.from.down_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;

				moves.push_back(mov); 
				flag = false;
			}
			if ( connected_down_left(mov.from) ) {
				mov.to = mov.from.down_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;

				moves.push_back(mov); 
				flag = false;	
			}
		}
	}
	pos_other = temp;
	return;
}

/* All jumps for present */
void State::get_all_jumps(std::vector<Move>& mov) {
	if (present_won()) { //He can pass.
		//cout << "hi, present won \n";
		Move pas;
		pas.from = pos_present;
		pas.m = 0; pas.r=0; pas.c=0; pas.to=pas.from;
		mov.push_back(pas);
		return; 
	}
	else {
		get_all_jumps(mov , pos_present);
		return;
	}
}
#endif