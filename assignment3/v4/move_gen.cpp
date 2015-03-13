#ifndef MOVE_GEN_CPP
#define MOVE_GEN_CPP

bool State::touchesWall(int r, int c) 		// r,c 1->10
{
	bool flag = false;
	Position p;
	
	p.r = r ; p.c =c;
	if (in_bounds(p)) {flag = (is_wall_H[r][c] and is_wall_V[r][c]);}
	if (flag) return flag;

	p.r = r-1 ; p.c =c;
	if (in_bounds(p)) flag = is_wall_V[r-1][c];
	if (flag) return flag;
	
	p.r = r+1 ; p.c =c;
	if (in_bounds(p)) flag = is_wall_V[r+1][c];
	if (flag) return flag;
	
	p.r = r ; p.c =c-1;
	if (in_bounds(p)) flag = is_wall_H[r][c-1];
	if (flag) return flag;
	
	p.r = r ; p.c =c+1;
	if (in_bounds(p)) flag = is_wall_H[r][c+1];
	return flag;
}

bool State::inLocality(int r, int c) 		// r,c 2->9
{
	int p_r = pos_present.r;
	int p_c = pos_present.c;
	int o_r = pos_other.r;
	int o_c = pos_other.c;
	
	if ((r-p_r)>=-1 and (r-p_r<=2) and (c-p_c)>=-1 and (c-p_c<=2)) return true;
	if ((r-o_r)>=-1 and (r-o_r<=2) and (c-o_c)>=-1 and (c-o_c<=2)) return true;
	
	return (touchesWall(r-1,c-1) or touchesWall(r-1,c) or touchesWall(r-1,c+1) or touchesWall(r,c-1) or touchesWall(r,c+1) or touchesWall(r+1,c-1) or touchesWall(r+1,c) or touchesWall(r+1,c+1));	
}

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
				if ( (plies>50 or inLocality(r,c)) and valid_wall(mov) ) {
					evaluator.eval_move(*this , mov);moves.push_back(mov); 
				
				}
				mov.m = 2;
				if ( (plies>50 or inLocality(r,c)) and valid_wall(mov) ) {
					evaluator.eval_move(*this , mov);moves.push_back(mov); 
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

	// cout << "###########IN GET ALL JUMPS###########\n";
	// mov.from.print(M_PRINT);
	//Upward!
	if ( connected_up(mov.from) ) {
		// cout << "::: connect_up() :::\n";
		
		mov.to = mov.from.up();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		evaluator.eval_move(*this , mov);moves.push_back(mov); 
		
	} else if ( flag ) {
		if ( connected_d_up(mov.from) ) {
			// cout << "::: connect_d_up() :::\n";
			mov.to = mov.from.d_up();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			evaluator.eval_move(*this , mov);moves.push_back(mov); 
			
			flag = false;
		} else {
			if ( connected_up_right(mov.from) ) {
				// cout << "::: connect_up_right() :::\n";
				mov.to = mov.from.up_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				
				flag = false;
			}
			if ( connected_up_left(mov.from) ) {
				// cout << "::: connect_up_left() :::\n";
				mov.to = mov.from.up_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				
				flag = false;
			}
		}
	}


	//Downward!
	if ( connected_down(mov.from) ) {
		// cout << "::: connect_down() :::\n";
		mov.to = mov.from.down();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		evaluator.eval_move(*this , mov);moves.push_back(mov); 
		
	} else if ( flag ) {
		if ( connected_d_down(mov.from) ) {
			// cout << "::: connect_d_down() :::\n";
			mov.to = mov.from.d_down();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			evaluator.eval_move(*this , mov);moves.push_back(mov); 
			
			flag = false;
		} else {
			if ( connected_down_right(mov.from) ) {
				// cout << "::: connect_down_right() :::\n";
				mov.to = mov.from.down_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				
				flag = false;
			}
			if ( connected_down_left(mov.from) ) {
				// cout << "::: connect_down_left() :::\n";
				mov.to = mov.from.down_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 

				flag = false;	
			}
		}
	}

	//Rightward!
	if ( connected_right(mov.from) ) {
		// cout << "::: connect_right() :::\n";
		mov.to = mov.from.right();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		evaluator.eval_move(*this , mov);moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_right(mov.from) ) {
			// cout << "::: connect_d_right() :::\n";
			mov.to = mov.from.d_right();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			evaluator.eval_move(*this , mov);moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_up_right(mov.from) ) {
				// cout << "::: connect_up_right() :::\n";
				mov.to = mov.from.up_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;
			}
			if ( connected_down_right(mov.from) ) {
				// cout << "::: connect_down_right() :::\n";
				mov.to = mov.from.down_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;	
			}
		}
	}

	//Leftward!
	if ( connected_left(mov.from) ) {
		// cout << "::: connect_left() :::\n";
		mov.to = mov.from.left();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		evaluator.eval_move(*this , mov);moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_left(mov.from) ) {
			// cout << "::: connect_d_left() :::\n";
			mov.to = mov.from.d_left();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			evaluator.eval_move(*this , mov);moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_up_left(mov.from) ) {
				// cout << "::: connect_up_left() :::\n";
				mov.to = mov.from.up_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;
			}
			if ( connected_down_left(mov.from) ) {
				// cout << "::: connect_down_left() :::\n";
				mov.to = mov.from.down_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
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
		evaluator.eval_move(*this , mov);moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_up(mov.from) ) {
			mov.to = mov.from.d_up();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			evaluator.eval_move(*this , mov);moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_up_right(mov.from) ) {
				mov.to = mov.from.up_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;
			}
			if ( connected_up_left(mov.from) ) {
				mov.to = mov.from.up_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;	
			}
		}
	}


	//Downward!
	if ( connected_down(mov.from) ) {
		mov.to = mov.from.down();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		evaluator.eval_move(*this , mov);moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_down(mov.from) ) {
			mov.to = mov.from.d_down();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			evaluator.eval_move(*this , mov);moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_down_right(mov.from) ) {
				mov.to = mov.from.down_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;
			}
			if ( connected_down_left(mov.from) ) {
				mov.to = mov.from.down_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;	
			}
		}
	}

	//Rightward!
	if ( connected_right(mov.from) ) {
		mov.to = mov.from.right();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		evaluator.eval_move(*this , mov);moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_right(mov.from) ) {
			mov.to = mov.from.d_right();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			evaluator.eval_move(*this , mov);moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_up_right(mov.from) ) {
				mov.to = mov.from.up_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;
			}
			if ( connected_down_right(mov.from) ) {
				mov.to = mov.from.down_right();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;	
			}
		}
	}

	//Leftward!
	if ( connected_left(mov.from) ) {
		mov.to = mov.from.left();
		mov.r = mov.to.r;
		mov.c = mov.to.c;
		evaluator.eval_move(*this , mov);moves.push_back(mov); 
	} else if ( flag ) {
		if ( connected_d_left(mov.from) ) {
			mov.to = mov.from.d_left();
			mov.r = mov.to.r;
			mov.c=mov.to.c;
			evaluator.eval_move(*this , mov);moves.push_back(mov); 
			flag = false;
		} else {
			if ( connected_up_left(mov.from) ) {
				mov.to = mov.from.up_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
				flag = false;
			}
			if ( connected_down_left(mov.from) ) {
				mov.to = mov.from.down_left();
				mov.r = mov.to.r;
				mov.c=mov.to.c;
				evaluator.eval_move(*this , mov);moves.push_back(mov); 
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
	plies++;
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
	plies--;
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
			bool ans = paths_exists(); //if (!ans){cout << "r,c: " << m.r << "," << m.c << endl; }
			unapply_move(m);
			return ans;
		}
	} else if ( m.m == 2) {
		if ( (m.r==1) || (m.r==N+1) || is_wall_V[m.r-1][m.c] || is_wall_V[m.r+1][m.c] ) {
			return false;
		} else {
			apply_move(m);
			bool ans = paths_exists(); //	if (!ans){cout << "r,c: " << m.r << "," << m.c << endl; };
			unapply_move(m);
			return ans;	
		}
	} else {
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