#ifndef FORMULATION_CPP
	#define FORMULATION_CPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <tr1/unordered_map>
#include <random>

using namespace std;

enum INIT_TYPE { RANDOM = 0 , GENETIC = 1 };


//Formulation requires that we minimize 
class SeqState {
public:
	int length; 					 	//stores the length of the strings of this state.
	double cost; 						//Functions as energy too.
	vector< deque<char> > sequences; 	//deque allows for Faster Swaps and stuff.
	vector< vector<int> > dashPos;

	//Misc.
	void print(); //Called by output.
};

class SeqProblem {
public:
	double clockTime;	
	//Cost Related
	vector< vector<double> > MC; 	//matching costs
	double CC; 						//Conversion cost
	//Alphabet Related
	int aSize;
	vector<char> alphabet;
	tr1::unordered_map< char , int > charToInt;
	//Sequence Related
	int k;
	vector<string> sequences; //Input sequences
	vector<int> stringLengths;
	int sumOfLengths;
	SeqState initialState;
	//Misc Functions
	void print();
	//Initialization Functions
	void initialize(INIT_TYPE initMode , int numStates=1); //Initializes into Problem::initialState.
	void initializeInto(INIT_TYPE initMode , int numStates=1 , SeqState& state);
		void randomInit();
		void randomInit(int x); //Generates x random states.		
		void geneticInit();
	//Functions required by search.
	void getNBD(SeqState& n , vector<SeqState>& nbd); //NeighBourhooD - NBD
	double evalCost(SeqState& state);
};

void SeqProblem::print() {
	cout << "Clock time is : \t " << clockTime << "\n";
	cout << "CC is 			 \t " << CC << "\n";
	
	cout << "######## MC ########\n";
	for(int r = 0 ; r<aSize+1 ; ++r) {
		for(int c = 0; c<aSize+1 ; ++c) {
			cout << MC[r][c] << " ";
		}
		cout << "\n";
	}

	//Alphabets
	cout << "The alphabets are : "; for(int i=0; i<aSize ; ++i) { cout << alphabet[i] << " "; } cout << "\n";

	cout << "string and their lengths are : \n";
	for(int i = 0; i<k ; ++i) {
		cout << stringLengths[i] << "\t" << sequences[i] << "\n";
	}
	return;
}

void SeqState::print() {
	return;
}
#endif