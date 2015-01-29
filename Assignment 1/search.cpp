//#include <math.h> //...because haroun
#include "Sequence Alignment.cpp" //...also includes vectors and also iostream and also the classes of sequence alignment.

#include <queue>
#include <stack> 	//...used for dfs and dfsbb
#include <limits> 	//...used for initialization

#define BIG_DOUBLE std::numeric_limits<double>::max()

struct SeqNodeHeuristicCostComparator { //Used in dfbb to sort the successor nodes.
	bool operator() ( const SeqNode& lhs , const SeqNode& rhs ) { return lhs.heuristicCost < rhs.heuristicCost; }
}seqNodeHeuristicComparator_left;

struct SeqNodeTotalCostComparator{
	bool operator() (SeqNode& lhs , SeqNode& rhs) { return lhs.totalCost< rhs.totalCost; }
};
//Not passing by reference. Can be changed if needed
SeqNode dfs(SeqProblem& problem)  { //Uninformed search.

	//Initialization
	SeqNode optimalSeqNode; 						// Includes something called auxData which is what we must output.
		optimalSeqNode.totalCost = BIG_DOUBLE; 	//BIG_DOUBLE has been macro-defined as numeric limits.
	//double bound; Not necessary here
	stack<SeqNode> fringe;
		fringe.push(initialState);

	while(!fringe.empty()) {
		//Optimization problem has no "goal state end."
		//Add all the kids to the stack.
		SeqNode node = fringe.top();
		fringe.pop();
		if( problem.goalTest(node) ) {
			if (node.totalCost < optimalSeqNode.totalCost ) {
				optimalSeqNode = node;
			}
		}
		else {
			//Insert all the kids into the stack.
			vector<SeqNode> children;
			problem.getSuccessors(node , children);
			for(int i = 0; i<children.size(); i++) {
				fringe.push(children[i]);
			}
		}
	}
	return optimalSeqNode;
}

SeqNode dfbb(SeqProblem& problem) { //Informed search

	//Initialization.
	//initialize bound.
	SeqNode optimalSeqNode; //Initialized using bound.
		optimalSeqNode.totalCost = BIG_DOUBLE; //BIG_DOUBLE is the numeric limit of double

	// ############# BOUND is the totalCost of the optimalSeqNode;

	stack<SeqNode> fringe;
		fringe.push(problem.initialState);

	while( !fringe.empty() ) {
		SeqNode  node = fringe.top();
			fringe.pop();
		if ( problem.goalTest(node) ) {
			if( node.totalCost < optimalSeqNode.totalCost ) {
				optimalSeqNode = node;
					//bound = node.totalCost; //Update Bound.
			}
		}
		else {
			vector<SeqNode> children;
			problem.getSuccessors(node , children);

			//Sort children by their heuristic value. Only heuristic value because looking into the future.
			std::sort(children.begin() , children.end() , seqNodeHeuristicComparator_left);

			for(int i = 0; i<children.size(); i++) {
				if( children[i].totalCost < optimalSeqNode.totalCost ) {
					fringe.push(children[i]);
				}
			}
		}
	}
	return optimalSeqNode;
}

SeqNode astarsearch(SeqProblem& problem) {
	SeqNode optimalSeqNode;
		optimalSeqNode.totalCost = BIG_DOUBLE; //BIG_DOUBLE is the numeric limit of double
		//Follows total cost contour.
	std::priority_queue<SeqNode , SeqNodeTotalCostComparator> fringe;
		fringe.push(problem.initialState);

	while( !fringe.empty() ) {
		SeqNode node = fringe.top();
			fringe.pop(); //GIVE ME AN EXTRACT FUNCTION DAMMIT.
		if ( problem.goalTest(node) ) {
			if (node.totalCost < optimalSeqNode.totalCost) {
				optimalSeqNode = node;
			}
		}
		else {
			vector<SeqNode> children;
			problem.getSuccessors( node , children );
			for(int i=0; i<children.size(); ++i) {
				fringe.push(children[i]);
			}
		}
	}
	return optimalSeqNode;
}

SeqNode dfbb_with_greedyBound( SeqProblem& problem) {
	SeqNode optimalSeqNode;
		optimalSeqNode.heuristicCost = BIG_DOUBLE; 	//BIG_DOUBLE is the numeric limit
	optimalSeqNode.totalCost = BIG_DOUBLE;			//BIG_DOUBLE is the numeric limit

	std::priority_queue<SeqNode , SeqNodeHeuristicCostComparator> fringe;
		fringe.push(problem.initialState);

	while(!fringe.empty()) {
		SeqNode node = fringe.top();
			fringe.pop(); //Extract() lala
		if ( problem.goalTest(node) ) {
			if( node.totalCost < optimalSeqNode.totalCost ) {
				optimalSeqNode = node;
			}
		}
		else {
			vector<SeqNode> children;
			problem.getSuccessors(node , children);
			for(int i =0 ; i< children.size(); ++i) {
				if( children[i].totalCost < optimalSeqNode.totalCost ) {
					fringe.push(children[i]);
				}
			}
		}
	}
	return optimalSeqNode;
}