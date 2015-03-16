#ifndef GAME_H
#define GAME_H

#include <vector>
#include <set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <cassert>
#include <string>
#include <utility>
#include <iostream>
#include "Move.h"

using namespace std;

class GameState {
	int numWallsA, numWallsB;
	vector<vector<bool> > horWalls;
	vector<vector<bool> > verWalls;
	Pos player1;
	Pos player2;
	bool turn;
public:
	GameState(int n, int m, int k)
	{
		horWalls.resize(n);
		verWalls.resize(n);
		for(int i = 0; i < n; i++)
		{
			horWalls[i].resize(m, false);
			verWalls[i].resize(m, false);
		}
		numWallsA = numWallsB = k;
		player1 = make_pair(0, (m-1)/2);
		player2 = make_pair(n-1, (m-1)/2);
		turn = 0;
	}
	
	int length() { return (int) horWalls.size(); }
	
	int width() { return (int) horWalls[0].size(); }
	
	int currentPlayer(){ return turn; }  // 0 if player 1, 1 if player 2
	
	int otherPlayer() {return !turn;}
	
	Pos player1Pos() { return player1; }

	Pos player2Pos() { return player2; }
	
	bool terminal() {
		return player1Win() || player2Win();
	}
	
	bool player1Win()
	{
		return player1.first == (int) horWalls.size();
	}
	
	bool player2Win()
	{
		return player2.first == 0;
	}
	
	int player1Walls() {
		return numWallsA;
	}
	
	int player2Walls() {
		return numWallsB;
	}
	
	void applyMove(Move& move);
	void unMove(Move& move);
	void getValidMoves(vector<Move>& possibleMoves);
	void addMove(vector<Move>& possibleMoves, Move& a);
	void getValidTraversals(vector<Move>& possibleMoves, Pos& currentPos, Pos& otherPos);
	void getValidWallPlacements(vector<Move>& possibleMoves);
	int shortestDistanceToGoal(Pos& p, int goalRow);
	
	void print();
	
};

#endif