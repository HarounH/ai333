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
	Move gen_simu_move(Player& p);
	
	// need some sort of memory
	// need to delete entries from memory after every move
	
	exploredNode* root;
	void change_root(Move m);			// m is a move on current root, state obtained on applying which is the current state { performs cleanup }
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
	
	return backed_up;
}

// returns the backed up value after simulating till cutoff 
// returns -1.0 if invalid movements => don't consider it
double MonteCarlo::simulate(Player& p, int curDepth, int cutoff)
{
	if (curDepth == cutoff or p.locState.is_endgame() or p.locState.i_won()) 	// terminal condition borrowed from mmx
	{
		if ((p.locState.shortest_path(1) == -1.0) or (p.locState.shortest_path(2) == -1.0)) return -1.0;		// => invalid move somewhere
		else return p.locState.evaluate();
	}
	
	else
	{
		Move cur = gen_simu_move(p);
		p.locState.apply_move(cur);
		
		double backed_up = simulate(p,curDepth+1,cutoff);
		
		p.locState.unapply_move(cur);
		
		return backed_up;		
	}
}
	
Move MonteCarlo::gen_simu_move(Player& p)				// a sorta-random quick move generator
{
	// with ~60% probability, move (mostly ahead) ?
	// change with number of plies
	// otherwise place a wall
}

void MonteCarlo::change_root(Move m)
{
	exploredNode* new_root;
	
	for (int i = 0 ; i<root->children.size() ; i++)
	{
		if (root->moves[i] == m) new_root = root->children[i];
		else root->children[i]->recursive_delete();
	}
	
	delete root;	// can do exploredNode::node_count--;
	root = new_root;
}
	
#endif