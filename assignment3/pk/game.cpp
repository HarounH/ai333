#ifndef GAME_CPP
#define GAME_CPP

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <utility>
#include <set>
#include "game.h"

using namespace std;

int NUMROWS, NUMCOLS, NUMWALLS, GAMETIME, TOTALWALLS; 		//Order of #define
float TIMELEFT;
#define HOR 1
#define VER 2
#define DEGREE 12
#define NULLACTION -1
#define PLAYERONE 1
#define PLAYERTWO 2
#define MININF -50000  //TO CHANGE
#define MAXINF 50000
#define MAX 1
#define MIN 0
unsigned int DEPTH = 2; //Decide depth according to time-left

bool ISFIRST;

//KABIR : 1. Define min and max functions
//		  2. ValidAction waala kabaada

//SHREYAS : 1. cutoff function that ends minimax at a depth or if game over

//TODO : 1. Evaluation function
//		 2. Path exists function (choose between union-find and DFS-BFS nonsense)
//       3. Decide if wanna implement learning (no time+minors)
//		 4. Implement wall-placement after winning...
//		 5. Get gulfriend for BOTH team-members

/*
action coordinate
		11
	7	3	6
12	4	o	2	10
	8	1	5
		9
		
*/

//Make extensible:put in numrows numcols while checking boundary conditions\
//is Valid : check number of walls



Player::Player()
{
	col = 0;
	row = 0;
	numWalls = 0;
}


Player::Player(Player& p)
{
	col = p.col;
	row = p.row;
	numWalls = p.numWalls;
	depth=p.depth;
}

Player::Player(int r, int c, int walls,int d)
{
	row = r;
	col = c;
	numWalls = walls;
	depth=d;
}

Position::Position()
{
	row = 1;
	col = 1;
	pathCost = 0;
	depth = 0;
}

Position::Position(int r, int c, int pCost)
{
	row = r;
	col = c;
	pathCost = pCost;
	depth = 0;
}

Position::Position(Player& p)
{
	row = p.row;
	col = p.col;
	pathCost = 0;
	depth = 0;
}

Action::Action(int action, int row, int col, int def) //stores exact coordinates of wall and relative movements
{
	if(action <= TOTALWALLS-1)
	{
		m = 1;
		CoordsOfWall(HOR, action, r, c);
	}
	else if(action >= TOTALWALLS && action <= 2*TOTALWALLS - 1)
	{
		m = 2;
		CoordsOfWall(VER, action, r, c);
	}
	else if(action >= 2*TOTALWALLS && action <= 2*TOTALWALLS + DEGREE)
	{
		m = 0;
		moveAction = action - 2*TOTALWALLS + 1;
		switch(moveAction)
		{
			case 1: r=row+1;
					c=col;
					break;
			case 2: c=col+1;
					r=row;
					break;
			case 3: r=row-1;
					c=col;
					break;
			case 4: r=row;
					c=col-1;
					break;
			case 5: r=row+1;
					c=col+1;
					break;
			case 6: r=row-1;
					c=col+1;
					break;
			case 7: r=row-1;
					c=col-1;
					break;
			case 8: r=row+1;
					c=col-1;
					break;
			case 9: r=row+2;
					c=col;
					break;
			case 10: r=row;
					c=col+2;
					break;
			case 11: r=row-2;
					c=col;
					break;
			case 12: r=row;
					c=col-2;
					break;
			
			
		}
		
		//Use row and col to find r and c
	}
}

Action::Action (int& moveType, int& row, int& col)
{
	m=moveType;
	r=row;
	c=col;
}

void CoordsOfWall(int orientation, int action, int& rowWall, int& colWall)
{
	if(orientation == HOR)
	{
		rowWall = (action/(NUMROWS-1)) + 2;
		colWall = (action%(NUMCOLS-1)) + 2;
	}
	else if(orientation == VER)
	{
		rowWall = ((action-64)/(NUMROWS-1)) + 2;
		colWall = ((action-64)%(NUMCOLS-1)) + 2;
	}
}



int bitsetIndex(int row,int col)
{
	return (row-2)*NUMROWS+(col-2);
}





bool validAction(int action, State& current)
{
	int rowWall, colWall;
	Player currPlayer, notCurrPlayer;
	if (current.stateType==MAX)  //CHANGES : Reversed player orders
		{
			currPlayer = current.AI;
			notCurrPlayer = current.server;
		}
		else if(current.stateType == MIN)
		{
			currPlayer = current.server;
			notCurrPlayer = current.AI;
		}

	int moveAction = action - 2*TOTALWALLS + 1;

	//cout<<"currPlayer "<<currPlayer.row<<" "<<currPlayer.col<<" "<<action<<" "<<moveAction<<endl;
	if(action <= TOTALWALLS-1)
	{
		CoordsOfWall(HOR, action, rowWall, colWall);
		if(currPlayer.numWalls == 0)
			return false;
		if(current.ifWall(HOR, rowWall, colWall-1) || current.ifWall(HOR, rowWall, colWall+1) || current.ifWall(VER, rowWall, colWall))
			return false;

		//cout<<"VALUE FOR PATH EXISTS : "<<pathExists(action, current)<<endl;;
		if(!(current.ifWall(HOR, rowWall, colWall)))
			return true;
			
	}
	else if(action >= TOTALWALLS && action <= 2*TOTALWALLS - 1)
	{
		CoordsOfWall(VER, action, rowWall, colWall);
		if(currPlayer.numWalls == 0)
			return false;
		if(current.ifWall(VER, rowWall-1,colWall) || current.ifWall(VER, rowWall+1, colWall) || current.ifWall(HOR, rowWall, colWall))
			return false;
		if(!(current.ifWall(VER, rowWall, colWall)))
			return true;
		
	}
	else if(action >= 2*TOTALWALLS && action <= 2*TOTALWALLS + DEGREE - 1)
	{
		//subject to change
		switch(moveAction)
		{
			case 1: if(currPlayer.row==9)
						return false;
					else if(currPlayer.row + 1 == notCurrPlayer.row && currPlayer.col == notCurrPlayer.col) 
						return false;
					else if(current.ifWall(HOR, currPlayer.row+1, currPlayer.col) || current.ifWall(HOR, currPlayer.row+1, currPlayer.col+1))
						return false;
					else
						return true;
					break;
			case 3: if(currPlayer.row==1)
						return false;
					else if(currPlayer.row - 1 == notCurrPlayer.row && currPlayer.col == notCurrPlayer.col) 
						return false;
					else if(current.ifWall(HOR, currPlayer.row, currPlayer.col) || current.ifWall(HOR, currPlayer.row, currPlayer.col + 1))
						return false;
					else
						return true;
					break;
			case 2: if(currPlayer.col==9) //checks bounds
						return false;
					else if(currPlayer.row == notCurrPlayer.row && currPlayer.col + 1== notCurrPlayer.col) //checks if players meet
						return false;
					else if(current.ifWall(VER, currPlayer.row+1, currPlayer.col+1) || current.ifWall(VER, currPlayer.row, currPlayer.col+1))
						return false;
					else
						return true;
					break;
			case 4: if(currPlayer.col==1) //checks bounds
						return false;
					else if(currPlayer.row == notCurrPlayer.row && currPlayer.col - 1== notCurrPlayer.col) //checks if players meet
						return false;
					else if(current.ifWall(VER, currPlayer.row+1, currPlayer.col) || current.ifWall(VER, currPlayer.row, currPlayer.col))
						return false;
					else
						return true;
					break;	
					
			case 9: if(currPlayer.row <= 7)
					{
						if(currPlayer.row+1 == notCurrPlayer.row && currPlayer.col == notCurrPlayer.col)
						{
							if(!current.ifWall(HOR, currPlayer.row+1, currPlayer.col) && !current.ifWall(HOR, currPlayer.row+1, currPlayer.col+1))
								return true;
							else
								return false;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
					break;
			case 11: if(currPlayer.row >= 3)
					{
						if(currPlayer.row-1 == notCurrPlayer.row && currPlayer.col == notCurrPlayer.col)
						{
							if(!current.ifWall(HOR, currPlayer.row, currPlayer.col) && !current.ifWall(HOR, currPlayer.row, currPlayer.col+1))
								return true;
							else
								return false;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
					break;
					
			case 10: if(currPlayer.col <= 7)
					{
						if(currPlayer.row == notCurrPlayer.row && currPlayer.col + 1 == notCurrPlayer.col)
						{
							if(!current.ifWall(VER, currPlayer.row, currPlayer.col+2) && !current.ifWall(VER, currPlayer.row+1, currPlayer.col+2))
								return true;
							else
								return false;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
					break;
					
			case 12: if(currPlayer.col >= 3)
					{
						if(currPlayer.row == notCurrPlayer.row && currPlayer.col - 1 == notCurrPlayer.col)
						{
							if(!current.ifWall(VER, currPlayer.row, currPlayer.col-1) && !current.ifWall(VER, currPlayer.row+1, currPlayer.col-1))
								return true;
							else
								return false;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
					break;
					
			case 5: if(currPlayer.row <= 8 && currPlayer.col <= 8)
					{
						if(currPlayer.row+1 == notCurrPlayer.row && currPlayer.col == notCurrPlayer.col)
						{
							if(current.ifWall(HOR, currPlayer.row+2, currPlayer.col) || current.ifWall(HOR, currPlayer.row+2, currPlayer.col+1))
							{
								if(!current.ifWall(VER, currPlayer.row+1, currPlayer.col+1) && !current.ifWall(VER, currPlayer.row+2, currPlayer.col + 1))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else if (currPlayer.row == notCurrPlayer.row && currPlayer.col + 1 == notCurrPlayer.col)
						{
							if(current.ifWall(VER, currPlayer.row, currPlayer.col+2) || current.ifWall(VER, currPlayer.row+1, currPlayer.col+2))
							{
								if(!current.ifWall(HOR, currPlayer.row+1, currPlayer.col+1) && !current.ifWall(HOR, currPlayer.row+1, currPlayer.col + 2))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else
						{
							return false;
						}
					}
					else 
					{
						return false;
					}
					break;
			case 6: if(currPlayer.row <= 8 && currPlayer.col <= 8)
					{
						if(currPlayer.row-1 == notCurrPlayer.row && currPlayer.col == notCurrPlayer.col)
						{
							if(current.ifWall(HOR, currPlayer.row-1, currPlayer.col) || current.ifWall(HOR, currPlayer.row-1, currPlayer.col+1))
							{
								if(!current.ifWall(VER, currPlayer.row, currPlayer.col+1) && !current.ifWall(VER, currPlayer.row-1, currPlayer.col + 1))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else if (currPlayer.row == notCurrPlayer.row && currPlayer.col + 1 == notCurrPlayer.col)
						{
							if(current.ifWall(VER, currPlayer.row, currPlayer.col+2) || current.ifWall(VER, currPlayer.row+1, currPlayer.col+2))
							{
								if(!current.ifWall(HOR, currPlayer.row, currPlayer.col+1) && !current.ifWall(HOR, currPlayer.row, currPlayer.col + 2))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else
						{
							return false;
						}
					}
					else 
					{
						return false;
					}
					break;
			case 7: if(currPlayer.row <= 8 && currPlayer.col <= 8)
					{
						if(currPlayer.row-1 == notCurrPlayer.row && currPlayer.col == notCurrPlayer.col)
						{
							if(current.ifWall(HOR, currPlayer.row-1, currPlayer.col) || current.ifWall(HOR, currPlayer.row-1, currPlayer.col+1))
							{
								if(!current.ifWall(VER, currPlayer.row-1, currPlayer.col) && !current.ifWall(VER, currPlayer.row, currPlayer.col))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else if (currPlayer.row == notCurrPlayer.row && currPlayer.col - 1 == notCurrPlayer.col)
						{
							if(current.ifWall(VER, currPlayer.row, currPlayer.col-1) || current.ifWall(VER, currPlayer.row+1, currPlayer.col-1))
							{
								if(!current.ifWall(HOR, currPlayer.row, currPlayer.col-1) && !current.ifWall(HOR, currPlayer.row, currPlayer.col ))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else
						{
							return false;
						}
					}
					else 
					{
						return false;
					}
					break;
					
			case 8: if(currPlayer.row <= 8 && currPlayer.col <= 8)
					{
						if(currPlayer.row+1 == notCurrPlayer.row && currPlayer.col == notCurrPlayer.col)
						{
							if(current.ifWall(HOR, currPlayer.row+2, currPlayer.col) || current.ifWall(HOR, currPlayer.row+2, currPlayer.col+1))
							{
								if(!current.ifWall(VER, currPlayer.row+1, currPlayer.col) && !current.ifWall(VER, currPlayer.row+2, currPlayer.col ))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else if (currPlayer.row == notCurrPlayer.row && currPlayer.col - 1 == notCurrPlayer.col)
						{
							if(current.ifWall(VER, currPlayer.row, currPlayer.col-1) || current.ifWall(VER, currPlayer.row+1, currPlayer.col-1))
							{
								if(!current.ifWall(HOR, currPlayer.row+1, currPlayer.col-1) && !current.ifWall(HOR, currPlayer.row+1, currPlayer.col))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else
						{
							return false;
						}
					}
					else 
					{
						return false;
					}
					break;
		}
	}
}

State::State()
{
	horWalls = 0;
	verWalls = 0;
	stateType = 1;

}

State::State(const State& state)
{
	AI = state.AI;
	server = state.server;
	stateType = state.stateType;
	horWalls = state.horWalls;
	verWalls = state.verWalls;
}

bool State::ifWall(int orientation, int rowWall, int colWall)
{
	if(rowWall < 2 || rowWall > 9 || colWall < 2 || colWall > 9)
		return false;
	
	if(orientation == HOR)
	{
		if(horWalls[bitsetIndex(rowWall,colWall)] == 1)
			return true;
		else
			return false;
	}
	else if(orientation == VER)
	{
		if(verWalls[bitsetIndex(rowWall, colWall)] == 1)
			return true;
		else
			return false;
		
	}
}

double State::evaluationFunction()
{
	double eval = 0;
	if(ISFIRST)
	{
		//we now have in current.AI.depth how far the goal is for AI and same for server
		if(AI.row == 9)
			eval = eval+ 10000;
		if(server.row == 1)
			eval = eval - 10000;

		eval=eval-AI.depth+server.depth;

		//eval = eval - AI.numWalls + server.numWalls;
		//eval = eval + 2*AI.row + 2*server.row;
		return eval;
	}
	else if(!ISFIRST)
	{
		if(AI.row == 1)
			eval = eval+ 10000;
		if(server.row == 9)
			eval = eval - 10000;
		eval=eval-AI.depth+server.depth;
		//eval = eval - AI.numWalls + server.numWalls;
		//eval = eval - 2*AI.row - 2*server.row;
		return eval;
	}
}

pair<int,int> pathExists(int& action, State& current)
{
	//Add union-find and auxilliary 81 array DS
	//cout<<"State "<<current.AI.row<<" "<<current.AI.col<<" "<<current.server.row<<" "<<current.server.col<<" "<<action<<endl;

	State tempState, tempState2;
	tempState2 = current;
	tempState = performActionOnState(tempState2, action);
	int depthForAI = BFS(tempState, true);
	int depthForServer = BFS(tempState, false);

	//cout<<depthForAI<<" "<<depthForServer<<endl;
	return make_pair(depthForAI, depthForServer);
	

}

int BFS(State& current, bool ifAI)
{
	//cout<<"BFS STARTED"<<endl;

	Player currPlayer;
	if(ifAI)
	{
		currPlayer = current.AI;  //Constructor that takes Player
	}
	else
	{
		currPlayer = current.server;
	}

	Position temp(currPlayer);

	//cout<<temp.row<<" "<<temp.col<<endl;

		multiset<Position, positionComp> frontier;
		typedef multiset<Position, positionComp>::iterator posItr;
		bool isExplored[9][9];
		bool inFrontier[9][9];
		for(int i = 0; i < 9;i++)
		{
			for(int j = 0; j < 9; j++)
			{
				inFrontier[i][j] = 0;
				isExplored[i][j] = 0;
			}
		}

		frontier.insert(temp);
		inFrontier[temp.row-1][temp.col-1] = true;
	
		while(!reached(temp, ifAI))
		{
			//cout<<"RUNNING"<<endl;
			//cout<<temp.row<<" "<<temp.col<<endl;
			// for(posItr It= frontier.begin(); It != frontier.end(); It++)
			// {
			// 	cout<<(*It).row<<" "<<(*It).col<<"...";
			// }
			//cout<<endl;
			if(frontier.empty())
				return -1;

			posItr ITR = frontier.begin();
			temp = *ITR;
			frontier.erase(ITR);
			isExplored[temp.row-1][temp.col-1] = true;
			vector<Position>* children = generateChildren(temp,current, ifAI);
			// for(vector<Position>::iterator It= children->begin(); It != children->end(); It++)
			// {
			// 	cout<<(*It).row<<" "<<(*It).col<<"...";
			// }
			
			for(int i = 0; i < children->size(); i++)
			{
				if(!isExplored[children->at(i).row - 1][children->at(i).col - 1])
				{
					if(inFrontier[children->at(i).row - 1][children->at(i).col - 1])
					{
						
						posItr it = frontier.begin();
						for(posItr it = frontier.begin(); it != frontier.end(); it++)
						{
							if((*it).row == children->at(i).row && (*it).col == children->at(i).col)
							{
								if((*it).pathCost > children->at(i).pathCost)
								{
									frontier.erase(it);
									children->at(i).depth = temp.depth+1;
									frontier.insert(children->at(i));

								}
							}
						}
					}
					else
					{
						children->at(i).depth = temp.depth+1;
						frontier.insert(children->at(i));
						inFrontier[children->at(i).row-1][children->at(i).col-1];
					}
				}
			}
		}
	return temp.depth;
}


bool reached(Position& temp, bool ifAI)
{
	if((ISFIRST && ifAI) || (!ISFIRST && !ifAI))
	{
		if(temp.row == 9)
			return true;
		else
			return false;
	}
	else if((ISFIRST && !ifAI)||(!ISFIRST && ifAI))
	{
		if(temp.row==1)
			return true;
		else
			return false;
	}
}

vector<Position>* generateChildren(Position& temp, State& current, bool IfAI)
{
	int downPathCost, upPathCost, sidePathCost;
	if((IfAI && ISFIRST) || (!IfAI && !ISFIRST))
	{
		downPathCost = -1; //1
		upPathCost = 1; //4
		sidePathCost = 0; //3
	}
	else if((IfAI && !ISFIRST) || (!IfAI && ISFIRST))
	{
		downPathCost = 1; //4
		upPathCost = -1;
		sidePathCost = 0; //3
	}

		vector<Position>* children = new vector<Position>;
		if(!current.ifWall(HOR, temp.row+1, temp.col) && !current.ifWall(HOR, temp.row+1, temp.col+1) && temp.row != 9)	//1
		{
			Position newPos(temp.row+1, temp.col, temp.pathCost+downPathCost);
			children->push_back(newPos);
		}
		if(!current.ifWall(HOR, temp.row, temp.col) && !current.ifWall(HOR, temp.row, temp.col+1) && temp.row != 1)	//3
		{
			Position newPos(temp.row-1, temp.col, temp.pathCost + upPathCost);
			children->push_back(newPos);
		}
		if(!current.ifWall(VER, temp.row, temp.col) && !current.ifWall(VER, temp.row+1, temp.col) && temp.col != 1)		//4
		{
			Position newPos(temp.row, temp.col-1, temp.pathCost + sidePathCost);
			children->push_back(newPos);
		}
		if(!current.ifWall(VER, temp.row, temp.col+1) && !current.ifWall(VER, temp.row+1, temp.col+1) && temp.col != 9)		//2
		{
			Position newPos(temp.row, temp.col+1, temp.pathCost + sidePathCost);
			children->push_back(newPos);
		}
		return children;
}

//Cutoff for both players
bool cutoff(State& current, int depth) //Need to have a global value that is true if we're player 1, false otherwise. Makes things easy
{
	if(depth == DEPTH)
		return true;
	else if(ISFIRST && current.AI.row == 9)
		return true;
	else if(!ISFIRST && current.AI.row == 1)
		return true;
		
	return false;
}

int minimaxSearch(State& current)
{
	pair<double ,int > finalState = maxValue(current, MININF, MAXINF, 0);
	cout<<"Evaluation function gives"<<finalState.first<<endl;
	

	return finalState.second;
}

//Datatype of evaluation function
pair<double ,int> maxValue(State& current, double alpha, double beta, int depth)
{
	
	//cout<<"CURRENT IN MAXVALUE "<<current.AI.row<<" "<<current.AI.col<<" "<<current.server.row<<" "<<current.server.col<<" "<<current.stateType<<endl;
	if(cutoff(current, depth))
	{
		double temp = current.evaluationFunction();
		return make_pair(temp, NULLACTION);
	}

	double value = MININF;
	int action = NULLACTION;

	//Time taken here to create successors
	vector<pair<State ,int > >::iterator Itr;
	vector<pair<State ,int > >* successors = new vector<pair<State, int > >;
	successors=genSuccessors(current);//Returns vector of succesor states and the validAction to form that states
	
	for(Itr = successors->begin(); Itr != successors->end(); Itr++)
	{
		pair<double, int> temp = minValue((*Itr).first, alpha, beta, depth+1);
		if(temp.first > value)
		{
			value = temp.first;
			action = (*Itr).second;
			//Pruning
			if(temp.first >= beta)
				return make_pair(value, action);

			alpha = max(alpha, value);
		}
	}
	return make_pair(value, action);
}

pair<double ,int> minValue(State& current, double alpha, double beta, int depth)
{
	//cout<<"CURRENT IN MINVALUE "<<current.AI.row<<" "<<current.AI.col<<" "<<current.server.row<<" "<<current.server.col<<" "<<current.stateType<<endl;

	if(cutoff(current, depth))
		return make_pair(current.evaluationFunction(), NULLACTION);

	double value = MAXINF;
	int action = NULLACTION;

	//Time taken here to create successors
	vector<pair<State ,int > >::iterator Itr;
	vector<pair<State ,int > >* successors = new vector<pair<State, int > >;
	successors=genSuccessors(current);
	for(Itr = successors->begin(); Itr != successors->end(); Itr++)
	{
		pair<double, int> temp = maxValue((*Itr).first, alpha, beta, depth+1);
		if(temp.first < value)
		{
			value = temp.first;
			action = (*Itr).second;
			//Pruning
			if(temp.first <= alpha)
				return make_pair(value, action);

			beta = min(beta, value);
		}
	}
	delete successors;
	return make_pair(value, action);
}

vector<pair<State ,int > >* genSuccessors(State& current)
{
	vector<pair<State, int > >* temp = new vector<pair<State , int > >;
	State tempState;
	//cout<<"Current Player "<<current.AI.row<<" "<<current.AI.col<<endl;
	for(int i = 2*TOTALWALLS + DEGREE - 1; i >= 0; i--)
	{
		
		if(validAction(i, current) == true)     //VALIDACTION ka kabada
		{
			pair<int,int> checkpath=pathExists(i, current);
			//State tempState;
			if(checkpath.first!=-1 && checkpath.second!=-1)
			{	
				tempState = performActionOnState(current, i);
				tempState.AI.depth=checkpath.first;
				tempState.server.depth=checkpath.second;
				//cout<<"After action : "<<tempState.AI.row<<" "<<tempState.AI.col<<" "<<i<<endl;
				temp->push_back(make_pair(tempState, i)); //Here ordering of successors can be implemented
			}
		}
	}
	
	return temp;
}


State performActionOnState(State& current, int& action)
{
	State temp(current);
	if(current.stateType == MAX)
		temp.stateType = MIN;
	else
		temp.stateType = MAX;
	int rowWall, colWall;
	if(action <= TOTALWALLS - 1)
	{
		CoordsOfWall(HOR, action, rowWall, colWall);

		temp.horWalls[bitsetIndex(rowWall,colWall)] = 1;
		if(current.stateType == MAX)
			temp.AI.numWalls--;
		else if(current.stateType == MIN)
			temp.server.numWalls--;
	}
	else if(action >= TOTALWALLS && action <= 2*TOTALWALLS - 1)
	{
		CoordsOfWall(VER, action, rowWall, colWall);
		temp.verWalls[bitsetIndex(rowWall, colWall)] = 1;
		if(current.stateType == MAX)
			temp.AI.numWalls--;
		else if(current.stateType == MIN)
			temp.server.numWalls--;
	}
	else if(action >= 2*TOTALWALLS && action < 2*TOTALWALLS + DEGREE)
	{
		//TODO
		
		if(current.stateType==MAX)
		{
			Action tempAction(action,current.AI.row,current.AI.col,0);
			temp.AI.row =tempAction.r;
			temp.AI.col=tempAction.c;
		}
		else
		{
			Action tempAction(action,current.server.row,current.server.col,0);
			temp.server.row=tempAction.r;
			temp.server.col=tempAction.c;
		}
	}
	
	return temp;
}

State currentState;

void updateGameState(Action& action, int whichPlayer)
{
	Player temp;
	if (whichPlayer==PLAYERONE)
	{
		temp = currentState.AI;
	}
	else
	{
		temp = currentState.server;
	}
	if(action.m == 1)
		{
			currentState.horWalls[bitsetIndex(action.r, action.c)] = 1;
			temp.numWalls--;
		}
		else if(action.m == 2)
		{
			currentState.verWalls[bitsetIndex(action.r, action.c)] = 1;
			temp.numWalls--;
		}
		else if(action.m == 0)
		{
			//TODO
			temp.row = action.r;
			temp.col = action.c;
		}
	if (whichPlayer==PLAYERONE)
	{
		currentState.AI=temp;
	}
	else
	{
		currentState.server=temp;
	}
}

void initializeGameState()
{

	Player first(1, NUMCOLS/2 + 1, NUMWALLS,8);
	Player second(NUMROWS, NUMCOLS/2 + 1, NUMWALLS,8);
	currentState.stateType = MAX;
	//cout<<"MAX : "<<currentState.stateType<<endl;
	
	if(ISFIRST)
	{
		currentState.AI = first;
		currentState.server = second;
	}
	else
	{
		currentState.AI = second;
		currentState.server = first;
	}
}

void initializeGame(const int& N, const int& M, const int& K, const int& player, const int& gametime)
{
	NUMROWS = N;
	NUMCOLS = M;
	NUMWALLS = K;
	TOTALWALLS = (NUMROWS-1)*(NUMCOLS-1);
	GAMETIME = gametime;
	//cout<<"NUMROWS : "<<NUMROWS<<endl;
	//cout<<"NUMCOLS : "<<NUMCOLS<<endl;

	//cout<<"NUMWALLS: "<<NUMWALLS<<endl;

	//cout<<"TOTALWALLS : "<<TOTALWALLS<<endl;

	if(player==1)
		ISFIRST = true;
	else
		ISFIRST = false;

	initializeGameState();
}

void setTimeLeft(const float& time_left)
{
	TIMELEFT = time_left;
}


void giveMove(int& m, int& r, int& c,int& moveAction)
{
	State temp(currentState);
	//cout<<"TEMP MAX : "<<temp.stateType<<endl;
	//cout<<"MINIMAX START"<<endl;
	int isBest=minimaxSearch(temp);

	Action bestAction(isBest, currentState.AI.row, currentState.AI.col, 0);
	State currr=currentState;
	int depthAI=BFS(currr,true);
	int depthForServer=BFS(currr,false);
	cout<<"My depth "<<depthAI<<" Your Depth "<<depthForServer<<endl;
	//cout<<"MINIMAX END"<<endl;
	updateGameState(bestAction, PLAYERONE); //Depending on bestAction.moveAction, or m r c, change gameState
	m = bestAction.m;
	r = bestAction.r;
	c = bestAction.c;
	moveAction=bestAction.moveAction;
}

void changeGameState(int& om, int& oro, int& oc)
{
	Action opponentAction(om, oro, oc);
	updateGameState(opponentAction, PLAYERTWO);
}

#endif
