#include <ctime>		//...Allows us to time stuff.
#include <random>
#include "InputOutput.cpp"
#include <algorithm>
#include "hillClimb.cpp"

//enum INIT_TYPE { RANDOM = 0 , STATS = 1 , RANDOM_UNIFORM , RANDOM_CHI2};

int main(int argc, char** argv) {
	clock_t start;
	start = clock();
	SeqProblem s;
	input(s);
	s.initialize(RANDOM);
	vector<SeqState> nbd;
	SeqState ans = greedyHillClimb_infRestarts_timed(s , start , STATS);
	s.printState(  ans );
	return 1;
}