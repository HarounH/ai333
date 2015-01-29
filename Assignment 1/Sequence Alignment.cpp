#include <iostream>
#include <vector>

using namespace std;

class SeqNode {
public:
	double currentCost;
	vector<int> position;
	vector<string> auxData;
	double heuristicCost;
	double totalCost;
	void heuristicCost();
};

class SeqProblem {
public:
	double clockTime;
	int aSize;
	int k;
	double CC;
	vector< vector<double> > MC;
	vector<string> sequences;
	vector<int> stringLengths;
	vector<char> alphabet;
	SeqNode initialState;
	void getSuccessors(SeqNode& n, vector<SeqNode>& successors);
	bool goalTest(SeqNode& n);
	double pathCost(SeqNode& s, SeqNode& t);
};

bool SeqProblem::goalTest(SeqNode& n)
{
	if (n.position == stringLengths)
		return true;
	else return false;
}

void getSuccessors(SeqNode& n, vector<SeqNode>& successors)
{
	/**for each 2^k possible tuples (consisting of 0's and 1's)
	//new position is position+tuple
	//new cost is previous cost + (CC * number of ones in tuple) + (sum of all cost pairs for that position)
	//possibly update auxData
	//call heuristic function
	//update total cost
	//push into vector
	**/
	for(int i = 1; i < (2 << k); ++i)
	{
		
	}
}

class SearchAgent {
public:
	double heuristicFunc(SeqProblem& p, SeqNode& n)
	{
		return 0;
	}
};

int main(int argc, char** argv) {
	SeqProblem s;
	input(s);
	
}