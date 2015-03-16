#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

struct Player
{
	int col, row;
	int numWalls;
	int depth;
	
	Player();
	Player(Player& p);
	Player(bool first);
	Player(int r, int c, int walls,int d);
	
};

struct Position
{
	int row, col, pathCost, depth;
	Position();
	Position(int r, int c, int pCost);
	Position(Player& p);
};

struct positionComp 
{
  bool operator() (const Position& lhs, const Position& rhs) const
  {
  	return lhs.pathCost<rhs.pathCost;
  }
};

struct Action
{
	int m, r, c;
	int moveAction;
	Action(int action, int row, int col, int def);
	Action(int& m_in, int& r_in, int& c_in);
	void convertToMove(int& m, int& r, int& c);
};

struct State
{
	Player AI, server;   //Do we need two players in State? Apparently. We always choose to be first in our implementation
	int stateType;
	bitset<64> horWalls;
	bitset<64> verWalls;
	State();
	State(const State& state);
	void insertWall(int orientation, int rowWall, int colWall);
	bool ifWall(int orientation, int rowWall, int colWall); //DONE
	vector<pair<int ,State* > > genSuccessors();
	double evaluationFunction();

};

void initializeGame(const int& N, const int& M, const int& k, const int& player, const int& gametime);
void setTimeLeft(const float& time_left);
void CoordsOfWall(int orientation, int action, int& rowWall, int& colWall);
pair<int,int> pathExists(int& action, State& current);
bool validAction(int action, State& current);
bool cutoff(State& current, int depth);
int minimaxSearch(State& current);
pair<double ,int> maxValue(State& current, double alpha, double beta, int depth);
pair<double ,int> minValue(State& current, double alpha, double beta, int depth);
void initializeGame(const int& N, const int& M, const int& k, const int& player);
void setTimeLeft(const float& time_left);
void giveMove(int& m, int& r, int& c, int& moveAction);
void changeGameState(int& om, int& oro, int& oc);
int bitsetIndex(int row,int col);
vector<pair<State ,int > >* genSuccessors(State& current);
State performActionOnState(State& current, int& action);
void updateGameState(Action& action, int& whichPlayer);

int BFS(State& current, bool ifAI);
bool reached(Position& temp, bool ifAI);
vector<Position>* generateChildren(Position& temp, State& current, bool ifAI);

#endif