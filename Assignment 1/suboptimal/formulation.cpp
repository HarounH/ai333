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
		//dashPos[i] is the number of sequence character's before the ith dash. ab-cd would have dashpos = [2].
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
	int minimumFinalLength;
	SeqState initialState;
	//Misc Functions
	void print();
	void printState(SeqState& state);
	//Initialization Functions
	void initialize(INIT_TYPE initMode , int numStates); //Initializes into Problem::initialState.
	void initializeInto(INIT_TYPE initMode , SeqState& state, int numStates); //Initialize 
		void randomInit();
		void randomInit(int x); //Generates x random states.		
	//Functions required by search.
	void getNBD(SeqState& n , vector<SeqState>& nbd); //NeighBourhooD - NBD
		void getDeterministicNBD_singleDashMove(SeqState& n , vector<SeqState>& nbd);
	
	double evalCost(SeqState& state);
	void setChildCost(SeqState& parent , SeqState& child , int stringIDX);
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

void SeqProblem::printState(SeqState& state) {
	for(int stringIDX = 0; stringIDX < k; ++stringIDX) {
		int ctr = 0; //Counts how many positions have been parsed.
		//Pointers to the dash/sequence thingies			
		int dctr = 0; //number of dashes read.
		int cctr = 0; //Number of characters read.
		while( ctr < state.length ) {
			if ( state.dashPos[stringIDX][dctr] + cctr == ctr) {
				cout << '-';
				++dctr;
			} else {
				cout << sequences[stringIDX][cctr];
				++cctr;
			}
		}
		cout << "\n"; //One string printed.
	}
	return;
}

void SeqProblem::initialize(INIT_TYPE initMode , int numStates = 1) {
	return; //TODO
}

void SeqProblem::initializeInto(INIT_TYPE initMode , SeqState& state, int numStates=1) {
	return; //TODO
}

void SeqProblem::getNBD(SeqState& state , vector<SeqState>& nbd) {
	getDeterministicNBD_singleDashMove(state , nbd); //Change According to will
}

void SeqProblem::getDeterministicNBD_singleDashMove(SeqState& state , vector<SeqState>& nbd) {
	//For each string, generate its neighbours by moving all strings randomly.
	
	/* //Use the following random devices if you must 
	std::random_device rd;
	std::mt19937 gen(rd()); //Some cool mersenne twister algorithm
	std::uniform_int_distribution<int> dist(0 , state.length);
	*/
	for(int stringIDX = 0; stringIDX < k ; ++stringIDX) {
		//For each string in the state, generate children by moving each dash randomly. and one more dash by one length more and one length less.
		for(int di = 0; di< state.dashPos[stringIDX].size(); ++di) {
			//If possible, swap the dash with the previous and the next character.
			if (state.dashPos[stringIDX][di] > 0) {
				SeqState child = state;
				--child.dashPos[stringIDX][di];
				nbd.push_back(child);
			}
			if (state.dashPos[stringIDX][di] < stringLengths[stringIDX]-1 ) {
				SeqState child = state;
				++child.dashPos[stringIDX][di];
				nbd.push_back(child);
			}
		}
	}
	//TODO : Insert string with 1 length more and string with 1 length less.
	for( int stringIDX = 0; stringIDX < k ; ++stringIDX) {
		//insert a random dash.
	}

	if( state.length > minimumFinalLength ) {
		//Remove a dash.
	}

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
				if ( state.dashPos[stringIDX_1][dashIDX_1] + dashIDX_1== ctr ) {
					//String_IDX1 has a '-' at this position.
					s1 = '-';
					cost += CC;
					++dashIDX_1;
				} else {
					s1 = sequences[stringIDX_1][seqIDX_1];
					++seqIDX_1;
				}

				//StringIDX_2 's character is calculated here.
				if ( state.dashPos[stringIDX_2][dashIDX_2] + dashIDX_2== ctr) {
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
} // Akshay QC : 

void SeqProblem::setChildCost(SeqState& parent , SeqState& child , int stringIDX) {
	double deltaCost = 0.0;
	for(stringIDX_2 = 0; stringIDX_2 < k ; ++stringIDX_2) {
		if ( stringIDX_2 == stringIDX )
			continue;
		else {
			int ctr = 0; //Counts how many positions have been parsed.
			//Pointers to the dash/sequence thingies			
			int dashIDX_1 	= 0;	
			int seqIDX_1 	= 0;
			int dashIDX_2 	= 0;
			int seqIDX_2	= 0;
			while ( ctr < parent.length ) {
				//StringIDX_1 's character is calculated here.
				//Parent Cost
					char s1 , s2; //s1 and s2 are the 
					if ( parent.dashPos[stringIDX_1][dashIDX_1] + dashIDX_1 == ctr ) {
						//String_IDX1 has a '-' at this position.
						s1 = '-';
						deltaCost -= CC;
						++dashIDX_1;
					} else {
						s1 = sequences[stringIDX_1][seqIDX_1];
						++seqIDX_1;
					}

					//StringIDX_2 's character is calculated here.
					if ( parent.dashPos[stringIDX_2][dashIDX_2] + dashIDX_2 == ctr) {
						//String_IDX2 has a '-' at this position
						s2 = '-';
						deltaCost -= CC;
						++dashIDX_2;
					} else {
						s1 = sequences[stringIDX_2][seqIDX_2];
						++seqIDX_2;
					}
					deltaCost -= MC[ charToInt[s1] ][ charToInt[s2] ];
				
				//ChildCost.
					char c1 , c2;
					if ( child.dashPos[stringIDX_1][dashIDX_1] + dashIDX_1 == ctr ) {
						//String_IDX1 has a '-' at this position.
						s1 = '-';
						deltaCost += CC;
						++dashIDX_1;
					} else {
						s1 = sequences[stringIDX_1][seqIDX_1];
						++seqIDX_1;
					}

					//StringIDX_2 's character is calculated here.
					if ( child.dashPos[stringIDX_2][dashIDX_2] + dashIDX_2 == ctr) {
						//String_IDX2 has a '-' at this position
						s2 = '-';
						deltaCost += CC;
						++dashIDX_2;
					} else {
						s1 = sequences[stringIDX_2][seqIDX_2];
						++seqIDX_2;
					}
					deltaCost += MC[ charToInt[s1] ][ charToInt[s2] ];
				++ctr;
			}	
		}
	}
	child.cost = parent.cost + deltaCost;
}
#endif