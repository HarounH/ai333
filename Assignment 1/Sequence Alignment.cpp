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
	double clockTime;
	int aSize;
	int k;
	double CC;
	vector< vector<double> > MC;
	vector<string> sequences;
	vector<char> alphabet;
	SeqNode initialState;
	vector<SeqNode> getSuccessors(SeqNode& n);
	bool goalTest(SeqNode& n);
	double pathCost(SeqNode& s, SeqNode& t);
};

class SearchAgent {
public:
	double heuristicFunc(SeqProblem& p, SeqNode& n);
};

bool SeqProblem::goalTest(SeqNode& n)
{
	
}

int main(int argc, char** argv) {
	SeqProblem s;
	input(s);
	
}