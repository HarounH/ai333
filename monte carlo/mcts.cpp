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
	cout << "\n\n #######################################\n \t\tBEFORE MCTS"; p.locState.print();
	
	double backed_up;

	if (current->times_moves_explored[i] > 1)									// move has been explored (initialised to 1!)
	{
		p.locState.apply_move(current->moves[i]);								// apply move
		cout << "#\t\tbrk1-before mcts in mcts\n";
		backed_up = MCTS(p, current->children[i], curDepth+1, cutoff,time_limit);	
		cout << "#\t\tbrk2-after mcts in mcts\n";
	}
	
	else													// unexplored move
	{
		p.locState.apply_move(current->moves[i]);
		current->children[i] = new exploredNode(p);			// making the new node, setting pointer 
		cout << "\t\t#brk3-before simulate in mcts\n";
		backed_up = simulate(p,curDepth+1,cutoff);
		cout << "\t\t#brk4-after simulate in mcts\n";
	}
	cout << "\t#brk5-before unapply, move applied is,"; current->moves[i].print();

	p.locState.unapply_move(current->moves[i]);
	cout << "\t#brk-6 done unapply. unapplied move is:\n";
	// p.locState.print();
	cout << "\tbrk-7 time for bookkeeping.\n";
	current->book_keeping(i,backed_up);						// increments counts and moves values, ignore if backed_up = -1
	cout << "\t#brk-8 done with book keeping\n";
	if (curDepth == 0)			// update best move
	{
		int best = 0;
		
		for (int m = 0; m<current->moves.size(); m++) {
			if (current->avg_so_far[m] > current->avg_so_far[best]) best = m;
		}
		
		p.best_move = current->moves[best];
	}

	cout << "\t\t Done with mcts\n#########################################\n";
	return backed_up;
}

// returns the backed up value after simulating till cutoff 
// returns -1.0 if invalid movements => don't consider it
double MonteCarlo::simulate(Player& p, int curDepth, int cutoff)
{
	if (curDepth > cutoff + 3) {return -1.0;}
	
	else if (curDepth == cutoff or p.locState.is_endgame() or p.locState.i_won() or p.locState.i_lost()) 	// terminal condition borrowed from mmx
	{
		int sp1,sp2; //shortest paths for player 1 and player 2.
		Move tempm = p.locState.causal_moves.top();
		p.locState.causal_moves.pop();
		//Set the move's my_shortest_path, op_shortest_path. tempm.print();
		
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
		if ((sp1<0 ) or (sp2<0)) return -1.0;		// => invalid move somewhere
		else 
		{
			return p.locState.evaluate(); 			// no computation, hopefully.
			
			// if (fabs(ret)>5000)
			// {
			// 	return ret/exp(2.5*(curDepth-2));
			// }
			//
			// else return ret;
		}
	}
	else
	{
		cout << "\t\t#brk8 - about to gen simu move - in simu, (curdept,cutoff)=" << curDepth << "," << cutoff << ")\n";
		pair<bool,Move> cur = gen_simu_move(p);
		cout << "\t\t#brk9 - got move\n";
		if (cur.first == false) return -1.0;
		

		p.locState.apply_move(cur.second);
		cout << "\t\t\t\t#brk11-applying the move="; cur.second.print();
		cout << "\t\t\t brk12 - the state in simulation is\n"; p.locState.print();

		double backed_up = simulate(p,curDepth+1,cutoff);
		p.locState.unapply_move(cur.second);
		
		return backed_up;		
	}
}
	
pair<bool,Move> MonteCarlo::gen_simu_move(Player& p)				// a sorta-random quick move generator
{																	// first bool if true => definitely invalid state { opposite may not hold }
	int temp = fastrand()%20;
	
	/*
		player lost, has he?
			not only jump but save shall he too.
		but if won the player has, jump he shall not.
			for wasted it is to jump after a win.
	*/


	if ( (!(p.locState.present_won())) && temp<10)		// prob 3/5 MOVE { randomly } OR if the present player has NOT won.
	{
		vector<Move> jumps;
		p.locState.get_all_jumps(jumps);
		// if jump he cant, then the game move cannot.
		if (jumps.size() == 0) return pair<bool,Move>(false,Move(6,6,6));
		
		int cur = fastrand()%jumps.size();
		return pair<bool,Move>(true,jumps[cur]);
	}
	else 		// prob 6/20, place wall close to opponent, 2/20 => completely random wall
	{ // we know that either : temp>=12 OR the player has won.			
		if ( p.locState.present_won() ) {
			//player has won, hence, he must either pass or place a wall. 
			/*
				if walls the player has,
					A biased wall he places with probability 16/20.
					A random wall he places with probability 18/20
				else, 
					pass he shall
			*/
			cout << "\t###looks like the present player has won :(\n";
			if (p.locState.n_present_walls>0 and temp<16) {
				cout << "\t\t\t#brk9-in gensimumove-trying to get biased wall\n";
				return pair<bool,Move>(true,p.locState.get_biased_random_wall());

			} else if (p.locState.n_present_walls>0 and temp<20) {
				cout << "\t\t\t#brk10-in gensimumove-trying to get completely random wall.\n";
				return pair<bool,Move>(true,p.locState.get_complete_random_wall());
			} else {
				Move m;
				 m.m=0;m.r=0;m.c=0; m.to=make_pair(0,0);
				 m.from = p.locState.pos_present;
				 m.eval = -1.0;

				return pair<bool,Move>( true, m );
			}

		} else {
			// temp be greater than 12 and won the player has not.
			/*
				In such a case, the player shall place a wall
					the probabilities shall be 18/20 for bias and 2/20 for random.
				if place a wall he cannot, then jump he shall. Why? For pass he cannot.
			*/
			cout << "\t### the present player has not won :|\n";
			if (p.locState.n_present_walls>0 and temp<18) {
				cout << "\t\t\t#brk9-in gensimumove-trying to get biased wall\n";
				return pair<bool,Move>(true,p.locState.get_biased_random_wall());
			} else if (p.locState.n_present_walls>0 and temp<20) {
				cout << "\t\t\t#brk10-in gensimumove-trying to get completely random wall.\n";
				return pair<bool,Move>(true,p.locState.get_complete_random_wall());
			} else { //wall cant be placed.
				vector<Move> jumps;
				p.locState.get_all_jumps(jumps);
				if (jumps.size() == 0) return pair<bool,Move>(false,Move(6,6,6));
				int cur = fastrand()%jumps.size();
				return pair<bool,Move>(true,jumps[cur]);	
			}
			
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