#ifndef MOVE_GEN_CPP
#define MOVE_GEN_CPP

void State::get_all_walls(std::vector<Move>& moves) {
		Move mov;
		mov.pn = pn;
		mov.from = pos_present;
	for( int r = 2; r<=N; r++) {
		for(int c=2; c<=M; c++) {
			mov.to = make_pair(r,c);
			mov.r = r;
			mov.c = c;

			mov.m = 1;
			if ( valid_wall(mov) ) {
				moves.push_back(mov);
			}
			mov.m = 2;
			if ( valid_wall(mov) ) {
				moves.push_back(mov);
			}
		}
	}
	return;
}

void State::get_all_jumps(std::vector<Move>& moves) {
	Move mov;
		mov.m = 0;
		mov.pn = pn;
		mov.from = pos_present;

	bool flag = true;

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
	return;
}


void State::get_all_jumps( std::vector<Move>& moves , Position& _from ) {
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
	return;
}

bool State::connected(Position& from, Position& to) {
	//TODO
	return false;
}

void State::toggle_player() {
	pn = ((pn==1)?(2):(1));
	
	Position temp;
	temp = pos_present;
	pos_present = pos_other;
	pos_other = temp;

	int n_wall_t;
	n_wall_t = n_present_walls;
	n_present_walls = n_other_walls;
	n_other_walls = n_wall_t;
	return;
}

void State::apply_move(Move& m) { //assumes that the move is valid
	if ( m.m==0 ) {
		pos_present = m.to;
	} else if ( m.m==1 ) {
		n_present_walls--;
		is_wall_H[m.r][m.c] = true;
		wall_H.insert( make_pair(m.r,m.c) );
	} else if ( m.m==2 ) {
		n_present_walls--;
		is_wall_V[m.r][m.c] = true;
		wall_V.insert( make_pair(m.r,m.c) );
	}
	toggle_player();
}

void State::unapply_move(Move& m) {
	toggle_player();						// SNair - moved toggle up
	if ( m.m==0 ) {
		pos_present = m.from;
	} else if ( m.m==1 ) {
		n_present_walls++;
		is_wall_H[m.r][m.c] = false;
		wall_H.erase( make_pair(m.r,m.c) );
	} else if ( m.m==2 ) {
		n_present_walls++;
		is_wall_V[m.r][m.c] = false;
		wall_V.erase( make_pair(m.r,m.c) );
	}
}

//VALIDITY STUFF.

bool State::valid_wall(Move& m) {
	if ( is_wall_H[m.r][m.c] || is_wall_V[m.r][m.c] || (!(n_present_walls>0))) { 
		return false;
	}

	if (m.m == 1) {
		if ( (m.c==1) || (m.c==M+1) || is_wall_H[m.r][m.c-1] || is_wall_H[m.r][m.c+1] ) {
			return false;
		} else {
			apply_move(m);
			bool ans = paths_exists(); if (!ans){cout << "r,c: " << m.r << "," << m.c << endl; }
			unapply_move(m);
			return ans;
		}
	} else if ( m.m == 2) {
		if ( (m.r==1) || (m.r==N+1) || is_wall_V[m.r-1][m.c] || is_wall_V[m.r+1][m.c] ) {
			return false;
		} else {
			apply_move(m);
			bool ans = paths_exists(); 	if (!ans){cout << "r,c: " << m.r << "," << m.c << endl; };
			unapply_move(m);
			return ans;	
		}
	} else if ( m.m==0 ) {
		return true;
	}
	return false;
}

bool State::valid_jump(Move& m) {
	if ( m.m != 0 ) {
		return true;
	} else { //All those cases.
		if ( pos_present == m.from ) {
			if ( m.to.is_up(m.from) ) {
				return connected_up(m.from);
			} else if ( m.to.is_down(m.from)) {
				return connected_down(m.from);
			} else if ( m.to.is_right(m.from)) {
				return connected_right(m.from);
			} else if ( m.to.is_left(m.from)) {
				return connected_left(m.from);
			} else if ( m.to.is_d_up(m.from)) {
				return connected_d_up(m.from);
			} else if ( m.to.is_d_down(m.from)) {
				return connected_d_down(m.from);
			} else if ( m.to.is_d_right(m.from)) {
				return connected_d_right(m.from);
			} else if ( m.to.is_d_left(m.from)) {
				return connected_d_left(m.from);
			} else if ( m.to.is_up_right(m.from)) {
				return connected_up_right(m.from);
			} else if ( m.to.is_up_left(m.from)) {
				return connected_up_left(m.from);
			} else if ( m.to.is_down_right(m.from)) {
				return connected_down_right(m.from);
			} else if ( m.to.is_down_left(m.from)) {
				return connected_down_left(m.from);
			}
		} else {
			return false;
		}
	}
	return false;
}
#endif