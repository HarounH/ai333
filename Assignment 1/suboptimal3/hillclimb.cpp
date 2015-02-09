#ifndef SUB_OPT_SEARCH_CPP
	#define SUB_OPT_SEARCH_CPP

#include <limits>
#define BIG_DOUBLE std::numeric_limits<double>::max()

void hilldescent_norestarts_untimed(int MAX_PLATEAU_MOVES = 0) {
	Move bestmove;
		bestmove.newcost = BIG_DOUBLE;
	int plateauctr = 0;
	while(true) { //Breaks on the first optima after looking to escape plateaus
		vector<Move> moves;
		Move nxtbstmov;
			nxtbstmov.newcost = BIG_DOUBLE;
		getMoves(moves);
		cout << moves.size() << " neighbours \n";
		for(int i=0; i<moves.size(); ++i) {
			cout << moves[i].newcost << " cost found \n";
			if (moves[i].newcost < nxtbstmov.newcost ) {
				nxtbstmov = moves[i];
			}
		}
		if ( nxtbstmov.newcost < bestmove.newcost ) {
			bestmove = nxtbstmov;
			plateauctr = 0;
			setState(bestmove);
		} else if (nxtbstmov.newcost == bestmove.newcost && (plateauctr < MAX_PLATEAU_MOVES)) {
			plateauctr++;
			bestmove = nxtbstmov;
			setState(bestmove);
		} else {
			break;
		}
	}
}

void hilldescent_restarts_untimed(int MAX_RESTARTS = 1 , int MAX_PLATEAU_MOVES = 0) {
	Move bestmove;
		bestmove.newcost = BIG_DOUBLE;
		
	int plateauctr = 0;


	//local version stores the best so far.
	vector<string> localstrings = sequences;
	double localcost = cost;
	int locallength = length;
	vector< vector<int> > localdashpos = dashpos;
	

	while( nrestarts <= MAX_RESTARTS ) {
		while(true) { //Breaks on the first optima after looking to escape plateaus
			vector<Move> moves;
			Move nxtbstmov;
				nxtbstmov.newcost = BIG_DOUBLE;
			getMoves(moves);
			cout << moves.size() << " neighbours \n";
			for(int i=0; i<moves.size(); ++i) {
				cout << moves[i].newcost << " cost found \n";
				if (moves[i].newcost < nxtbstmov.newcost ) {
					nxtbstmov = moves[i];
				}
			}
			if ( nxtbstmov.newcost < bestmove.newcost ) {
				bestmove = nxtbstmov;
				plateauctr = 0;
				setState(bestmove);
				if ( cost < localcost) {
					moveToLocal(localstrings , localdashpos , length , cost);
				}

			} else if (nxtbstmov.newcost == bestmove.newcost && (plateauctr < MAX_PLATEAU_MOVES)) {
				plateauctr++;
				bestmove = nxtbstmov;
				setState(bestmove);
				if ( cost < localcost) {
					moveToLocal(localstrings , localdashpos , length , cost);
				}
			} else {
				break;
			}
		}
		if ( cost < localcost) {
			moveToLocal(localstrings , localdashpos , length , cost);
		}
		++nrestarts;
	} //Break out of inner loop.
	if (cost < localcost) {
		//Do Nothing.
	} else {
		movefromLocal(localstrings , localdashpos , locallength , localcost);
	}
	return;
}

#endif