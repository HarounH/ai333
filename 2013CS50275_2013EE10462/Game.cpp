#include "Game.h"

void GameState::applyMove(Move& move)
{
	if(move.choice == 0 && move.pos != make_pair(0, 0))
	{
		if(currentPlayer() == 0)
			player1 = move.pos;
		else
			player2 = move.pos;
	}
	else if(move.choice == 1)
	{
		horWalls[move.pos.first][move.pos.second] = true;
		horWalls[move.pos.first][move.pos.second-1] = true;
		if(currentPlayer() == 0) 
			numWallsA--;
		else
			numWallsB--;
	}
	else if(move.choice == 2)
	{
		verWalls[move.pos.first][move.pos.second] = true;
		verWalls[move.pos.first-1][move.pos.second] = true;
		if(currentPlayer() == 0) 
			numWallsA--;
		else
			numWallsB--;
	}
	turn = !turn;
}

void GameState::unMove(Move& move)   //Game states aren't copied. There are just moves and unmoves in the minimax tree.
{
	turn = !turn;
	if(move.choice == 0)
	{
		if(currentPlayer() == 0) 
			player1 = move.pos;
		else
			player2 = move.pos;
	}
	else if(move.choice == 1)
	{
		horWalls[move.pos.first][move.pos.second] = false;
		horWalls[move.pos.first][move.pos.second-1] = false;
		if(currentPlayer() == 0) 
			numWallsA++;
		else
			numWallsB++;
	}
	else if(move.choice == 2)
	{
		verWalls[move.pos.first][move.pos.second] = false;
		verWalls[move.pos.first-1][move.pos.second] = false;
		if(currentPlayer() == 0) 
			numWallsA++;
		else
			numWallsB++;
	}
}

void GameState::getValidMoves(vector<Move>& possibleMoves)
{
	Pos currentPos, otherPos;
	if(currentPlayer() == 0)
	{
		currentPos = player1;
		otherPos = player2;
	}
	else
	{
		currentPos = player2;
		otherPos = player1;
	}
	getValidTraversals(possibleMoves, currentPos, otherPos);   //traversal type moves
	getValidWallPlacements(possibleMoves);  //wall placing moves
}

void GameState::addMove(vector<Move>& possibleMoves, Move& a)   //helper
{
	possibleMoves.push_back(a);
}

void GameState::getValidTraversals(vector<Move>& possibleMoves, Pos& currentPos, Pos& otherPos)
{
	Move a(0, currentPos);
	int n = verWalls.size();
	int m = verWalls[0].size();
	if( (a.pos.first - 1 >= 0) && !horWalls[currentPos.first][currentPos.second] )    //Move up
	{
		a.pos.first -= 1;
		if(a.pos != otherPos)    //Other player not in the way
		{
			addMove(possibleMoves, a);
		}
		else                    //Other player in the way
		{
			if( (a.pos.first - 1 >= 0) && !horWalls[a.pos.first][a.pos.second] )      //jump
			{
				a.pos.first -= 1;
				addMove(possibleMoves, a);
				a.pos.first += 1;
			}
			else if( (a.pos.second - 1 >= 0) && !verWalls[a.pos.first][a.pos.second] )  //upleft diagonal move
			{
				a.pos.second -= 1;
				addMove(possibleMoves, a);
				a.pos.second += 1;
			}
			else if( (a.pos.second + 1 < m) && !verWalls[a.pos.first][a.pos.second+1] )  //upright diagonal move
			{
				a.pos.second += 1;
				addMove(possibleMoves, a);
				a.pos.second -= 1;
			}
		}
		a.pos.first += 1;
	}
	
	if( (a.pos.first + 1 < n) && !horWalls[currentPos.first+1][currentPos.second] )    //Move down
	{
		a.pos.first += 1;
		if(a.pos != otherPos)    //Other player not in the way
		{
			addMove(possibleMoves, a);
		}
		else                    //Other player in the way
		{
			if( (a.pos.first + 1 < n) && !horWalls[a.pos.first+1][a.pos.second] )      //jump
			{
				a.pos.first += 1;
				addMove(possibleMoves, a);
				a.pos.first -= 1;
			}
			else if( (a.pos.second - 1 >= 0) && !verWalls[a.pos.first][a.pos.second] )  //downleft diagonal move
			{
				a.pos.second -= 1;
				addMove(possibleMoves, a);
				a.pos.second += 1;
			}
			else if( (a.pos.second + 1 < m) && !verWalls[a.pos.first][a.pos.second+1] )  //downright diagonal move
			{
				a.pos.second += 1;
				addMove(possibleMoves, a);
				a.pos.second -= 1;
			}
		}
		a.pos.first -= 1;
	}
	
	if( (a.pos.second - 1 >= 0) && !verWalls[currentPos.first][currentPos.second] )    //Move left
	{
		a.pos.second -= 1;
		if(a.pos != otherPos)    //Other player not in the way
		{
			addMove(possibleMoves, a);
		}
		else                    //Other player in the way
		{
			if( (a.pos.second - 1 >= 0) && !verWalls[a.pos.first][a.pos.second] )      //jump
			{
				a.pos.second -= 1;
				addMove(possibleMoves, a);
				a.pos.second += 1;
			}
			else if( (a.pos.first - 1 >= 0) && !horWalls[a.pos.first][a.pos.second] )  //leftup diagonal move
			{
				a.pos.first -= 1;
				addMove(possibleMoves, a);
				a.pos.first += 1;
			}
			else if( (a.pos.first + 1 < n) && !horWalls[a.pos.first+1][a.pos.second] )  //leftdown diagonal move
			{
				a.pos.first += 1;
				addMove(possibleMoves, a);
				a.pos.first -= 1;
			}
		}
		a.pos.second += 1;
	}
	
	if( (a.pos.second + 1 < m) && !verWalls[currentPos.first][currentPos.second+1] )    //Move right
	{
		a.pos.second += 1;
		if(a.pos != otherPos)    //Other player not in the way
		{
			addMove(possibleMoves, a);
		}
		else                    //Other player in the way
		{
			if( (a.pos.second + 1 < m) && !verWalls[a.pos.first][a.pos.second+1] )      //jump
			{
				a.pos.second += 1;
				addMove(possibleMoves, a);
				a.pos.second -= 1;
			}
			else if( (a.pos.first - 1 >= 0) && !horWalls[a.pos.first][a.pos.second] )  //rightup diagonal move
			{
				a.pos.first -= 1;
				addMove(possibleMoves, a);
				a.pos.first += 1;
			}
			else if( (a.pos.first + 1 < m) && !horWalls[a.pos.first+1][a.pos.second] )  //rightdown diagonal move
			{
				a.pos.first += 1;
				addMove(possibleMoves, a);
				a.pos.first -= 1;
			}
		}
		a.pos.second -= 1;
	}
}

void GameState::getValidWallPlacements(vector<Move>& possibleMoves)
{
	int wallsLeft = (currentPlayer() == 0) ? numWallsA : numWallsB;
	if(wallsLeft == 0)
		return;
	int n = horWalls.size();
	int m = horWalls[0].size();
	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j < m; j++)
		{
			if(!horWalls[i][j-1] && !horWalls[i][j] && !(verWalls[i-1][j] && verWalls[i][j]))   //place horizontal wall
			{
				Move a(1, i, j);
				addMove(possibleMoves, a);
			}
			
			if(!verWalls[i-1][j] && !verWalls[i][j] && !(horWalls[i][j-1] && horWalls[i][j]))   //place vertical wall
			{
				Move a(2, i, j);
				addMove(possibleMoves, a);
			}
		}
	}
}

int GameState::shortestDistanceToGoal(Pos& start, int goalRow)
{
	int n = verWalls.size();
	int m = verWalls[0].size();
	typedef pair<Pos, int> posInt;
	priority_queue<posInt, vector<posInt>, PosComparator> q;
	posInt startInt = make_pair(start, 0);
	q.push(startInt);
	unordered_map<Pos, int, PosHasher> distMap;
	distMap[start] = 0;
	while(!q.empty())
	{
		posInt p = q.top(); 
		q.pop();
		if(p.first.first == goalRow)
		{
			return distMap[p.first];
		}
		if( (p.first.first - 1 >= 0) && !horWalls[p.first.first][p.first.second] ) //move up
		{
			Pos np = make_pair(p.first.first-1, p.first.second);
			if(distMap.find(np) == distMap.end())
			{
				distMap[np] = distMap[p.first]+1;
				posInt npp = (goalRow > p.first.first) ? make_pair(np, p.second + 2) : make_pair(np, p.second);
				q.push(npp);
			}
		}
		
		if( (p.first.first + 1 < n) && !horWalls[p.first.first+1][p.first.second] ) //move down
		{
			Pos np = make_pair(p.first.first+1, p.first.second);
			if(distMap.find(np) == distMap.end())
			{
				distMap[np] = distMap[p.first]+1;
				posInt npp = (goalRow > p.first.first) ? make_pair(np, p.second) : make_pair(np, p.second + 2);
				q.push(npp);
			}
		}
		
		if( (p.first.second - 1 >= 0) && !verWalls[p.first.first][p.first.second] ) //move left
		{
			Pos np = make_pair(p.first.first, p.first.second-1);
			if(distMap.find(np) == distMap.end())
			{
				distMap[np] = distMap[p.first]+1;
				posInt npp = make_pair(np, p.second + 1);
				q.push(npp);
			}
		}
		
		if( (p.first.second + 1 < m) && !verWalls[p.first.first][p.first.second+1] ) //move right
		{
			Pos np = make_pair(p.first.first, p.first.second+1);
			if(distMap.find(np) == distMap.end())
			{
				distMap[np] = distMap[p.first]+1;
				posInt npp = make_pair(np, p.second + 1);
				q.push(npp);
			}
		}
		
	}
	return -1;
}

void GameState::print()
{
	int n = verWalls.size();
	int m = verWalls[0].size();
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(horWalls[i][j])
				cout <<"-";
			else
				cout<<" ";
		}
		cout<<"\n";
		for(int j = 0; j < m; j++)
		{
			if(verWalls[i][j])
				cout <<"|";
			else
				cout<<" ";
		}
		cout <<"\n";
	}
}