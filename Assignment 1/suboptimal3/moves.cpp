void getMoves( vector<Move>& moves ) { //Generates 2*k*length neighbours. Also stores the best neighbour yet in a global variable.
	for(int idx=0; idx<k; ++idx) {
		for(int didx = 0; didx < dashpos[idx].size(); ++didx) {
			//Forward swap
			if ( dashpos[idx][didx] < seqLengths[idx] ) { //it is possible to swap forward.
				Move move;
					move.newcost = 0.0;
					move.idx = idx;
					move.di = didx;
				int origDptr = dashpos[idx][didx] + didx;
				int newDptr  = dashpos[idx][didx] + didx + 1;
				while ((newDptr < length) && (sequences[idx][newDptr]=='-')) {
					++newDptr;
				}
				move.origDptr = origDptr;
				move.newDptr  = newDptr;
				move.newcost  = cost + evalCost_move(move);
				moves.push_back(move);
			}
			//Backward swap
			if ( dashpos[idx][didx] > 0 ) { //it is possible to swap backward 
				Move move;
					move.newcost = 0.0;
					move.idx = idx;
					move.di = didx;
				int origDptr = dashpos[idx][didx] + didx;
				int newDptr  = dashpos[idx][didx] + didx - 1;
				while ((newDptr > 0) && (sequences[idx][newDptr]=='-')) {
					--newDptr;
				}
				move.origDptr = origDptr;
				move.newDptr  = newDptr;
				move.newcost  = cost + evalCost_move(move);
				moves.push_back(move);
			}
		}
	}
}

void getBestMove( Move& bestMove ) {
	bestMove.newcost = 0.0;
	for(int idx=0; idx<k; ++idx) {
		for(int didx = 0; didx < dashpos[idx].size(); ++didx) {
			//Forward swap
			if ( dashpos[idx][didx] < seqLengths[idx] ) { //it is possible to swap forward.
				Move move;
					move.newcost = 0.0;
					move.idx = idx;
					move.di = didx;
				int origDptr = dashpos[idx][didx] + didx;
				int newDptr  = dashpos[idx][didx] + didx + 1;
				while ((newDptr < length) && (sequences[idx][newDptr]=='-')) {
					++newDptr;
				}
				move.origDptr = origDptr;
				move.newDptr  = newDptr;
				move.newcost += cost + evalCost_move(move);
				if ( move.newcost < bestMove.newcost )  {
					bestMove.idx = move.idx;
					bestMove.di = move.di ;
					bestMove.origDptr = move.origDptr;
					bestMove.newDptr = move.newDptr;
					bestMove.newcost = move.newcost;
				}
			}
			//Backward swap
			if ( dashpos[idx][didx] > 0 ) { //it is possible to swap backward 
				Move move;
					move.newcost = 0.0;
					move.idx = idx;
					move.di = didx;
				int origDptr = dashpos[idx][didx] + didx;
				int newDptr  = dashpos[idx][didx] + didx - 1;
				while ((newDptr > 0) && (sequences[idx][newDptr]=='-')) {
					--newDptr;
				}
				move.origDptr = origDptr;
				move.newDptr  = newDptr;
				move.newcost += cost + evalCost_move(move);
				if ( move.newcost < bestMove.newcost )  {
					bestMove.idx = move.idx;
					bestMove.di = move.di ;
					bestMove.origDptr = move.origDptr;
					bestMove.newDptr = move.newDptr;
					bestMove.newcost = move.newcost;
				}
			}
		}
	}
}

void setState(Move& move) {
	sequences[move.idx][ move.origDptr ] = sequences[move.idx][ move.newDptr ];
	sequences[move.idx][ move.newDptr ] = '-';
	cost = move.newcost;
	//Need to alter dashPos and sort it as well.
	dashpos[move.idx][move.di] += ((move.newDptr>move.origDptr)?(1):(-1));
	//swap forward
	for( int di1 = move.di; di1 < dashpos[move.idx].size()-1 ; ++di1) {
		if ( dashpos[move.idx][di1] < dashpos[move.idx][di1+1]) {
			int temp = dashpos[move.idx][di1];
			dashpos[move.idx][di1] = dashpos[move.idx][di1+1];
			dashpos[move.idx][di1+1] = temp;
		} else {
			break;
		}
	}
	//swap backward.
	for( int di1 = move.di; di1 > -1; --di1) {
		if ( dashpos[move.idx][di1] > dashpos[move.idx][di1-1]) {
			int temp = dashpos[move.idx][di1];
			dashpos[move.idx][di1] = dashpos[move.idx][di1-1];
			dashpos[move.idx][di1-1] = temp;
		} else {
			break;
		}
	}
}

void movefromLocal( vector<string>& localsequences , vector< vector<int> >& localdashpos , int locallength , double localcost) {
	cost = localcost;
	length = locallength;
	sequences = localsequences;
	dashpos = localdashpos;
}


void moveToLocal( vector<string>& localsequences , vector< vector<int> >& localdashpos , int locallength , double localcost) {
	localcost = cost ;
	locallength = length ;
	localsequences = sequences;
	localdashpos = dashpos;
}