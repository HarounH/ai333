#ifndef STATE_QUERY
#define STATE_QUERY
#include "form.h"

/* functions for queries into states */

/* ----add here ----*/
/* validity queries .*/
bool State::valid_wall(Move& m) { //Also calculates the shortest paths. (it does this for bfs anyway. )
	// cout << "###brk1\n";
	if ( is_wall_H[m.r][m.c] || is_wall_V[m.r][m.c] || (!(n_present_walls>0))) { 
		return false;
	}
	// cout << "###brk2\n";
	if (m.m == 1) {
		if ( (m.c==1) || (m.c==M+1) || is_wall_H[m.r][m.c-1] || is_wall_H[m.r][m.c+1] ) {
			return false;
		} else {
			// cout << "###brk3\n";
			apply_move(m);
			// cout << "###brk4\n";
			m.my_shortest_path=shortest_path(mypn);
			// cout << "###brk5\n";
			m.op_shortest_path=shortest_path(opn);
			// cout << "###brk6\n";
			unapply_move(m);
			// cout << "###brk7\n";
			return ((m.op_shortest_path>=0)&&(m.my_shortest_path>=0));
		}
	} else if ( m.m == 2) {
		if ( (m.r==1) || (m.r==N+1) || is_wall_V[m.r-1][m.c] || is_wall_V[m.r+1][m.c] ) {
			return false;
		} else {
			apply_move(m);
			m.my_shortest_path=shortest_path(mypn);
			m.op_shortest_path=shortest_path(opn);
			unapply_move(m);
			return ((m.op_shortest_path>=0)&&(m.my_shortest_path>=0));	
		}
	} else { //Pass or jump.
		return true;
	}
	return false;
}
/* Valid jump thing, it isnt really used. */
bool State::valid_jump(Move& m) {
	if ( m.m != 0 ) { //wall or jump.
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

/* Used for pruning. */
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
	//if ((r-p_r)>=-1 and (r-p_r<=2) and (c-p_c)>=-1 and (c-p_c<=2)) return true;
	//if ((r-o_r)>=-1 and (r-o_r<=2) and (c-o_c)>=-1 and (c-o_c<=2)) return true;
	//return (touchesWall(r-1,c-1) or touchesWall(r-1,c) or touchesWall(r-1,c+1) or touchesWall(r,c-1) or touchesWall(r,c+1) or touchesWall(r+1,c-1) or touchesWall(r+1,c) or touchesWall(r+1,c+1));		
	if ((r-p_r)>=-1 and (r-p_r<=2) and (c-p_c)>=-1 and (c-p_c<=2)) return true;
	if ((r-o_r)>=-1 and (r-o_r<=2) and (c-o_c)>=-1 and (c-o_c<=2)) return true;
	return (touchesWall(r-1,c) or touchesWall(r,c-1) or touchesWall(r,c+1)  or touchesWall(r+1,c) );	
}

/* General queries. */
bool State::is_endgame() { 
	if ( pn==1 ) {
		return ((pos_present.r==N)&&(pos_other.r==1)); 
	} else {
		return ((pos_present.r==1)&&(pos_other.r==N)); 
	}
}

bool State::i_won() {
	if (mypn == pn) {
		if (mypn == 1) return pos_present.r == N;
		else 		   return pos_present.r == 1;
	} else {
		if (mypn == 1) return pos_other.r == N;
		else		   return pos_other.r == 1;
	}
}
bool State::i_lost() {
	if (mypn == pn) {
		if (mypn == 1) return pos_other.r == 1;
		else 		   return pos_other.r == N;
	} else {
		if (mypn == 1) return pos_present.r == 1;
		else		   return pos_present.r == N;
	}
}

bool State::present_won() {
	if (pn==1) { return pos_present.r == N; }
	else { return pos_present.r == 1 ;}
}

bool State::present_lost() {
	if (pn==1) { return pos_other.r == 1; }
	else { return pos_other.r == N ;}
}

bool State::in_bounds(Position& p) {
	return ( (p.r>0)&&(p.r<=N)&&(p.c>0)&&(p.c<=M) );
}

bool State::in_bounds_wall(Position& p) {
	return ( (p.r>1)&&(p.r<=N)&&(p.c>1)&&(p.c<=M) );	
}

bool State::in_bounds(int r, int c) {
	return ( (r>0)&&(r<=N)&&(c>0)&&(c<=M) );
}

bool State::in_bounds_wall(int r , int c) {
	return ( (r>1)&&(r<=N)&&(c>1)&&(c<=M) );	
}

/* Connectivity Follows */
bool State::connected_up(Position& p) { 
	Position to= p.up();
	if ( !in_bounds(to) ) { return false; }
	return (
		(!((pos_other==to)))
		&&  (!wall_up(p))
		);
}
bool State::connected_down(Position& p) { 
	Position to=p.down();
	if ( !in_bounds(to) ) { return false; }
	return (
		(!((pos_other==to)))
		&&  (!wall_down(p))
		); 
}
bool State::connected_right(Position& p) { 
	Position to=p.right();
	if ( !in_bounds(to) ) { return false; }
	return (
		(!((pos_other==to)))
		&&  (!wall_right(p))
		);
}
bool State::connected_left(Position& p) { 
	Position to=p.left();
	if ( !in_bounds(to) ) { return false; }
	return (
		(!((pos_other==to)))
		&&  (!wall_left(p))
		); 
}

//Part 1 Done!.

bool State::connected_d_up(Position& p) { 
	Position to=p.d_up();
	Position bl=p.up();
	if ( !in_bounds(to) ) { return false; }
	return (
		((pos_other==bl))
		&& (!wall_up(p))
		&& (!((pos_other==to)))
		&&  (!wall_d_up(p))
		);
}
bool State::connected_d_down(Position& p) { 
	Position to=p.d_down();
	Position bl=p.down();
	if ( !in_bounds(to) ) { return false; }
	return (
		((pos_other==bl))
		&& (!wall_down(p))
		&& (!((pos_other==to)))
		&&  (!wall_d_down(p))
		);
}
bool State::connected_d_right(Position& p) { 
	Position to=p.d_right();
	Position bl=p.right();
	if ( !in_bounds(to) ) { return false; }
	return (
		((pos_other==bl))
		&& (!wall_right(p))
		&& (!((pos_other==to)))
		&&  (!wall_d_right(p))
		);
}
bool State::connected_d_left(Position& p) { 
	Position to=p.d_left();
	Position bl=p.left();
	if ( !in_bounds(to) ) { return false; }
	return (
		((pos_other==bl))
		&& (!wall_left(p))
		&& (!((pos_other==to)))
		&&  (!wall_d_left(p))
		);
}

//part2 : Done!

bool State::connected_up_right(Position& p) { 
	Position to = p.up_right();
	if ( !in_bounds(to) ) { return false; }
	if (!((pos_other==to))) { //Player doesnt block my destination
		//Destination isn't blocked.
		
		Position up = p.up();
		Position right = p.right();
		if ( pos_other==up ) { //Case1 : Blocked above.
			return (
				(!wall_up(p))
				&& wall_d_up(p)
				&& (!wall_right(up) )
				);
		}
		
		else if ( pos_other==right ) { //Case2 : Blocked to the right.
			return (
				(!wall_right(p))
				&& wall_d_right(p)
				&& (!wall_up(right) )
				);
		} else {
			return false;
		}
	}
	return false;
}

bool State::connected_up_left(Position& p) { 
	Position to = p.up_left();
	if ( !in_bounds(to) ) { return false; }
	if (!((pos_other==to))) { //Player doesnt block my destination
		//Destination isn't blocked.
		
		Position up = p.up();
		Position left = p.left();
		if ( pos_other==up ) { //Case1 : Blocked above.
			return (
				(!wall_up(p))
				&& wall_d_up(p)
				&& (!wall_left(up) )
				);
		}
		
		else if ( pos_other==left ) { //Case2 : Blocked to the right.
			return (
				(!wall_left(p))
				&& wall_d_left(p)
				&& (!wall_up(left) )
				);
		} else {
			return false;
		}
	}
	return false;
}

bool State::connected_down_right(Position& p) { 
	Position to = p.down_right();
	if ( !in_bounds(to) ) { return false; }
	if (!((pos_other==to))) { //Player doesnt block my destination
		//Destination isn't blocked.
		
		Position down = p.down();
		Position right = p.right();
		if ( pos_other==down ) { //Case1 : Blocked above.
			return (
				(!wall_down(p))
				&& wall_d_down(p)
				&& (!wall_right(down) )
				);
		}
		
		else if ( pos_other==right ) { //Case2 : Blocked to the right.
			return (
				(!wall_right(p))
				&& wall_d_right(p)
				&& (!wall_down(right) )
				);
		} else {
			return false;
		}
	}
	return false;
}

bool State::connected_down_left(Position& p) { 
	Position to = p.down_left();
	if ( !in_bounds(to) ) { return false; }
	if (!((pos_other==to))) { //Player doesnt block my destination
		//Destination isn't blocked.
		
		Position down = p.down();
		Position left_l = p.left();
		if ( pos_other==down ) { //Case1 : Blocked above.
			return (
				(!wall_down(p))
				&& wall_d_down(p)
				&& (!wall_left(down) )
				);
		}
		
		else if ( pos_other==left_l ) { //Case2 : Blocked to the right.
			return (
				(!wall_left(p))
				&& wall_d_left(p)
				&& (!wall_down(left_l) )
				);
		} else {
			return false;
		}
	}
	return false;
}
#endif