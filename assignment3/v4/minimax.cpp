#ifndef MINIMAX_CPP
#define MINIMAX_CPP

/* MINIMAX (with Alpha Beta Pruning, with cutoff)
 *-------------------------------------------------
 * Recursive implementation
 * idea is to use local state element and pass it around in the tree
 * edges (which specify actions) are generated using get_all_moves
 * apply_move, unapply_move to tweak state back and forth
 * implementation similar to AIMA version 						
 * INVARIANT: max_value and min_value return state unchanged in the end	
 * -------------------------------------------------*/									

Move Player::minimax( int depth , float time_limit )
{
	locState = glbState;		// init
	
	max_value( -infty, +infty , depth, 0, time_limit);								// FIX {do a find and replace for all -infty, +infty}
	
	return best_move;
}

int Player::max_value(double alpha, double beta, int cutoff, int curDepth, float time_limit)
{
	if (cutoff == curDepth or locState.is_endgame()) return locState.eval_state();
	
	vector<Move> moves = locState.get_all_moves();
	double v = -infty;
	
	for (vector<Move>::iterator it = moves.begin ; it!=moves.end ;it++)
	{
		locState.apply_move(*it);
		
		// v = max(v,min_value(alpha,beta,cutoff,curDepth+1,time_limit));					// FIX time_limit
		int cur_min = min_value(alpha,beta,cutoff,curDepth+1,time_limit);
		if (cur_min > v)
		{
			v = cur_min;
			if (curDepth == 0) best_move = *it;
		}
		
		if (v >= beta) return v;
		alpha = max(alpha,v);
		
		locState.unapply_move(*it);
	}
	
	return v;
}

int Player::min_value(double alpha, double beta, int cutoff, int curDepth, float time_limit)
{
	if (cutoff == curDepth or  locState.is_endgame()) return locState.eval_state();
	double v = +infty;
	
	for (vector<Move>::iterator it = moves.begin ; it!=moves.end ;it++)
	{
		locState.apply_move(*it);
		
		v = min(v,max_value(alpha,beta,cutoff,curDepth+1,time_limit));					// FIX time_limit
		if (v <= alpha) return v;
		beta = min(beta,v);
		
		locState.unapply_move(*it);
	}
	
	return v;
}																

////////////////  end of minimax  //////////////////

#endif