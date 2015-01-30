#include "Sequence Alignment.cpp"
#include "InputOutput.cpp"
#include "search.cpp"
#include <algorithm>

int main(int argc, char** argv) {
	SeqProblem s;
	input(s);
	s.initialState.position.resize(s.k);
	s.initialState.currentCost = 0;
	s.initialState.heuristicCost = 0;
	s.initialState.totalCost = 0;
	s.initialState.auxData.resize(s.k);
	copy(s.sequences.begin(), s.sequences.end(), s.initialState.auxData.begin());
	SeqNode n = aStarSearch(s);
	output(n);
}