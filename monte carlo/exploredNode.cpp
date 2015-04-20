#ifndef EXPLORED_NODE_CPP
#define EXPLORED_NODE_CPP

// FOR MCTS
#define C 12

static unsigned int g_seed;
inline void fast_srand( int seed )
	{g_seed = seed;}

inline int fastrand() { 
  g_seed = (214013*g_seed+2531011); 
  return (g_seed>>16)&0x7FFF; 
} 

class exploredNode
{
public:

	exploredNode(Player& p);
	//~exploredNode();
	void recursive_delete();
	
	vector<exploredNode*> children;
	vector<Move> moves;
	int total_times_explored;
	vector<int> times_moves_explored;
	vector<double> avg_so_far;
	vector<double> value_of_moves;
	bool is_my_move;								// choosing nodes depends on player
		
	int choose_move();								// return index of move
	void book_keeping(int i, double backed_up);		// explored ith move
	int next_move;									// update after every round of book keeping
	
	static int node_count;
	
	// when calling delete on exploredNode
	// recursively call a delete function on its children 
	// set pointer of its parent to NULL!	(if required)
	// relocate root pointer
};

int exploredNode::choose_move()
{
	int temp = fastrand()%10;
	
	if (temp<9) {return next_move;}			// 90% return best valued move
	else 
	{
		int cur = fastrand()%moves.size();
		return cur;
	}
}

exploredNode::exploredNode(Player& p)
{
	//	double initprofile = clock(); // is any of this even avoidable?

	p.locState.get_all_moves(moves);
	total_times_explored = moves.size();

	times_moves_explored = vector<int>(moves.size(),1);
	avg_so_far           = vector<double>(moves.size(),0.0);
	value_of_moves       = vector<double>(moves.size(),log(total_times_explored));				// 0 == ln(total_times_explore)/1
	children             = vector<exploredNode*>(moves.size(), NULL);
	is_my_move           = (p.locState.pn == p.locState.mypn);
	node_count ++;
	// determine initial move {review}
	next_move = 0;

	//cout << "init profile= " << (clock()-initprofile)/(CLOCKS_PER_SEC) << "\n";
	//RESULT: Takes about 0.005 seconds. EXTREMELY SLOW. DAFUQ? 

}

void exploredNode::book_keeping(int i , double backed_up)	// depends on whose move it is
{
	//double bookprofile = clock();
	if (backed_up == -1.0) return;			// ignore
	
	total_times_explored++;
	times_moves_explored[i]++;
	
	avg_so_far[i] = (backed_up + (times_moves_explored[i]-2)*avg_so_far[i])/(times_moves_explored[i]-1);
	// -1 in denominator is to nullify initial count of 1
	
	next_move = 0;
//	vector<int> same_valued;
	for (int j = 0 ; j<value_of_moves.size() ; j++)
	{
		if (is_my_move)	value_of_moves[j] = avg_so_far[j] + C*sqrt(log(total_times_explored)/times_moves_explored[j]);		// choosing max, so add
		else			value_of_moves[j] = avg_so_far[j] - C*sqrt(log(total_times_explored)/times_moves_explored[j]);		// chooseing min, so subtract


		if 		(is_my_move  and (value_of_moves[j] > value_of_moves[next_move])) next_move = j;				// choose max
		else if (!is_my_move and (value_of_moves[j] < value_of_moves[next_move])) next_move = j;				// choose min
		

		else if (value_of_moves[j] == value_of_moves[next_move])			// with an 80% probability, swap			{ review }
		{
			int temp = fastrand()%5;
			if (temp != 4) next_move = j;
		}
	}
	
	//cout << " iteration in book keeping takes time=" << (clock()-bookprofile)/(CLOCKS_PER_SEC) << "\n";
	//RESULT OF PROFILE : Each call takes 0.00015 seconds, the log-wala part is half of that time.
		//INFERENCE : Too fast to make a difference.
	// next_move is ready to be called :D
}

void exploredNode::recursive_delete()
{
	
	for (int i = 0 ; i<children.size() ; i++)
	{
		if (!children[i]) { /*delete children[i] ;*/ }		// do nothing if pointer is NULL { or should I delete a NULL pointer? }
		
		else children[i]->recursive_delete();

	}
	//cout << "recursive-delete profile=" << (clock()-rcprof)/(CLOCKS_PER_SEC) << "\n";
	//RESULT OF PROFILE : Each reccursive delete takes between 1e-05 to 9e-06. However, there's a shit ton of these.
	//RESULT PART2 : The entire thing, i.e, for the root, takes a grand total of 0.0005 seconds...about 5 times as much as the bookkeeping.
		//INFERENCE : Maybe surag is right and we should bother about this.

	node_count--;
	delete this;	// I have lost the will to live, simply nothing more to gain
					// there is nothing more for me, need the end to set me free 
}


#endif