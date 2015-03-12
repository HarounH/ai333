#ifndef COMMUNICATIONS_CPP
#define COMMUNICATIONS_CPP

void terminal_input(int& m , int& r, int& c) {cin >> m >> r >> c; }
//ACTIVELY ALTER THIS FOR OUR AI.
void Player::send_move_to_client_cpp(int& m , int& r , int& c) {
	
	if ( M_PRINT ) {
		cout << "-----------------------\n";
		vector<Move> moves;
		//locState.get_all_walls(moves);
		locState.get_all_jumps(moves);
		for(int i=0; i<moves.size(); ++i) moves[i].print(M_PRINT);
		cout << "-----------------------\n";
	}

	Move res;
	//terminal_input(m,r,c);					// SNair - made edits here for using minimax
	cout << "starting minimax" << endl;
	minimax(5,10);
	cout << "et fini minimax" << endl;
	//Preserve.
		m = best_move.m;
		r = best_move.r;
		c = best_move.c;
		res.m = best_move.m;
		res.r = best_move.r;
		res.c = best_move.c;
		res.pn = gblState.pn;
		res.to = make_pair(best_move.r,best_move.c);
		res.from = gblState.pos_present;
		res.eval = -1.0;
	gblState.apply_move(res);
	locState.apply_move(res);
	cout << "Move played " <<  m << " " << r << " " << c << endl;
	gblState.print(S_PRINT);
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
		res.pn = gblState.pn;
		res.to = make_pair(r,c);
		res.from = gblState.pos_present;
		res.eval = -1.0;
	gblState.apply_move(res);
	locState.apply_move(res);

	gblState.print(S_PRINT);
	return;
}
#endif