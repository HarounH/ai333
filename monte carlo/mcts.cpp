#ifndef MCTS_CPP
#define MCTS_CPP

#include "exploredNode.cpp"
// MONTE CARLO TREE SEARCH
// http://mcts.ai/about/index.html

// cutoff might become neg, check!

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
	if (curDepth > cutoff+3) return -1.0;			// {review if can be handled better}
	
	if (curDepth == cutoff or p.locState.is_endgame() or p.locState.i_won()) 	// terminal condition borrowed from mmx
	{
		if ((p.locState.shortest_path(1) == -1.0) or (p.locState.shortest_path(2) == -1.0)) return -1.0;		// => invalid move somewhere
		else return p.locState.evaluate();
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
	int temp = rand()%20;
	
	if (temp<12)		// prob 3/5 move { randomly }
	{
		vector<Move> jumps;
		p.locState.get_all_jumps(jumps);
		
		if (jumps.size() == 0) return pair<bool,Move>(false,Move(6,6,6));
		
		int cur = rand()%jumps.size();
		return pair<bool,Move>(true,jumps[cur]);
	}
	
	else 		// prob 3/20, place wall close to opponent, 5/20 => completely random wall
	{
		if (p.locState.n_present_walls>0 and temp<15) return pair<bool,Move>(true,p.locState.get_biased_random_wall());
		else if (p.locState.n_present_walls>0 and temp<20) return pair<bool,Move>(true,p.locState.get_complete_random_wall());
		
		else		// jump
		{
			vector<Move> jumps;
			p.locState.get_all_jumps(jumps);
		
			if (jumps.size() == 0) return pair<bool,Move>(false,Move(6,6,6));
		
			int cur = rand()%jumps.size();
			return pair<bool,Move>(true,jumps[cur]);
		}
	}
}

void MonteCarlo::change_root(Player& p, Move m)
{
	exploredNode* new_root;
	
	for (int i = 0 ; i<root->children.size() ; i++)
	{
		if (root->moves[i] == m)
		{
			if(root->children[i]) new_root = root->children[i];			// if pointer is not NULL pointer
			
			else
			{
				p.locState.apply_move(m);
				new_root = new exploredNode(p);
				p.locState.unapply_move(m);
			}
		}
		 
		else if (root->children[i]) root->children[i]->recursive_delete();
	}
	
	delete root;	
	exploredNode::node_count--;
	root = new_root;
}
	
#endif