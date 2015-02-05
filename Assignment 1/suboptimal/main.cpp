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
	s.printState(s.initialState);
	return 1;
}