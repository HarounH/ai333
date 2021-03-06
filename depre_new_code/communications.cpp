#ifndef COMMUNICATIONS_CPP
#define COMMUNICATIONS_CPP

bool snair_flag = false;
void terminal_input(int& m , int& r, int& c) {cin >> m >> r >> c; }
//ACTIVELY ALTER THIS FOR OUR AI.
void Player::send_move_to_client_cpp(int& m , int& r , int& c) {
	Move res;
	
	//terminal_input(m,r,c);					// SNair - made edits here for using minimax
	bool shouldimmx = true;
	std::vector<bool> phc(5,true); //plie hard coded.
	if (gblState.plies/2==0 and phc[0])
	{	
		phc[0] = false;
		Move iftwo(0,8,5); iftwo.from = Position(9,5);iftwo.to = Position(8,5);
		Move ifone(0,2,5);ifone.from = Position(1,5);ifone.to = Position(2,5);
//		cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((gblState.mypn==1) and gblState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=false;}
		else snair_flag = true; 
	}
	if (gblState.plies/2==1 and !snair_flag and phc[1])
	{	phc[1] = false;
		Move iftwo(0,7,5);iftwo.from = Position(8,5);iftwo.to = Position(7,5);
		Move ifone(0,3,5);ifone.from = Position(2,5);ifone.to = Position(3,5);
//		cout << "mypn " << gblState.mypn <<st " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((gblState.mypn==1) and gblState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=false;}
		else snair_flag = true;
	}
	if (gblState.plies/2==2 and !snair_flag and phc[2])
	{	phc[2] = false;
		Move iftwo(0,6,5);iftwo.from = Position(7,5);iftwo.to = Position(6,5);
		Move ifone(0,4,5);ifone.from = Position(3,5);ifone.to = Position(4,5);
//		cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((gblState.mypn==1) and gblState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=false;}
		else snair_flag = true;
	}
	if (gblState.plies/2==3 and !snair_flag and phc[3])
	{
		phc[3] = false;
		Move iftwo(1,8,5);
		Move ifone(1,3,5);
		//cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((gblState.mypn==1) and gblState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=false;}
		
		snair_flag = true;
	}
	// if (gblState.plies/2==4 and !snair_flag and phc[4])
// 	{
// 		phc[4] =false;
// 		Move iftwo(1,7,7);
// 		Move ifone(1,4,7);
// 		//cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
// 		if ((gblState.mypn==1) and gblState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
// 		else if ((gblState.mypn==2) and gblState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=false;}
//
// 		snair_flag = true;		// making it false, last hard coded move
// 	} //Safely disregarding time for hard coded moves.
 	bool h_flag = true;
	
	if ((h_flag && snair_flag && shouldimmx && locState.i_lost())) {
		
		res = ordinary_mmx(1,10);
		h_flag = false;
	}
	if (h_flag && snair_flag && shouldimmx) {
 		//cout << "yo" << endl;
 		res = ordinary_mmx(2,10); /* H - Need to make changes here. */
 	}

		res.m = best_move.m;
		res.r = best_move.to.r;
		res.c = best_move.to.c;
		res.pn = gblState.pn;
		res.to = make_pair(best_move.r,best_move.c);
		res.from = gblState.pos_present;
		res.eval = -1.0;
		m = best_move.m;
		r = best_move.r;
		c = best_move.c;
		
	gblState.apply_move(res);
	locState.apply_move(res);
	plies++;
	
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
	plies++;
	// gblState.print(S_PRINT);
	return;
}
#endif