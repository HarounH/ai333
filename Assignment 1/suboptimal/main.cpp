#include <ctime>		//...Allows us to time stuff.
#include <random>
#include "InputOutput.cpp"
#include <algorithm>
#include "hillClimb.cpp"

int main(int argc, char** argv) {
	clock_t start;
	start = clock();
	SeqProblem s;
	input(s);
	s.initialize(RANDOM);
	vector<SeqState> nbd;
	s.printState(greedyHillClimb_nRestarts_untimed(s , 100));
	return 1;
}