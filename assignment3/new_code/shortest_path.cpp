#ifndef SHORTEST_PATH_CPP
#define SHORTEST_PATH_CPP
/* Functions that compute shortest path. */
double State::shortest_path(int _for) {
	// cout << "####shortest_path_brk1\t _for=" << _for << "\n";
	Position cur;
	vector< vector<bool> > visited(N+1 , std::vector<bool>(M+1,false));
	std::vector< std::vector<int> > mindist(N+1 , std::vector<int>(M+1,-1));
	queue<Position> fringe;
	vector<Move> moves;
	std::vector<Move>::iterator it,endv;
	//Initiatilzation.
	int goalr = ((_for==1)?(N):(1));
	int goalc = 0;
	if ( _for==pn ) {
		cur = pos_present;
	} else {
		cur = pos_other;
	}
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

double State::shortest_path(int _for, Position& goal) { //Shortest path to any goal.
	Position cur;
	vector< vector<bool> > visited(N+1 , std::vector<bool>(M+1,false));
	std::vector< std::vector<int> > mindist(N+1 , std::vector<int>(M+1,-1)); //initialized to -1.
	queue<Position> fringe;
	vector<Move> moves;
	std::vector<Move>::iterator it,endv;
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