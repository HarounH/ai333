#ifndef MMX_CPP
#define MMX_CPP
/* min_value, max_value, plain old minimax-no time limit, itd_minimax - with a time limit. */

/* H - Want an iterative version of minimax which uses iteration instead of recursion.
Why? Because i want to remember which table was the best path. 
*/
#define INF 100000000
/*enum NODE_TYPE {MAX_NODE, MIN_NODE} - I dont need it because My depth tells me whether I'm a minnode or a max node
	even depth means that I'm at a max node. Odd depth means that i'm at a min node.
*/


//UNCOMMENT THE LOWER SECTION 
// Move Player::iterative_mmx( int d , double t) { //Cares not for time limit.
// 	//Requires that the moves always turn up in the same order.
// 	double alpha = -INF;
// 	double beta  = +INF;
	
// 	stack<Move> fringe; //Implementing a dfs, basically.
// 	stack<Move> path_taken; //Remembers the path taken so far.
// 	std::vector<Move> node_children;
// 	/*Initialize loc state.
// 		Dont need to because the player already has locState.
// 	*/
// 	locState.get_all_moves(fringe); //Put all the moves into the stack
	
// 	do {

// 	}while();
// }

/* Old minimax . 
*//* MINIMAX (with Alpha Beta Pruning, with cutoff)
 *-------------------------------------------------
 * Recursive implementation
 * idea is to use local state element and pass it around in the tree
 * edges (which specify actions) are generated using get_all_moves
 * apply_move, unapply_move to tweak state back and forth
 * implementation similar to AIMA version 						
 * INVARIANT: max_value and min_value return state unchanged in the end	
 * ------------------------------------------------- */									
#define INFTY 100000000
Move Player::ordinary_mmx( int depth , float time_limit )
{
	// locState = gblState;		// init

	max_value( -INFTY, +INFTY , depth, 0, time_limit);								// FIX {do a find and replace for all -INFTY, +INFTY}
	return best_move;
}

double Player::max_value(double alpha, double beta, int cutoff, int curDepth, float time_limit)
{
	//if (cutoff == curDepth or locState.i_won() or locState.i_lost() ) return locState.evaluate();
	if (cutoff == curDepth or locState.is_endgame() or (locState.i_won() /*and !locState.i_lost()*/)) return locState.evaluate();
	
	vector<Move> moves; locState.get_all_moves(moves);
	// cout << " ########### BEGIN LOC_STATE in max_value of depth="<<curDepth<<"########### \n";
	// locState.print(S_PRINT);
	// cout << " ########### END OF LOC STATE in max_value ########## \n";
	double v = -INFTY;
	// for(int i=0; i<moves.size(); ++i) {
	// 	locState.apply_move(moves[i]);
	// 	moves[i].eval = locState.evaluate();
	// 	locState.unapply_move(moves[i]);
	// }
	//std::sort(moves.begin() , moves.end() , [](Move lhs,Move rhs){return ((lhs.op_shortest_path-lhs.my_shortest_path)>(rhs.op_shortest_path-rhs.my_shortest_path)) ;} );
	std::sort(moves.begin() , moves.end() , [](Move lhs,Move rhs){return (lhs.eval>rhs.eval) ;} );
	
	vector<Move>::iterator mend = moves.end();
	// if ( curDepth > 4 ) {
	// 	mend = moves.begin() + 1 + (moves.size()/2);
	// }
	
	for (vector<Move>::iterator it = moves.begin() ; it!=mend ;it++)
	{
		Move t = *it;  // H - Changed the free usage of *it to a "save the value and do shit" because iterators can be scary things.
		locState.apply_move(t);
		
		// v = max(v,min_value(alpha,beta,cutoff,curDepth+1,time_limit));					// FIX time_limit
		double cur_min = min_value(alpha,beta,cutoff,curDepth+1,time_limit);
		
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
	//if (cutoff == curDepth or locState.i_won() or locState.i_lost()) return locState.evaluate();
	if (cutoff == curDepth or locState.is_endgame() or (locState.i_won() /*and !locState.i_lost()*/)) return locState.evaluate();
	
	vector<Move> moves; locState.get_all_moves(moves);
	// cout << " ########### BEGIN LOC_STATE in min_value of depth="<<curDepth<<"########### \n";
	// locState.print(S_PRINT);
	// cout << " ########### END OF LOC STATE in min_value ########## \n";
	// for(int i=0; i<moves.size(); ++i) {
	// 	locState.apply_move(moves[i]);
	// 	moves[i].eval = locState.evaluate();
	// 	locState.unapply_move(moves[i]);
	// }
	//std::sort(moves.begin() , moves.end() , [](Move lhs,Move rhs){return ((lhs.op_shortest_path-lhs.my_shortest_path)<(rhs.op_shortest_path-rhs.my_shortest_path)) ;} );
	std::sort(moves.begin() , moves.end() , [](Move lhs,Move rhs){return (lhs.eval<rhs.eval) ;} );
	double v = +INFTY;
	
	vector<Move>::iterator mend = moves.end();
	// if ( curDepth > 4 ) {
	// 	mend = moves.begin() + 1 + (moves.size()/2);
	// }
	
	for (vector<Move>::iterator it = moves.begin() ; it!=mend ;it++)
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

#endif