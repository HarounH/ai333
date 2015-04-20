#ifndef MCTS_CPP
#define MCTS_CPP

#include "exploredNode.cpp"
// MONTE CARLO TREE SEARCH
// http://mcts.ai/about/index.html

// curDepth might exceed current, check!

class MonteCarlo
{
public:

	MonteCarlo() {};
	void init(Player& p);
	double MCTS(Player& p, exploredNode* current, int curDepth, int cutoff, float time_limit);
	double simulate(Player& p, int curDepth, int cutoff);	
	pair<bool,Move> gen_simu_move(Player& p);
	
	// need some sort of memory
	// need to delete entries from memory after every move
	
	exploredNode* root;
	void change_root(Player& p, Move m);			// m is a move on current root, state obtained on applying which is the current state { performs cleanup }
};

void MonteCarlo::init(Player& p)
{
	root = new exploredNode(p);
}

// returns backed up value
double MonteCarlo::MCTS(Player& p, exploredNode* current, int curDepth, int cutoff, float time_limit)	// update best_move!
{
	int i = current->choose_move();

	double backed_up;

	if (current->times_moves_explored[i] > 1)									// move has been explored (initialised to 1!)
	{	
		p.locState.apply_move(current->moves[i]);								// apply move
		backed_up = MCTS(p, current->children[i], curDepth+1, cutoff,time_limit);	
	} 
	else													// unexplored move
	{
		p.locState.apply_move(current->moves[i]);
		current->children[i] = new exploredNode(p);			// making the new node, setting pointer 
		backed_up = simulate(p,curDepth+1,cutoff);
	}
	
	p.locState.unapply_move(current->moves[i]);
	current->book_keeping(i,backed_up);						// increments counts and moves values, ignore if backed_up = -1
	
	if (curDepth == 0)			// update best move
	{
		int best = 0;
		
		for (int m = 0; m<current->moves.size(); m++)
			if (current->avg_so_far[m] > current->avg_so_far[best]) best = m;
		
		p.best_move = current->moves[best];
	}
	
	return backed_up;
}

// returns the backed up value after simulating till cutoff 
// returns -1.0 if invalid movements => don't consider it
double MonteCarlo::simulate(Player& p, int curDepth, int cutoff)
{
	if (curDepth > cutoff+3) return -1.0;			// {review if can be handled better} - i'm not sure i get this.
	
	if (curDepth == cutoff or p.locState.is_endgame() or p.locState.i_won()) 	// terminal condition borrowed from mmx
	{
		int sp1,sp2; //shortest paths for player 1 and player 2.
		Move tempm = p.locState.causal_moves.top();
		p.locState.causal_moves.pop();
		//Set the move's my_shortest_path, op_shortest_path.
		
		
		if ( tempm.my_shortest_path < 0) {
			sp1 = p.locState.shortest_path_Astar(p.pn);
			tempm.my_shortest_path = sp1;
		}
		if ( tempm.op_shortest_path < 0) {
			sp2 = p.locState.shortest_path_Astar( ((p.pn==1)?(2):(1)) ); //other player.
			tempm.op_shortest_path = sp2;	
		}
		
		p.locState.causal_moves.push(tempm);

		//CHECK FOR RECOMPUTATION.
		if ((sp1 == -1.0) or (sp2 == -1.0)) return -1.0;		// => invalid move somewhere
		else return p.locState.evaluate(); // no computation, hopefully.
	}
			
	else
	{
		pair<bool,Move> cur = gen_simu_move(p);
		if (cur.first == false) return -1.0;
		

		p.locState.apply_move(cur.second);
		double backed_up = simulate(p,curDepth+1,cutoff);
		p.locState.unapply_move(cur.second);
		
		return backed_up;		
	}
}
	
pair<bool,Move> MonteCarlo::gen_simu_move(Player& p)				// a sorta-random quick move generator
{																	// first bool if true => definitely invalid state { opposite may not hold }
	int temp = fastrand()%20;
	//after a win, simulate only walls.
	if (!(p.locState.i_won()) || temp<12)		// prob 3/5 move { randomly }
	{
		vector<Move> jumps;
		p.locState.get_all_jumps(jumps);
		
		if (jumps.size() == 0) return pair<bool,Move>(false,Move(6,6,6));
		
		int cur = fastrand()%jumps.size();
		return pair<bool,Move>(true,jumps[cur]);
	}
	
	else 		// prob 6/20, place wall close to opponent, 2/20 => completely random wall
	{
		if (p.locState.n_present_walls>0 and temp<18) return pair<bool,Move>(true,p.locState.get_biased_random_wall());
		else if (p.locState.n_present_walls>0 and temp<20) return pair<bool,Move>(true,p.locState.get_complete_random_wall());
		
		else if (!p.locState.i_won())		// jump only if i havent won.
		{
			vector<Move> jumps;
			p.locState.get_all_jumps(jumps);
		
			if (jumps.size() == 0) return pair<bool,Move>(false,Move(6,6,6));
		
			int cur = fastrand()%jumps.size();
			return pair<bool,Move>(true,jumps[cur]);
		} 
		else {
			//I won.
			Move m;
			m.m=0;
			m.r=0;
			m.c=0;
			return pair<bool,Move>(true,m); //returning the pass move.
			//ASSERT : Possible cause of segfaults.
		}
	}
}

void MonteCarlo::change_root(Player& p, Move m)
{
	exploredNode* new_root;
	
	for (int i = 0 ; i<root->children.size() ; i++)
	{
		if (root->moves[i] == m) //NOTE : Prevents n nodes from being executed.
		{
			if(root->children[i]) new_root = root->children[i];			// if pointer is not NULL pointer --- H: its fine.
			
			else
			{
				p.locState.apply_move(m);
				new_root = new exploredNode(p);
				p.locState.unapply_move(m);
			}
		}
		//TODO: Insert this child into a hashtable of sorts? - just H thoughts. 
		//TODO: Remove this? - surag hallucinations.
		//else if (root->children[i]) root->children[i]->recursive_delete();
	}
	
	//delete root;
	exploredNode::node_count--;
	root = new_root;
}
	
#endif