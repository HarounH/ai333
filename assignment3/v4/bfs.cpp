#ifndef BFS_CPP
#define BFS_CPP

#include <queue>

bool State::paths_exists() 
{
	vector<vector<bool> > visited = vector<vector<bool> >(N+1 , vector<bool>(M+1,false));
	queue<Position> q;
	vector<Move> moves;
	bool found_present = false;
	bool found_other = false;
	
	// check for pos_present
	
	q.push(pos_present);
	visited[pos_present.r][pos_present.c] = true;
	if ((pn==1 and pos_present.r==N) or (pn==2 and pos_present.r==1)) found_present = true;
	
	else
	{
		while (!q.empty())
		{
			Position cur = q.front();
			q.pop();
			get_all_jumps(moves,cur);
		
			for (vector<Move>::iterator it = moves.begin() ; it!=moves.end() ; it++)
			{				
				if ((pn==1 and it->to.r==N) or (pn==2 and it->to.r==1))
				{
					found_present = true;
					break;
				}
				
				if (!visited[it->to.r][it->to.c])
				{
					visited[it->to.r][it->to.c] = true;
					q.push(it->to);
				}
			}
			
			moves.clear();
			if (found_present==true) break;
		}
	}
	
	if (found_present==false) return false;
	
	// check for pos_other
	
	visited = vector<vector<bool> >(N+1 , vector<bool>(M+1,false));
	queue<Position> Q;
	
	Q.push(pos_other);
	visited[pos_other.r][pos_other.c] = true;
	if ((pn==1 and pos_other.r==1) or (pn==2 and pos_other.r==N)) found_other = true;
	
	else
	{
		while (!Q.empty())
		{
			Position cur = Q.front();
			Q.pop();
			get_all_jumps(moves,cur);
		
			for (vector<Move>::iterator it = moves.begin() ; it!=moves.end() ; it++)
			{				
				if ((pn==1 and it->to.r==1) or (pn==2 and it->to.r==N))
				{
					found_other = true;
					break;
				}
				
				if (!visited[it->to.r][it->to.c])
				{
					visited[it->to.r][it->to.c] = true;
					Q.push(it->to);
				}
			}
			
			moves.clear();
			if (found_other==true) break;
		}
	}
	
	return found_other;	
}

#endif