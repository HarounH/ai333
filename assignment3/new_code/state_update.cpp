#ifndef STATE_UPDATE_CPP
#define STATE_UPDATE_CPP
/* functions for creating and modifying states. Also, all the prints. */


void Position::print() {
	cout << "_pos("<<r<<","<<c<<")\n";
}
void Move::print() {
	cout << "Move("<<m<<","<<r<<","<<c<<")"<<"shortpath="<<my_shortest_path<<","<<op_shortest_path<<" from="; from.print(); 
}
void Player::print() {
	cout << "####PLAYER####\n";
	cout << "\tpn="<<pn<<"\n";
	cout << "\twls="<< remaining_walls << "\n";
}
void State::print() {
	/*cout << " Present Player=" << pn << "\n";
	pos_present.print();
	cout << "\n Other Player @"; pos_other.print(); */ //H- toggled this out because annoying
	std::set< pair<int,int> >::iterator it;
	cout << "\n Horizontal walls at: \n";
	for( it=wall_H.begin(); it != wall_H.end(); ++it) {
		cout << "\t("<< (*it).first<<","<< (*it).second <<")\t"; 
	}
	cout << "\n Vertical walls at: \n";
	for( it=wall_V.begin(); it != wall_V.end(); ++it) {
		cout << "\t("<< (*it).first<<","<< (*it).second <<")\t";
	}
}
void State::init(int n, int m , int k , int _mypn) {
	N = n;
	M = m;
	K = k;
	pn = 1;
	mypn = _mypn;
	opn = ((mypn==1)?(2):(1));
	plies = 0;
	n_present_walls = K; n_other_walls = K;
	pos_present = make_pair(1,(M+1)/2);
	pos_other = make_pair(N, (M+1)/2 );

	can_wall_H = std::vector< std::vector<bool> >(N+3 , vector<bool>(M+3,true));
	can_wall_V = std::vector< std::vector<bool> >(N+3 , vector<bool>(M+3,true));  
	is_wall_H = vector<vector<bool> >(N+3, vector<bool>(M+3,false));		// SNair - changed way of declaration
	is_wall_V = vector<vector<bool> >(N+3, vector<bool>(M+3,false));		// H - likes this way of declaration.
	return;
}
State& State::operator=(const State& s) {
	N = s.N; M = s.M; K = s.K; pn = s.pn;
	mypn = s.mypn; opn=s.opn;
	causal_moves = s.causal_moves;
	plies = s.plies;
	pos_present = s.pos_present;
	pos_other = s.pos_other;
	n_present_walls = s.n_present_walls;
	n_other_walls = s.n_other_walls;

	is_wall_H = s.is_wall_H;
	is_wall_V = s.is_wall_V;
	wall_H = s.wall_H;
	wall_V = s.wall_V;
	return *this;
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
	//Doesnt need changes to handle passing.
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
	causal_moves.push(m);
}

void State::unapply_move(Move& m) {
	//Doesn't need changes to handle passing.
	causal_moves.pop(); //Requires that the move played be correct.
	plies--;
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
#endif