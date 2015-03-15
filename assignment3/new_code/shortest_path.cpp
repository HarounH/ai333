#ifndef SHORTEST_PATH_CPP
#define SHORTEST_PATH_CPP
/* Functions that compute shortest path. */
double State::shortest_path(int _for) {
	Position cur;
	vector< vector<bool> > visited(N+1 , std::vector<bool>(M+1,false));
	std::vector< std::vector<int> > mindist(N+1 , std::vector<int>(M+1,-1));
	queue<Position> fringe;
	vector<Move> moves;
	std::vector<Move>::iterator it;
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

	while(!q.empty()) {
		cur = q.front();
		q.pop();
		get_all_jumps(moves,cur);
		for( it=moves.begin(), end=moves.end() ; it!=end; ++it) {
			if (*it.to.r == goalr ) { return (mindist[cur.r][cur.c]+1); } //DONE!
			if (!visited[*it.to.r][*it.to.c]) {
				visited[*it.to.r][*it.to.c] = true;
				mindist[*it.to.r][*it.to.c] = mindist[cur.r][cur.c] + 1;
				fringe.push(*it);
			}
		}
		moves.clear(); //Empty the moves vector for the next iteration.
	}
	return mindist[goalc][goalr];
}

double shortest_path(int forpn, Position& goal) { //Shortest path to any goal.
	Position cur;
	vector< vector<bool> > visited(N+1 , std::vector<bool>(M+1,false));
	std::vector< std::vector<int> > mindist(N+1 , std::vector<int>(M+1,-1)); //initialized to -1.
	queue<Position> fringe;
	vector<Move> moves;
	std::vector<Move>::iterator it;
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

	while(!q.empty()) {
		cur = q.front();
		q.pop();
		get_all_jumps(moves,cur);
		for( it=moves.begin(), end=moves.end() ; it!=end; ++it) {
			if ((*it.to.r == goalr)&&(*it.to.c == goalc) ) { return (mindist[cur.r][cur.c]+1); } //DONE!
			if (!visited[*it.to.r][*it.to.c]) {
				visited[*it.to.r][*it.to.c] = true;
				mindist[*it.to.r][*it.to.c] = mindist[cur.r][cur.c] + 1;
				fringe.push(*it);
			}
		}
		moves.clear(); //Empty the moves vector for the next iteration.
	}
	return mindist[goalc][goalr]; //-1 of ot osnt reached.
}
#endif