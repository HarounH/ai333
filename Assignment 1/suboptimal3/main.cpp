#include <vector>
#include <iostream>
#include <unordered_map>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

/*################################################
Parameters to change : 
	Restarts can be of multiple types, check accordingly.
	initializaiton of length during restarts is set my a mode called SCHEDULE_<mode>
	Initialization of the initial string is set by INIT_<>
	Printing mode is set by PRINT_<> TODO: Ensure that the correct thing is printed out. set it to PRINT_OUTPUT when you call print.
###############################################*/

struct Move { //Represents Moves.
	int idx;
	int di;
	int origDptr;
	int newDptr;
	int newcost;
};

enum MODE { PRINT_STATE , PRINT_DEBUG  , PRINT_OUTPUT , 
	INIT_APPEND_BACK ,
	RESTART_RANDOM , RESTART_MEANLENGTH,
	SCHEDULE_RANDOM , SCHEDULE_BYRESTARTS
};

Move bestMove;
//Global Variables here.
double timeLimit; //from input
double TIME_BUFFER; //needs to be calculated.

int aSize; //number of alphabets
vector<char> idxToChar; //every position is a character. 
unordered_map<char , int> charToIdx; // every chararcter is mapped to an int.


int minFinalLength; // Minimum length needed by the strings
int maxFinalLength; // maximum length needed by the strings. beyond which it is redundant.
vector<int> seqLengths; //Length of each initial sequence of characters in the input

int k; //number of strings
double initcost; //Cost of the origin set of strings generated by calling init.
double cost; //cost of present set of strings
int length; // Length of the given strings right now.
vector<string> sequences; // present set of strings.
vector< vector<int> > dashpos; //positions of the dashes in the present strings.

double cc;
vector< vector<double> > mc;

random_device rd;
mt19937 engine(rd()); //Engines for random number generation.

int nrestarts = 1; //number of restarts done so far.
clock_t start; //We need to keep track of time.
//Ideally i would have externs all over the place in the following files, but thats cool.

#include "io.cpp"
#include "costs.cpp"
#include "init.cpp"
#include "moves.cpp"
#include "restarts.cpp"
#include "hillclimb.cpp"

int main(int argc , char** argv) {
	start = clock(); //Allows one to keep track of time.
	input();
	init( INIT_APPEND_BACK );
	//search();
	hilldescent_restarts_untimed(20);
	print(PRINT_DEBUG);
	return 1;
}