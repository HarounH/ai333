#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"
#include "get_all_moves.cpp"

void State::apply_move(Move& mov) { // Assumes that the move is valid.
	if ( mov.m == 0 ) {
		//Change positions.
		if ( mov._pn == 1 ) {
			player_1 = make_pair(r,c);
		} else {
			player_2 = make_pair(r,c);
		}
	} else if ( mov.m == 1 ) {
		//Throw a wall_H into it.
		wall_H[r][c] = true;
	} else if ( mov.m == 2 ) {	
		wall_V[r][c] = true;
	}
	toggle_player();
}

void State::unapply_move(Move& mov) { // Assumes that the move is valid.
	if ( mov.m == 0 ) {
		//Change positions.
		if ( mov._pn == 1 ) {
			player_1 = make_pair(_pr,_pc);
		} else {
			player_2 = make_pair(_pr,_pc);
		}
	} else if ( mov.m == 1 ) {
		//Throw a wall_H into it.
		wall_H[r][c] = false;
	} else if ( mov.m == 2 ) {	
		wall_V[r][c] = false;()
	}
	toggle_player();
}

bool State::valid_wall( int& _r , int& _c , bool hor) {
	if ( wall_V[_r][_c] || wall_H[_r][_c] ) {
		return false;
	} //There isnt already a wall there.
	//Avoids segfaults on the +1 side too.
	if (( hor && !wall_H[_r-1][_c] && ( (_r+1) <= N ) && (!wall_H[_r+1][_c] )) || ( (!hor) && !wall_V[_r][_c-1] && ( (_c+1) <= M ) && (!wall_V[_r][_c+1] )) ) {
		return true;
	} else {
		return false;
	}
}


/* MINIMAX (with Alpha Beta Pruning, with cutoff)
 *-------------------------------------------------
 * Recursive implementation
 * idea is to use local state element and pass it around in the tree
 * edges (which specify actions) are generated using get_all_moves
 * apply_move, unapply_move to tweak state back and forth
 * implementation similar to AIMA version 						
 * INVARIANT: max_value and min_value return state unchanged in the end	
 * -------------------------------------------------*/									/*

Move Player::minimax( int depth , float time_limit )
{
	locState = glbState;		// init
	
	max_value( -infty, +infty , depth, 0, time_limit);								// FIX {do a find and replace for all -infty, +infty}
	
	return best_move;
}

int Player::max_value(double alpha, double beta, int cutoff, int curDepth, float time_limit)
{
	if (cutoff == curDepth) return eval_state();
	
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
	if (cutoff == curDepth) return eval_state();
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
}																*/

////////////////  end of minimax  //////////////////

#endif