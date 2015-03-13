#ifndef EVAL_CPP
#define EVAL_CPP

#include <time.h>

double State::evaluate()
{
	 Eval w;
	 
 	double a = w.diff_shortest_path(*this);
 	double b = -w.shortest_path(*this,this->pn);
 	double c = w.shortest_path(*this,(this->pn==1)?(2):(1));

 	if (is_win() && (mypn==pn)) { return 100000;}
 	if (is_loss() && (mypn==pn) ) { return -100000;}
	
 	return a*abs(a) + b ;
	// double ans = w.diff_shortest_path(*this);
	// return ans;
//	return (rand()%10) ;
	// if ( pn==1 ) {
	// 	return (pos_present.r - 1)*(rand()%100);
	// } else {
	// 	return (pos_present.r - N)*(-1.0)*(rand()%100);
	// }
}

double Eval::shortest_path(State& s , int _pn)
{
	vector<vector<bool> > visited = vector<vector<bool> >(s.N+1 , vector<bool>(s.M+1,false));
	queue<Position> q;
	vector<Move> moves;

	vector< vector<int> > mindist(s.N+1 , std::vector<int>(s.M+1,-1));

	bool found_present = false;
	bool found_other = false;
	
	// check for s.pos_present
	if ( _pn==s.pn ) { //Eval shortest path for present player	
		q.push(s.pos_present);
		visited[s.pos_present.r][s.pos_present.c] = true;
		mindist[s.pos_present.r][s.pos_present.c] = 0;
		if ((s.pn==1 and s.pos_present.r==s.N) or (s.pn==2 and s.pos_present.r==1)) found_present = true;
		
		else
		{
			while (!q.empty())
			{
				Position cur = q.front();
				q.pop();
				s.get_all_jumps(moves,cur);
			
				for (vector<Move>::iterator it = moves.begin() ; it!=moves.end() ; it++)
				{				
					if ((s.pn==1 and it->to.r==s.N) or (s.pn==2 and it->to.r==1))
					{
						found_present = true;
						return mindist[cur.r][cur.c]+1;
					}
					
					if (!visited[it->to.r][it->to.c])
					{
						visited[it->to.r][it->to.c] = true;
						mindist[it->to.r][it->to.c] = mindist[cur.r][cur.c]+1;
						q.push(it->to);
					}
				}
				
				moves.clear();
				if (found_present==true) break;
			}
		}
		
		if (!found_present) 
		{
			return -1.0;
		}
	} else { //Eval shortest path for present player
		visited = vector<vector<bool> >(s.N+1 , vector<bool>(s.M+1,false));
		queue<Position> Q;
		
		Q.push(s.pos_other);
		visited[s.pos_other.r][s.pos_other.c] = true;
		mindist[s.pos_other.r][s.pos_other.c] = 0;
		if ((s.pn==1 and s.pos_other.r==1) or (s.pn==2 and s.pos_other.r==s.N)) found_other = true;
		
		else
		{
			while (!Q.empty())
			{
				Position cur = Q.front();
				Q.pop();
				s.get_all_jumps(moves,cur);
			
				for (vector<Move>::iterator it = moves.begin() ; it!=moves.end() ; it++)
				{				
					if ((s.pn==1 and it->to.r==1) or (s.pn==2 and it->to.r==s.N))
					{
						found_other = true;
						return mindist[cur.r][cur.c]+1;
					}
					
					if (!visited[it->to.r][it->to.c])
					{
						visited[it->to.r][it->to.c] = true;
						mindist[it->to.r][it->to.c] = mindist[cur.r][cur.c]+1;
						Q.push(it->to);
					}
				}
				
				moves.clear();
				if (found_other==true) break;
			}
		}
		
		if(!found_other)
		{
		//	cout << "Can't block it all off, mate." << endl; 
			return false;
		}
	}
	// // check for s.pos_other
	return -1.0;
		
	
	// return true;
}
#endif