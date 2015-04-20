#ifndef AIENGINE_H
#define AIENGINE_H

#include <vector>
#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "Game.h"


using namespace std;


// There is some bug in the alpha beta pruning thing which I can't pin point. I'll tackle it in the evening.

template <typename EVAL>
class AIEngine{

private:
	EVAL eval;
	int myPlayer;

public:
	AIEngine(EVAL e, int m): eval(e), myPlayer(m){ 
	}

	Move minimax(GameState& gs, int depth)
	{
		double alpha = -1000000;
		double beta = 1000000;
		double v = -1000000;
		vector<Move> possibleMoves;
		cout << "Getting moves...\n";
		if(myPlayer == 0 && gs.player1Win())
		{
			depth = 1;
			if(gs.player1Walls() == 0)
				return Move(0, 0, 0);
			else
				gs.getValidWallPlacements(possibleMoves);
		}
		else if(myPlayer == 1 && gs.player2Win())
		{
			depth = 1;
			if(gs.player2Walls() == 0)
				return Move(0, 0, 0);
			else
				gs.getValidWallPlacements(possibleMoves);
		}
		else if(myPlayer == 0 && gs.player2Win())
		{
			Pos mypos = gs.player1Pos();
			Pos otherpos = make_pair(20, 20);
			gs.getValidTraversals(possibleMoves, mypos, otherpos);
			depth = 1;
		}
		else if(myPlayer == 1 && gs.player1Win())
		{
			Pos mypos = gs.player1Pos();
			Pos otherpos = make_pair(20, 20);
			gs.getValidTraversals(possibleMoves, mypos, otherpos);
			depth = 1;
		}
		else
			gs.getValidMoves(possibleMoves);
		Move bestMove = *(possibleMoves.begin());
		Pos p1 = gs.player1Pos();
		Pos p2 = gs.player2Pos();
		
		cout << "Player 1 position : " << p1.first <<" " << p1.second <<"\n";
		cout << "Player 2 position : "<< p2.first <<" " << p2.second <<"\n";
		
		typedef vector<Move>::iterator itr;		
		cout << "No. of Possible Moves: " << (int)possibleMoves.size() << "\n";
		random_shuffle(possibleMoves.begin(), possibleMoves.end());
		for (itr it = possibleMoves.begin(); it != possibleMoves.end(); it++)
		{
			Move undo;
			undo.choice = (*it).choice;
			if(undo.choice == 0)
			{
				if(gs.currentPlayer() == 0)
					undo.pos = p1;
				else
					undo.pos = p2;
			}
			else
				undo.pos = (*it).pos;
			gs.applyMove(*it);
			// cout <<"After move :\n";
// 			gs.print();
			Pos pl1 = gs.player1Pos();
			Pos pl2 = gs.player2Pos();
			
			
			int dist1 = gs.shortestDistanceToGoal(pl1, gs.length()-1);
			int dist2 = gs.shortestDistanceToGoal(pl2, 0);
			if(dist1 == -1 || dist2 == -1)
			{
				gs.unMove(undo);
				continue;
			}
			double value = Min(gs, depth-1, alpha, beta);
			if(v < value)
			{
				v = value;
				bestMove = *it;
			}
			if(v >= beta)
			{
				gs.unMove(undo);
				cout <<"\nBest Eval : " << v<<"\n";
				
				return bestMove;
			}
			alpha = max(alpha, v);
			// double m = eval(gs, myPlayer);
// 			if(m > v)
// 			{
// 				v = m;
// 				bestMove = *it;
// 			}
			gs.unMove(undo);
			// cout <<"After unmove :\n";
// 			gs.print();
		}
		cout <<"\nBest Eval : " << v<<"\n";
		
		return bestMove;
	}


	double Max(GameState& gs, int depth, double alpha, double beta)
	{
		if (gs.terminal() || (depth == 0)) return eval(gs, myPlayer);
		
		double v = -1000000;
		vector<Move> possibleMoves;
		gs.getValidMoves(possibleMoves);
		

		typedef vector<Move>::iterator itr;
		for (itr it = possibleMoves.begin(); it != possibleMoves.end(); it++)
		{
			Move undo;
			undo.choice = (*it).choice;
			if(undo.choice == 0)
			{
				if(gs.currentPlayer() == 0)
					undo.pos = gs.player1Pos();
				else
					undo.pos = gs.player2Pos();
			}
			else
				undo.pos = (*it).pos;
			gs.applyMove(*it);
			Pos p1 = gs.player1Pos();
			Pos p2 = gs.player2Pos();
			
			int dist1 = gs.shortestDistanceToGoal(p1, gs.length()-1);
			int dist2 = gs.shortestDistanceToGoal(p2, 0);
			if(dist1 == -1 || dist2 == -1)
			{
				gs.unMove(undo);
				continue;
			}
			v = max(v, Min(gs, depth-1, alpha, beta));
			if(v >= beta)
			{
				gs.unMove(undo);
				return v;
			}
			
			alpha = max(alpha, v);
			gs.unMove(undo);
		}
		return v;
	}


	double Min(GameState& gs, int depth, double alpha, double beta)
	{
		if (gs.terminal() || (depth == 0)) 
			return eval(gs, myPlayer);
		double v = 1000000;
		vector<Move> possibleMoves;
		gs.getValidMoves(possibleMoves);

		typedef vector<Move>::iterator itr;
		for (itr it = possibleMoves.begin(); it != possibleMoves.end(); it++)
		{
			Move undo;
			undo.choice = (*it).choice;
			if(undo.choice == 0)
			{
				if(gs.currentPlayer() == 0)
					undo.pos = gs.player1Pos();
				else
					undo.pos = gs.player2Pos();
			}
			else
				undo.pos = (*it).pos;
			gs.applyMove(*it);
			Pos p1 = gs.player1Pos();
			Pos p2 = gs.player2Pos();
			int dist1 = gs.shortestDistanceToGoal(p1, gs.length()-1);
			int dist2 = gs.shortestDistanceToGoal(p2, 0);
			
			if(dist1 == -1 || dist2 == -1)
			{
				gs.unMove(undo);
				continue;
			}
			v = min(v, Max(gs, depth-1, alpha, beta));
			if(v <= alpha)
			{
				gs.unMove(undo);
				return v;
			}
			beta = min(beta, v);
			gs.unMove(undo);
		}
		return v;
	}

};

#endif