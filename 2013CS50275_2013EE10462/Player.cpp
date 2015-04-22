#include "Player.h"

typedef double Feature;    //readability

class BasePlayer : public Player
{

public:
	double operator()(GameState& gs, int myPlayer)
	{
		double eval = 0;
		int dist1, dist2;
		int walls1, walls2;
		Pos mine, his;
		
		Feature wallsDiff = 0, distanceDiff = 0, winning = 0;
		
		if(myPlayer == 0)
		{
			mine = gs.player1Pos();
			his = gs.player2Pos();
			dist1 = gs.shortestDistanceToGoal(mine, gs.length()-1);
			dist2 = gs.shortestDistanceToGoal(his, 0);
			walls1 = gs.player1Walls();
			walls2 = gs.player2Walls();
			if(gs.player1Win())
				winning = 10000;
			else if(gs.player2Win())
				winning = -10000;
		}
		else
		{
			mine = gs.player2Pos(); 
			his = gs.player1Pos();
			dist1 = gs.shortestDistanceToGoal(mine, 0);
			dist2 = gs.shortestDistanceToGoal(his, gs.length()-1);
			walls1 = gs.player2Walls();
			walls2 = gs.player1Walls();
			if(gs.player2Win())
				winning = 10000;
			else if(gs.player1Win())
				winning = -10000;
		}
		if(walls1 != 0)
			distanceDiff = dist2 - dist1; 
		wallsDiff = walls1 - walls2;
		if(wallsDiff < -2)
			eval += 20 * (wallsDiff + 2);
		eval += 8 * distanceDiff;
		eval -= dist1;
		eval += winning;
		return eval;
	}
};

class RandPlayer : public Player
{

public:
	double operator()(GameState& gs, int myPlayer)
	{
		double eval;

		eval = rand() % 20;
		return eval;
	}
};