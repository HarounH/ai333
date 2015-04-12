#ifndef SHORTEST_PATH_CPP
#define SHORTEST_PATH_CPP
/* Functions that compute shortest path. */
/* We use bfs instead of A* etc, because it really shouldn't matter.
Also, the moves are returned as : up/down/left/right. */
double State::shortest_path(int _for) {
	// cout << "####shortest_path_brk1\t _for=" << _for << "\n";
	Position 					cur;											// SNair added a lot of space. Looks better, na?
	vector<vector<bool> > 		visited(N+1 , vector<bool>(M+1,false));
	vector<vector<int> >  		mindist(N+1 , vector<int> (M+1,-1));
	queue<Position> 	  		fringe;
	vector<Move> 				moves;
	vector<Move>::iterator 		it, endv;
	                        	
	//Initiatilzation.
	int goalr = ((_for==1)?(N):(1));
	int goalc = 0;
	
	if ( _for==pn ) cur = pos_present;
	else cur = pos_other;
	
	fringe.push(cur);
	visited[cur.r][cur.c] = true;
	mindist[cur.r][cur.c] = 0;
	// cout << "####brk2\t & cur=";
	// cur.print(); cout << "\n";
	while(!fringe.empty()) {
		
		cur = fringe.front();
		fringe.pop();
		// cout << "####brk3\t & cur=";
		// cur.print(); cout << "\n";
		get_all_jumps(moves,cur);
		// cout << "####brk4\n";
		endv = moves.end(); //For the upcoming for loop. cache locality.
		// cout << "####brk5\n";
		for( it=moves.begin() ; it!=endv; ++it) {
			if ((*it).to.r == goalr ) { return (mindist[cur.r][cur.c]+1); } //DONE!
			// cout << "####brk8 recursion! \n";
			if (!visited[(*it).to.r][(*it).to.c]) {
				visited[(*it).to.r][(*it).to.c] = true;
				mindist[(*it).to.r][(*it).to.c] = mindist[cur.r][cur.c] + 1;
				fringe.push((*it).to);
			}
		}
		// cout << "####brk6\n";
		moves.clear(); //Empty the moves vector for the next iteration.
		// cout << "####brk7\n";
	}
	return mindist[goalc][goalr];
}

//--------------------------------------	A_Star territory	------------------------------------------------- //	SNair --- pls check

bool operator<(const pair<Position,pair<int,int> >& lhs, const pair<Position,pair<int,int> >& rhs)		// Position, cost_yet, heuristic
{
	return lhs.second.second > rhs.second.second;
}

double State::shortest_path_Astar(int _for) 
{
	Position 					cur;									
	vector<Move> 				moves;
	vector<Move>::iterator 		it, endv;
	vector<vector<bool> > 		explored(N+1 , vector<bool>(M+1,false));
	priority_queue<pair<Position,pair<int,int> > > fringe;									// sort by int value, which is cost_yet + heuristic
	                        	
	//Initiatilzation.
	int goalr = ((_for==1)?(N):(1));
	int goalc = 0;
	
	if ( _for == pn ) cur = pos_present;
	else 			  cur = pos_other;
	
	fringe.push( pair<Position,pair<int,int> > (cur,pair<int,int>(0,abs(cur.r - goalr))) );
	
	pair<Position,pair<int,int> > current;

	while(!fringe.empty()) 
	{	
		current = fringe.top();
		fringe.pop();
		
		if (current.first.r == goalr) return current.second.first;			// cost to goal. Done!
		if (explored[current.first.r][current.first.c]) continue;
		else explored[current.first.r][current.first.c] = true;
		
		get_all_jumps(moves,current.first);
		endv = moves.end(); //For the upcoming for loop. cache locality.

		for( it=moves.begin() ; it!=endv; it++) 	
			if (!explored[(*it).to.r][(*it).to.c]) {
				fringe.push( pair<Position,pair<int,int> > ((*it).to, pair<int,int> (current.second.first+1, current.second.first+1+abs((*it).to.r - goalr))));
			}
		
		explored[current.first.r][current.first.c] = true;
		moves.clear(); //Empty the moves vector for the next iteration.

		// priority_queue<pair<Position,pair<int,int> > > copy = fringe;
		// cout << "pq  1 : " ;
		// while (!copy.empty())
		// {
		// 	cout << copy.top().second.first << "(" << copy.top().second.second << ") " ;//"["<< copy.top().first.r << "," << copy.top().first.c << "] ";
		// 	copy.pop();
		// }
		// cout << endl;
	}	
	return -1.0;
}

//---------------------------------  ^^^	A_Star territory	^^^  -------------------------------------------- //

double State::shortest_path(int _for, Position& goal) { //Shortest path to any goal.
	
	Position 					cur;											
	vector<vector<bool> > 		visited(N+1 , vector<bool>(M+1,false));
	vector<vector<int> >  		mindist(N+1 , vector<int> (M+1,-1));
	queue<Position> 	  		fringe;
	vector<Move> 				moves;
	vector<Move>::iterator 		it, endv;
	//Initiatilzation.
	int goalr = goal.r;
	int goalc = goal.c;
	if ( _for==pn ) {
		cur = pos_present;
	} else {
		cur = pos_other;
	}
	fringe.push(cur);
	visited[cur.r][cur.c] = true;
	mindist[cur.r][cur.c] = 0;

	while(!fringe.empty()) {
		cur = fringe.front();
		fringe.pop();
		get_all_jumps(moves,cur);
		endv=moves.end(); //for the upcoming for loop. cache locality!
		for( it=moves.begin() ; it!=endv; ++it) {
			if (((*it).to.r == goalr)&&((*it).to.c == goalc) ) { return (mindist[cur.r][cur.c]+1); } //DONE!
			if (!visited[(*it).to.r][(*it).to.c]) {
				visited[(*it).to.r][(*it).to.c] = true;
				mindist[(*it).to.r][(*it).to.c] = mindist[cur.r][cur.c] + 1;
				fringe.push((*it).to);
			}
		}
		moves.clear(); //Empty the moves vector for the next iteration.
	}
	return mindist[goalc][goalr]; //-1 of ot osnt reached.
}
#endif