#include "formulation.cpp"
#include "InputOutput.cpp"
#include <algorithm>
#include "suboptsearch.cpp"
#include <ctime>		//...Allows us to time stuff.
#include <random>

int main(int argc, char** argv) {
	clock_t start;
	start = clock();
	SeqProblem s;
	input(s);
	s.print();
	return 1;
}