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
				if ( /*(plies>50 or inLocality(r,c)) and*/ valid_wall(mov) ) {
					mov.eval = -1;
					apply_move(mov);
					mov.my_shortest_path=shortest_path_Astar(mypn);
					mov.op_shortest_path=shortest_path_Astar(opn);
					causal_moves.pop();
					causal_moves.push(mov);
					if ( mov.my_shortest_path>=0 && mov.op_shortest_path>=0 ) {
						mov.eval = evaluate();
						unapply_move(mov);
						moves.push_back(mov);	
					} else {
						unapply_move(mov);
					}
				
				}
				mov.m = 2;
				if ( /*(plies>50 or inLocality(r,c)) and*/ valid_wall(mov) ) {
					mov.eval = -1;
					apply_move(mov);
					mov.my_shortest_path=shortest_path_Astar(mypn);
					mov.op_shortest_path=shortest_path_Astar(opn);
					causal_moves.pop();
					causal_moves.push(mov);
					if ( mov.my_shortest_path>=0 && mov.op_shortest_path>=0 ) {
						mov.eval = evaluate();
						unapply_move(mov);
						moves.push_back(mov);	
					} else {
						unapply_move(mov);
					}
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

inline double rng() {
	return ((double) fastrand() / (RAND_MAX));
}


void State::get_spiral_walls(std::vector<Move>& moves) {
	Move mov;
	mov.pn = pn;
	mov.from = pos_present;
	bool possible = true;
	std::vector<Position> corners(4);
	int delta = 0;
	#define RD 0
	#define RU 1
	#define LU 2
	#define LD 3
	bool flagRDRU , flagRULU , flagLULD , flagLDRD;
	flagLDRD = flagRULU = flagLULD = flagRDRU = true;
	while(possible) {
		if (this->pos_other.r + delta > N) {
			flagRULU = false;
		}
		if (this->pos_other.r - delta <=0 ) {
			flagLDRD = false;
		}
		if ( this->pos_other.c + delta > M) {
			flagRDRU = false;
		}
		if (this->pos_other.c - delta <= 0) {
			flagLULD = false;
		}
		corners[RD] = Position(this->pos_other.r + delta, this->pos_other.c - delta);
		corners[RU] = Position(this->pos_other.r + delta, this->pos_other.c + delta);
		corners[LU] = Position(this->pos_other.r - delta, this->pos_other.c + delta);
		corners[LD] = Position(this->pos_other.r - delta, this->pos_other.c - delta);
		for(int i=(0 - delta); i<=delta; ++i) {
			if ( flagRULU ) {
				mov.r=this->pos_other.r + delta;
				mov.c=this->pos_other.c + i;
				mov.m=1;
				if ( in_bounds_wall(mov.r,mov.c) && valid_wall(mov) ) {
					moves.push_back(mov);
				}
				mov.m=2;
				if ( in_bounds_wall(mov.r,mov.c) && valid_wall(mov) ) {
					moves.push_back(mov);
				}
			}
			if ( flagLULD ) {
				mov.c=this->pos_other.c - delta;
				mov.r=this->pos_other.r + i;
				mov.m = 1;
				if ( in_bounds_wall(mov.r,mov.c) && valid_wall(mov) ) {
					moves.push_back(mov);
				}
				mov.m=2;
				if ( in_bounds_wall(mov.r,mov.c) && valid_wall(mov) ) {
					moves.push_back(mov);
				}
			}
			if ( flagLDRD ) {
				mov.r=this->pos_other.r - delta;
				mov.c=this->pos_other.c + i;
				mov.m = 1;
				if ( in_bounds_wall(mov.r,mov.c) && valid_wall(mov) ) {
					moves.push_back(mov);
				}
				mov.m=2;
				if ( in_bounds_wall(mov.r,mov.c) && valid_wall(mov) ) {
					moves.push_back(mov);
				}
			}
			if ( flagRDRU ) {
				mov.c=this->pos_other.c + delta;
				mov.r=this->pos_other.r + i;
				mov.m = 1;
				if ( in_bounds_wall(mov.r,mov.c) && valid_wall(mov) ) {
					moves.push_back(mov);
				}
				mov.m=2;
				if ( in_bounds_wall(mov.r,mov.c) && valid_wall(mov) ) {
					moves.push_back(mov);
				}
			}
		}
		delta++;
		possible = flagRDRU && flagLDRD && flagLULD && flagRULU;
	}
	return;
	#undef RD
	#undef RU
	#undef LU
	#undef LD
}



Move State::get_complete_random_wall() {
	Move mov;
	mov.pn = pn;
	mov.from = pos_present;
	bool valid = false;
	int toolong = 0;
	while(!valid) {
		if ( rng() >0.5 ) {mov.m = 1;} else {mov.m = 2;} //vertical v/s horizontal with P = 0.5
		mov.r = 2 + (N-2)*rng(); //goes between 2 -> N-1
		mov.c = 2 + (M-2)*rng();	
					
		valid = in_bounds_wall(mov.r,mov.c)&&valid_wall(mov);/*&&(shortest_path_Astar(1)!=-1)&&(shortest_path_Astar(2)!=-1);*/
		if ( toolong > 100 ) {
			std::vector<Move> v;
			get_spiral_walls(v);
			return v[0]; //TODO : Use a better strategy, man.
		}
		toolong++;
	}
	mov.to = Position(mov.r,mov.c);
	return mov;
}

Move State::get_locality_random_wall() {
	Move mov;
	mov.pn = pn;
	mov.from = pos_present;
	bool valid = false;
	int toolong = 0;
	while(!valid) {
		if ( rng() >0.5 ) {mov.m = 1;} else {mov.m = 2;} //vertical v/s horizontal with P = 0.5
		mov.r = 2 + (N-2)*rng(); //goes between 2 -> N-1
		mov.c = 2 + (M-2)*rng();	
					
		valid = in_bounds_wall(mov.r,mov.c)&&valid_wall(mov)&&inLocality(mov.r,mov.c);/*&&(shortest_path_Astar(1)!=-1)&&(shortest_path_Astar(2)!=-1);*/
		if ( toolong > 100 ) {
			std::vector<Move> v;
			get_spiral_walls(v);
			return v[0]; //TODO : Use a better strategy, man.
		}
		toolong++;
	}
	mov.to = Position(mov.r,mov.c);
	return mov;
}


Move State::get_biased_random_wall() { //with a mean equal to the other players' position. 
	Move mov;
	mov.pn = pn;
	mov.from = pos_present;
	bool valid = false;
	int loopCount = 0;
	// cout << "\t#########presently in biased random wall.\n";
	// cout << "\t######## pn=" << mov.pn << " posp=" << pos_present.r << "," << pos_present.c << ")\n";
	while(!valid) {
		if ( rng() >0.5 ) {mov.m = 1;} else {mov.m = 2;}  //vertical v/s horizontal with P = 0.5
		mov.r = pos_other.r + (N-2)*(rng() - 0.5); //goes between 2 -> N-1
		mov.c = pos_other.c + (M-2)*(rng() - 0.5);	
		
		// if (mov.r <=1) mov.r = 2;
		// if (mov.c <= 1) mov.c = 2;
		// if (mov.r >=N) mov.r = N;
		// if (mov.c >= M) mov.c = M;
		
		valid = in_bounds_wall(mov.r,mov.c)&&valid_wall(mov);/*&&(shortest_path_Astar(1)!=-1)&&(shortest_path_Astar(2)!=-1);*/
		loopCount++;
		if (loopCount==100) {
			// cout << "you've tried hard son, lets get you a random wall.\n";
			return get_complete_random_wall();
		}
	}
	mov.to = Position(mov.r,mov.c);
	return mov;	
}

#endif