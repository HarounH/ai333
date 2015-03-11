#ifndef MISC_CPP
#define MISC_CPP

void terminal_input(int& m , int& r, int& c) {cin >> m >> r >> c; }
//ACTIVELY ALTER THIS FOR OUR AI.
void Player::send_move_to_client_cpp(int& m , int& r , int& c) {
	
	if ( MOVE_PRINTORNOTTOPRINT ) {
		vector<Move> moves;
		locState.get_all_moves(moves);
		for(int i=0; i<moves.size(); ++i) moves[i].print();
	}

	Move res;
	terminal_input(m,r,c);
	//Preserve.
		res.m = m;
		res.r = r;
		res.c = c;	
		res._pn = gblState.present_player;
		res._pr = gblState.pos_present_player.r;
		res._pc = gblState.pos_present_player.c;
		res.eval = -1.0;
	gblState.apply_move(res);
	locState.apply_move(res);

	gblState.print(STATE_PRINTORNOTTOPRINT);
	return;
}

void Player::read_time_left_from_client_cpp(float _t) {
	remaining_time = _t;
}

void Player::read_move_from_client_cpp(int& m ,int& r, int& c) {
	Move res;
		res.m = m;
		res.r = r;
		res.c = c;
		res._pn = gblState.present_player;
		res._pr = gblState.pos_present_player.r;
		res._pc = gblState.pos_present_player.c;
		res.eval = -1.0;
	gblState.apply_move(res);
	locState.apply_move(res);

	gblState.print(STATE_PRINTORNOTTOPRINT);
	return;
}


//STUFF!
void State::print( bool shouldiprint ) {
	if ( !shouldiprint ) {
		return;
	}

	cout << "\n##################\nPrinting State:\n";
	cout << "Player_1 : \n \twalls_left="<<n_player_1_walls<<" "; player_1.print();
	cout << "Player_2 : \n \twalls_left="<<n_player_2_walls<<" "; player_2.print();
	cout << "Present_player is player=" << present_player << " has walls left="<< n_present_player_walls <<"\n"; pos_present_player.print();
	//Now to print walls.

	std::set< pair<int,int> >::iterator it;
	
	cout << "\n Horizontal walls at: \n";
	for( it=pos_wall_H.begin(); it != pos_wall_H.end(); ++it) {
		cout << "Horizontal::: \t\t("<< (*it).first<<","<< (*it).second <<")\n"; 
	}
	cout << "\n Vertical walls at: \n";
	for( it=pos_wall_V.begin(); it != pos_wall_V.end(); ++it) {
		cout << "Vertical:::::\t\t("<< (*it).first<<","<< (*it).second <<")\n"; 
	}

	cout << " Printing is_wall_H ... NOTE: ITS ONLY THE CENTRES OF THE WALLS \n";
	for(int r=1; r<=N; ++r) {
		for(int c=1; c<=M; ++c) {
			cout << is_wall_H[r][c] << " ";
		}
		cout << "\n";
	}

	cout << " Printing is_wall_V ... NOTE: ITS ONLY THE CENTRES OF THE WALLS \n";
	for(int r=1; r<=N; ++r) {
		for(int c=1; c<=M; ++c) {
			cout << is_wall_V[r][c] << " ";
		}
		cout << "\n";
	}
	cout << "End of state printing \n";
}

void State::apply_move(Move& mov) { //Assumes that the move is valid.
	if (mov._pn == 1) {
		if(mov.m == 0) {
			player_1.r = mov.r;
			player_1.c = mov.c;
		} else if ( mov.m == 1) {
			n_player_1_walls--;
			is_wall_H[mov.r][mov.c] = true;
			pos_wall_H.insert( make_pair(mov.r,mov.c) );
		} else {
			n_player_1_walls--;
			is_wall_V[mov.r][mov.c] = true;
			pos_wall_V.insert( make_pair(mov.r,mov.c) );
		}
	} else if (mov._pn == 2) {
		if(mov.m == 0) {
			player_2.r = mov.r;
			player_2.c = mov.c;
		} else if ( mov.m == 1) {
			n_player_2_walls--;
			is_wall_H[mov.r][mov.c] = true;
			pos_wall_H.insert( make_pair(mov.r,mov.c) );
		} else {
			n_player_2_walls--;
			is_wall_V[mov.r][mov.c] = true;
			pos_wall_V.insert( make_pair(mov.r,mov.c) );
		}
	}

	//Insert other stuff here.

	toggle_player();
}

void State::unapply_move(Move& mov) { //Assumes that the move is valid.
	if (mov._pn == 1) {
		if(mov.m == 0) {
			player_1.r = mov._pr;
			player_1.c = mov._pc;
		} else if ( mov.m == 1) {
			n_player_1_walls++;
			is_wall_H[mov.r][mov.c] = false;
			pos_wall_H.erase( make_pair(mov.r,mov.c) );
		} else {
			n_player_1_walls++;
			is_wall_V[mov.r][mov.c] = false;
			pos_wall_V.erase( make_pair(mov.r,mov.c) );
		}
	} else if (mov._pn == 2) {
		if(mov.m == 0) {
			player_2.r = mov._pr;
			player_2.c = mov._pc;
		} else if ( mov.m == 1) {
			n_player_2_walls++;
			is_wall_H[mov.r][mov.c] = false;
			pos_wall_H.erase( make_pair(mov.r,mov.c) );
		} else {
			n_player_2_walls++;
			is_wall_V[mov.r][mov.c] = false;
			pos_wall_V.erase( make_pair(mov.r,mov.c) );
		}
	}
	//Insert other stuff here.
	toggle_player();
}


void State::init(int _N , int _M , int _K) {
	N = _N; M=_M; K=_K;
	

		Position top(1 , ((M+1)/2) );
	player_1 = top;
		top.r = N;
	player_2 = top; //Now bottom. dw.
	n_player_2_walls = K; n_player_1_walls = K;
	

	present_player = 1;
	pos_present_player.r = player_1.r;
	pos_present_player.c = player_1.c;
	n_present_player_walls = n_player_1_walls;


	is_wall_H.resize(N+3); //Extra size to allow for easy life later on.
	is_wall_V.resize(N+3); //Extra size to allow for easy life later on.
	
	for(int i = 0; i<N+2; ++i) {
		is_wall_V[i].resize(M+3,false); //Extra size to allow for easy life later on.
		is_wall_H[i].resize(M+3,false); //Extra size to allow for easy life later on.
	}

/*	pos_wall_V.resize(0);
	pos_wall_H.resize(0);*/ //Not necessary because sets.

	return;
}

void Player::init( int _N , int _M , int _K , int _pn , float max_time ) {
	player_num = _pn;
	max_total_time = max_time;
	remaining_time = max_time;
	walls_left = _K;
	gblState.init(_N,_M,_K);
	locState.init(_N,_M,_K);
	return;
}

State& State::operator=(const State& s) {
	N = s.N; M = s.M; K = s.K;
	
	player_1.r = s.player_1.r;
	player_1.c = s.player_1.c;
	player_2.r = s.player_2.r;
	player_2.c = s.player_2.c;
	pos_present_player.r = s.pos_present_player.r;
	pos_present_player.c = s.pos_present_player.c;

	n_player_1_walls = s.n_player_1_walls;
	n_player_2_walls = s.n_player_2_walls;
	n_present_player_walls = s.n_present_player_walls;

	is_wall_H = s.is_wall_H;
	is_wall_V = s.is_wall_V;
	pos_wall_H = s.pos_wall_H;
	pos_wall_V = s.pos_wall_V;

	return *this;
}
#endif