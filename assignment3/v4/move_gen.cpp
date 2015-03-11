#ifndef MOVE_GEN_CPP
#define MOVE_GEN_CPP

bool State::connected(Position& from, Position& to) {
	//TODO
	return false;
}

void State::toggle_player() {
	pn = ((pn==1)?(2):(0));
	
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
	toggle_player();
}

//VALIDITY STUFF.

bool State::valid_wall(Move& m) {
	if (m.m == 1) {
		
	} else if ( m.m == 2) {

	} else if ( m==0 ) {
		return true;
	}
}

#endif