#ifndef MINIMAX_CPP
#define MINIMAX_CPP

#define INFTY 1000000000
 
/* MINIMAX (with Alpha Beta Pruning, with cutoff)
 *-------------------------------------------------
 * Recursive implementation
 * idea is to use local state element and pass it around in the tree
 * edges (which specify actions) are generated using get_all_moves
 * apply_move, unapply_move to tweak state back and forth
 * implementation similar to AIMA version 						
 * INVARIANT: max_value and min_value return state unchanged in the end	
 * ------------------------------------------------- */									

Move Player::minimax( int depth , float time_limit )
{
	locState = gblState;		// init
	
	max_value( -INFTY, +INFTY , depth, 0, time_limit);								// FIX {do a find and replace for all -INFTY, +INFTY}
	
	return best_move;
}

double Player::max_value(double alpha, double beta, int cutoff, int curDepth, float time_limit)
{
	if (cutoff == curDepth or locState.is_endgame()) return locState.evaluate();

	vector<Move> moves; locState.get_all_moves(moves);
	// cout << " ########### BEGIN LOC_STATE in max_value of depth="<<curDepth<<"########### \n";
	// locState.print(S_PRINT);
	// cout << " ########### END OF LOC STATE in max_value ########## \n";
	double v = -INFTY;
	for(int i=0; i<moves.size(); ++i) {
		locState.apply_move(moves[i]);
		moves[i].eval = locState.evaluate();
		locState.unapply_move(moves[i]);
	}
	sort(moves.begin(), moves.end() , [](Move l,Move r){return l.eval>r.eval;} );
	for (vector<Move>::iterator it = moves.begin() ; it!=moves.end() ;it++)
	{
		Move t = *it;  // H - Changed the free usage of *it to a "save the value and do shit" because iterators can be scary things.
		locState.apply_move(t);
		
		// v = max(v,min_value(alpha,beta,cutoff,curDepth+1,time_limit));					// FIX time_limit
		int cur_min = min_value(alpha,beta,cutoff,curDepth+1,time_limit);
		
		if (cur_min > v)
		{
			v = cur_min;
			if (curDepth == 0) {
				best_move = t;
				// cout << " ################# BEST"; best_move.print(M_PRINT); cout << " ##################\n";
			}
		}
		
		if (v >= beta) {
			locState.unapply_move(t); //H - Changed some stuff to be VERY careful.
			return v;
		}
		alpha = max(alpha,v);
		
		locState.unapply_move(t);
	}
	
	return v;
}

double Player::min_value(double alpha, double beta, int cutoff, int curDepth, float time_limit)
{
	if (cutoff == curDepth or  locState.is_endgame()) return locState.evaluate();
	
	vector<Move> moves; locState.get_all_moves(moves);
	// cout << " ########### BEGIN LOC_STATE in min_value of depth="<<curDepth<<"########### \n";
	// locState.print(S_PRINT);
	// cout << " ########### END OF LOC STATE in min_value ########## \n";
	for(int i=0; i<moves.size(); ++i) {
		locState.apply_move(moves[i]);
		moves[i].eval = locState.evaluate();
		locState.unapply_move(moves[i]);
	}
	std::sort(moves.begin() , moves.end() , [](Move l,Move r){return l.eval>r.eval;} );
	double v = +INFTY;
	
	for (vector<Move>::iterator it = moves.begin() ; it!=moves.end() ;it++)
	{
		Move t = *it; 	// H - Changed the free usage of *it to a "save the value and do shit" because iterators can be scary things.
		locState.apply_move(t);
		
		v = min(v,max_value(alpha,beta,cutoff,curDepth+1,time_limit));					// FIX time_limit
		if (v <= alpha) { 
			locState.unapply_move(t); //H - Changed some stuff to be VERY careful.
			return v;
		}
		beta = min(beta,v);
		
		locState.unapply_move(t);
	}
	
	return v;
}

////////////////  end of minimax  //////////////////

#endif