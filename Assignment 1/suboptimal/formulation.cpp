#ifndef FORMULATION_CPP
	#define FORMULATION_CPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <unordered_map>
#include <random>

using namespace std;

enum INIT_TYPE { RANDOM = 0 , GENETIC = 1 };


//Formulation requires that we minimize 
class SeqState {
public:
	int length; 					 	//stores the length of the strings of this state.
	double cost; 						//Functions as energy too.
	//vector< deque<char> > sequences; 	//deque allows for Faster Swaps and stuff. - Not necessary.
	vector< vector<int> > dashPos;		//Encapsulates the entire state. NEEDS TO BE SORTED.

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
	unordered_map< char , int > charToInt;
	//Sequence Related
	int k;
	vector<string> sequences; //Input sequences
	vector<int> stringLengths;
	int sumOfLengths;
	SeqState initialState;
	//Misc Functions
	void print();
	//Initialization Functions
	void initialize(INIT_TYPE initMode , int numStates); //Initializes into Problem::initialState.
	void initializeInto(INIT_TYPE initMode , SeqState& state, int numStates);
		void randomInit();
		void randomInit(int x); //Generates x random states.		
		void geneticInit();
	//Functions required by search.
	void getNBD(SeqState& n , vector<SeqState>& nbd); //NeighBourhooD - NBD
	double evalCost(SeqState& state);
};
//Misc Functions
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

void SeqProblem::initialize(INIT_TYPE initMode , int numStates = 1) {
	return; //TODO
}

void SeqProblem::initializeInto(INIT_TYPE initMode , SeqState& state, int numStates=1) {
	return; //TODO
}

void SeqProblem::getNBD(SeqState& state , vector<SeqState>& nbd) {
	return; //TODO
}

double SeqProblem::evalCost(SeqState& state) {
	double cost = 0.0;
	/*
	Following algorithm :
	forAll 0 <= i < j < k :
	cost = MisMatchCost( String_i [...ctr] , String_j [...ctr]) where String_i and String_j are the i'th and j'tj resultant strings.
		It can be calculated easily without copying and inserting and stuff.
		maintain 5 pointers, two for the dashes , two for the sequences and one for the length processed. Repeat this for every pair.
	*/
	for( stringIDX_1 = 0; stringIDX_1 < k; ++stringIDX_1) {
		for( stringIDX_2 = stringIDX_1+1 ; stringIDX_2 < k; ++stringIDX_2) {
			int ctr = 0; //Counts how many positions have been parsed.
			//Pointers to the dash/sequence thingies			
			int dashIDX_1 	= 0;	
			int seqIDX_1 	= 0;
			int dashIDX_2 	= 0;
			int seqIDX_2	= 0;
			while ( ctr < state.length ) {
				//StringIDX_1 's character is calculated here.
				char s1 , s2; //s1 and s2 are the 
				if ( state.dashPos[stringIDX_1][dashIDX_1] == ctr ) {
					//String_IDX1 has a '-' at this position.
					s1 = '-';
					cost += CC;
					++dashIDX_1;
				} else {
					s1 = sequences[stringIDX_1][seqIDX_1];
					++seqIDX_1;
				}

				//StringIDX_2 's character is calculated here.
				if ( state.dashPos[stringIDX_2][dashIDX_2] == ctr) {
					//String_IDX2 has a '-' at this position
					s2 = '-';
					cost += CC;
					++dashIDX_2;
				} else {
					s1 = sequences[stringIDX_2][seqIDX_2];
					++seqIDX_2;
				}
				cost += MC[ charToInt[s1] ][ charToInt[s2] ];
				++ctr;
			}	
		}
	}
	return cost;
}
#endif