#ifndef COMMUNICATIONS_CPP
#define COMMUNICATIONS_CPP

bool snair_flag = false;
void terminal_input(int& m , int& r, int& c) {cin >> m >> r >> c; }
int init_count = 0;
//ACTIVELY ALTER THIS FOR OUR AI.


void Player::init_monte_carlo(MonteCarlo& mc)
{
	mc.init(*this);
}

void Player::send_move_to_client_cpp(int& m , int& r , int& c, MonteCarlo& monte_carlo) {
	Move res;
	
	//terminal_input(m,r,c);					// SNair - made edits here for using minimax
	bool shouldimmx = true;
	std::vector<bool> phc(5,true); //plie hard coded.
	if (locState.plies/2==0 and phc[0])
	{	
		phc[0] = false;
		Move iftwo(0,8,5); iftwo.from = Position(9,5);iftwo.to = Position(8,5);
		Move ifone(0,2,5);ifone.from = Position(1,5);ifone.to = Position(2,5);
//		cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((locState.mypn==1) and locState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
		else if ((locState.mypn==2) and locState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=false;}
		else snair_flag = true; 
	}
	if (locState.plies/2==1 and !snair_flag and phc[1])
	{	phc[1] = false;
		Move iftwo(0,7,5);iftwo.from = Position(8,5);iftwo.to = Position(7,5);
		Move ifone(0,3,5);ifone.from = Position(2,5);ifone.to = Position(3,5);
//		cout << "mypn " << gblState.mypn <<st " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((locState.mypn==1) and locState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
		else if ((locState.mypn==2) and locState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=false;}
		else snair_flag = true;
	}
	if (locState.plies/2==2 and !snair_flag and phc[2])
	{	phc[2] = false;
		Move iftwo(0,6,5);iftwo.from = Position(7,5);iftwo.to = Position(6,5);
		Move ifone(0,4,5);ifone.from = Position(3,5);ifone.to = Position(4,5);
//		cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((locState.mypn==1) and locState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
		else if ((locState.mypn==2) and locState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=false;}
		else snair_flag = true;
	}
	if (locState.plies/2==3 and !snair_flag and phc[3])
	{
		phc[3] = false;
		Move iftwo(1,8,5);
		Move ifone(1,3,5);
		//cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
		if ((locState.mypn==1) and locState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
		else if ((locState.mypn==2) and locState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=true;}		// SNair changed this
		
		snair_flag = true;
	}
	// if (locState.plies/2==4 and !snair_flag and phc[4])
// 	{
// 		phc[4] =false;
// 		Move iftwo(1,7,7);
// 		Move ifone(1,4,7);
// 		//cout << "mypn " << gblState.mypn << " valid move : " << gblState.valid_move(iftwo) << endl;
// 		if ((locState.mypn==1) and locState.valid_move(ifone)) {best_move.m=0;best_move = ifone; shouldimmx=false;}
// 		else if ((locState.mypn==2) and locState.valid_move(iftwo)) {best_move.m=0;best_move = iftwo; shouldimmx=false;}
//
// 		snair_flag = true;		// making it false, last hard coded move
// 	} //Safely disregarding time for hard coded moves.
	
	if (shouldimmx and init_count == 0) {
		init_monte_carlo(monte_carlo); 
		init_count++; //its like a flag.
	}
	
 	bool h_flag = true;
	
 	cout << "game state=" << locState.is_endgame() << "," << locState.i_won() << "," << locState.i_lost() << "\n";
 	cout << "other player=(" << locState.pos_other.r << "," << locState.pos_other.c << ")\n";
	if ((h_flag && snair_flag && shouldimmx && locState.i_lost())) {
		res = ordinary_mmx(1,10); //if i've lost, just do a normal minimax.
		h_flag = false;
	}
	

	
	//ASSERT : all profiling happens within the functions.
	if (h_flag && snair_flag && shouldimmx) {
 		//cout << "yo" << endl;
 		timetaken_formove = clock();
		for (int i = 0 ; i<2000 ; i++) {
			monte_carlo.MCTS(*this,monte_carlo.root,0,2,0.0);
			//Observation : Each iteration takes ~0.005 seconds, which makes no sense.
		}
		timetaken_formove = (clock() - timetaken_formove)/(CLOCKS_PER_SEC);
		
		cout << "time taken to pick move=" << timetaken_formove << "\n";
		

		//Printing out the result of searching. 	
		int total = 0;
		/*for (int i = 0 ; i<monte_carlo.root->children.size() ; i++) {
			{cout << monte_carlo.root->times_moves_explored[i] << " (" << monte_carlo.root->avg_so_far[i] << ") "; total+= monte_carlo.root->times_moves_explored[i];}
		}
		cout << "\n"; cout << "total : " << total << "\n";*/
		
	//	cout << "before clean up : " << exploredNode::node_count << endl;
		monte_carlo.change_root(*this, best_move);							// delete extra nodes
	//	cout << "after clean up  : " << exploredNode::node_count << endl;
		
 	}

		res.m = best_move.m;
		res.r = best_move.to.r;
		res.c = best_move.to.c;
		res.pn = locState.pn;
		res.to = make_pair(best_move.r,best_move.c);
		res.from = locState.pos_present;
		res.my_shortest_path = best_move.my_shortest_path;
		res.op_shortest_path = best_move.op_shortest_path;
		res.eval = best_move.eval;
		m = best_move.m;
		r = best_move.r;
		c = best_move.c;
		
	//gblState.apply_move(res);
	locState.apply_move(res);
	plies++;
	
	cout << "Move played " <<  m << " " << r << " " << c << "\n";
	
	// gblState.print(S_PRINT);
	return;
}

void Player::read_time_left_from_client_cpp(float _t) {
	remaining_time = _t;
}

void Player::read_move_from_client_cpp(int& m ,int& r, int& c, MonteCarlo& monte_carlo) {
	Move res;
		res.m = m;
		res.r = r;
		res.c = c;
		res.pn = locState.pn;
		res.to = make_pair(r,c);
		res.from = locState.pos_present;
		res.eval = -1.0;

	
	cout << "move read=(" << res.m << "," << res.r << "," << res.c << ")\n";
	cout << "\t gamestate=(" << locState.is_endgame() << "," << locState.i_won() << "," << locState.i_lost() << ")\n";
//	cout << "before clean up : " << exploredNode::node_count << endl;
	if (init_count == 1 and !locState.i_lost() and !locState.i_won()) monte_carlo.change_root(*this, res);	// deletions performed
//	cout << "after  clean up : " << exploredNode::node_count << endl;
	
	//gblState.apply_move(res);
	locState.apply_move(res);
	plies++;
	// gblState.print(S_PRINT);
	return;
}
#endif