#ifndef SUB_OPT_SEARCH_CPP
	#define SUB_OPT_SEARCH_CPP

#include <random> //...for simulated annealing.

#define BIG_DOUBLE std::numeric_limits<double>::max()

//enum INIT_TYPE { RANDOM = 0 , GENETIC = 1 };


/*
Does not handle shoulders, pits, plateaus or ANY of that.
*/
SeqState greedyHillClimb_NoRestarts_untimed(SeqProblem& p) {
	SeqState best = p.initialState; //Copy cost.
	cout << "hi \t The best cost is : \t " << best.cost << "\n";
	while(true) {
		vector<SeqState> nbd;
		p.getNBD(best , nbd);
		//Find minimum of the neigbhours.
		int minIDX = 0;
		double minCost = BIG_DOUBLE; //Defined as numeric limit.
		for(int i = 0; i<nbd.size() ; ++i) {
			if ( nbd[i].cost < 0) p.printState(nbd[i]);
			if (nbd[i].cost < minCost) {
				minCost = nbd[i].cost;
				minIDX = i;
			}
		} //Minimum found at i.
		if( best.cost < minCost ) {
			break;
		} else {
			best = nbd[minIDX]; //New best.
		}
	}
	return best;
}

/*
Restarts but does not time itself.
*/
SeqState greedyHillClimb_nRestarts_untimed(SeqProblem& p , int n) {
	SeqState best = p.initialState;
	SeqState prevBest = p.initialState;
	int restarts = n;
	while( --restarts ) {
		int sameCostMoves = 0;
		while(true) {
			vector<SeqState> nbd;
			p.getNBD(best , nbd);
			//Find minimum of the neigbhours.
			int minIDX = 0;
			double minCost = BIG_DOUBLE; //Defined as numeric limit.
			for(int i = 0; i<nbd.size();++i) {
				if (nbd[i].cost < minCost) {
					minCost = nbd[i].cost;
					minIDX = i;
				}
			} //Minimum found at i.
			if( best.cost < minCost ) {
				break;
			} 
			else if (best.cost > minCost) {
				best = nbd[minIDX]; //New best.
				//Compare the previous bests too.
				sameCostMoves = 0;
			}
			else {
				if(sameCostMoves > -1)
					break;
				++sameCostMoves;
				best = nbd[minIDX];
			}
		}
		if(prevBest.cost > best.cost)
		{
			prevBest = best;
			cout << "\n" << prevBest.cost << "\n";
		}
		cout<<restarts<<"\n";
		p.initializeInto(RANDOM , best); //Generate 1 Random Start. ALTER THIS for better greedyhillClimb.

	}
	return (( best.cost < prevBest.cost )?( best ):( prevBest ));
}

/*
Need some way of evaluation TIME_BUFFER. It allows for the program to print stuff etc.
*/
#define TIME_BUFFER 1000

/*
Greedy Hill Climb with no restarts but it is timed. Theoretically runs into shoulders etc and treats it as optimal.
*/
SeqState greedyHillClimb_NoRestarts_timed(SeqProblem& p , clock_t& start) {
	clock_t present;
	present = clock();
	SeqState best  = p.initialState;
	while( ((float)present/CLOCKS_PER_SEC) + TIME_BUFFER < ((float)start/CLOCKS_PER_SEC) + p.clockTime) {
		vector<SeqState> nbd;
		p.getNBD(best , nbd);
		//Find minimum of the neigbhours.
		int minIDX;
		double minCost = BIG_DOUBLE; //Defined as numeric limit.
		for(int i = 0; i<nbd.size();++i) {
			if (nbd[i].cost < minCost) {
				minCost = nbd[i].cost;
				minIDX = i;
			}
		} //Minimum found at i.
		if( best.cost < minCost )
			break;
		else
			best = nbd[minIDX]; //New best.
		present = clock(); //Get time.
	}
	return best;
}

/*
Greedy Hill Climb with infinite restarts if time permits.
*/
SeqState greedyHillClimb_infRestarts_timed(SeqProblem& p , clock_t& start) {
	clock_t present;
	present = clock();
	SeqState& best = p.initialState;		//...Extra copy.
	SeqState& prevBest = p.initialState; //...Extra copy.
	while( ((float)present/CLOCKS_PER_SEC) + TIME_BUFFER < ((float)start/CLOCKS_PER_SEC) + p.clockTime) {
		while(true && ((float)present/CLOCKS_PER_SEC) + TIME_BUFFER < ((float)start/CLOCKS_PER_SEC) + p.clockTime ) { //You don't want to get caught in this.
			vector<SeqState> nbd;
			p.getNBD(best , nbd);
			//Find minimum of the neigbhours.
			int minIDX;
			double minCost = BIG_DOUBLE; //Defined as numeric limit.
			for(int i = 0; i<nbd.size();++i) {
				if (nbd[i].cost < minCost) {
					minCost = nbd[i].cost;
					minIDX = i;
				}
			} //Minimum found at i.
			if( best.cost <= minCost ){
				break;
			} else {
				best = nbd[minIDX]; //New best.
				
			}
			present = clock();
		}
		if (prevBest.cost > best.cost) 
			prevBest = best;
		p.initializeInto(RANDOM , best);
	}
	return (( best.cost < prevBest.cost )?( best ):( prevBest ));
}

//TODO : stochaticHillClimb with random restarts
#endif