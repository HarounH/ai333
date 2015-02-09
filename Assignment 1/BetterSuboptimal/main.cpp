#include <iostream>
#include <math.h>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;

#include "formulation.h"
#include "formulation.cpp"
#include "io.cpp"
#include "hillClimb.cpp"
int main(int argc, char** argv) {
	Problem p;
	input(p); //Get input for p	
	p.init(); //Initialize p.
	State s;

	//s = greedyHillClimb_nRestarts_untimed(p , 100);
	
	p.printState(p.initState);
	return 1;
}