#ifndef COMMUNICATIONS_CPP
#define COMMUNICATIONS_CPP

bool flag = false;
void terminal_input(int& m , int& r, int& c) {cin >> m >> r >> c; }
//ACTIVELY ALTER THIS FOR OUR AI.
void Player::send_move_to_client_cpp(int& m , int& r , int& c) {
	
	// if ( M_PRINT ) {
	// 	cout << "-----------------------\n";
	// 	vector<Move> moves;
	// 	//locState.get_all_walls(moves);
	// 	locState.get_all_jumps(moves);
	// 	for(int i=0; i<moves.size(); ++i) moves[i].print(M_PRINT);
	// 	cout << "-----------------------\n";
	// } // H - ...might want it elsewhere because of how wierd this looks. :P

	
	Move res;
	
	//terminal_input(m,r,c);					// SNair - made edits here for using minimax

	//Preserve.
	//

	if (gblState.plies/2==0 )
	{	Move iftwo(0,8,5); iftwo.from = Position(9,5);iftwo.to = Position(8,5);
		Move ifone(0,2,5);ifone.from = Position(1,5);ifone.to = Position(2,5);
//		cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((gblState.mypn==1) and gblState.valid_move(ifone)) best_move = ifone;
		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) best_move = iftwo;
		else flag = true; 
	}

	if (gblState.plies/2==1 and !flag)
	{
		Move iftwo(0,7,5);iftwo.from = Position(8,5);iftwo.to = Position(7,5);
		Move ifone(0,3,5);ifone.from = Position(2,5);ifone.to = Position(3,5);
//		cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((gblState.mypn==1) and gblState.valid_move(ifone)) best_move = ifone;
		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) best_move = iftwo;
		else flag = true;
	}

	if (gblState.plies/2==2 and !flag)
	{
		Move iftwo(0,6,5);iftwo.from = Position(7,5);iftwo.to = Position(6,5);
		Move ifone(0,4,5);ifone.from = Position(3,5);ifone.to = Position(4,5);
//		cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((gblState.mypn==1) and gblState.valid_move(ifone)) best_move = ifone;
		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) best_move = iftwo;
		else flag = true;
	}

	if (gblState.plies/2==3 and !flag)
	{
		Move iftwo(1,8,5);
		Move ifone(1,3,5);
		//cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((gblState.mypn==1) and gblState.valid_move(ifone)) best_move = ifone;
		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) best_move = iftwo;
		else flag = true;
	}

	if (gblState.plies/2==4 and !flag)
	{
		Move iftwo(1,8,3);
		Move ifone(1,3,3);
		//cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((gblState.mypn==1) and gblState.valid_move(ifone)) best_move = ifone;
		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) best_move = iftwo;

		flag = true;		// making it false, last hard coded move
	}

	 	if (flag and gblState.plies/2>4) {cout << "yo" << endl;res = minimax(2,10);}
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
	cout << "Move played " <<  m << " " << r << " " << c << "\n";
	// gblState.print(S_PRINT);
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

	// gblState.print(S_PRINT);
	return;
}
#endif