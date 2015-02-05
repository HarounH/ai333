#ifndef FORMULATION_CPP
	#define FORMULATION_CPP

#include "formulation.h"


//Misc Functions
void SeqProblem::print() { //Trivial Code to print the problem out.
	cout << "Clock time is : \t " << clockTime << "\n";
	cout << "CC is 			 \t " << CC << "\n";
	cout << "######## MC ########\n";
	for(int r = 0 ; r<aSize+1 ; ++r) {
		for(int c = 0; c<aSize+1 ; ++c) {
			cout << MC[r][c] << " ";
		}
		cout << "\n";
	}
	cout << "The alphabets are : "; for(int i=0; i<aSize ; ++i) { cout << alphabet[i] << " "; } cout << "\n";
	cout << "string and their lengths are : \n";
	for(int i = 0; i<k ; ++i) {
		cout << stringLengths[i] << "\t" << sequences[i] << "\n";
	}
	return;
}

void SeqProblem::printState(SeqState& state) { //Mostly trivial Code to print out the strings associated with state
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
	getNBD_singleDashMove(state , nbd); //Change According to will
}

void SeqProblem::getNBD_singleDashMove(SeqState& state , vector<SeqState>& nbd) {
	//One neighbour per dash per string. , big-O(k*n*n) neighbours are generated here.
	for(int stringIDX = 0; stringIDX < k ; ++stringIDX) {
		//For each string in the state, generate children by moving each dash randomly. and one more dash by one length more and one length less.
		for(int di = 0; di< state.dashPos[stringIDX].size(); ++di) {
			//If possible, swap the dash with the previous and the next character.
			if (state.dashPos[stringIDX][di] > 0) {
				SeqState child = state;
				--child.dashPos[stringIDX][di];
				//Check if the di'th position needs to be sorted.
				/*
				Feasible alternative to sorting is to assert child.dsahPos[stringIDX][di] > child.dsahPos[stringIDX][di+1] 
															and also to assert child.dashPos[stringIDX][di] < childdashPos[stringIDX][di-1]
				*/
				if ( di+1 < child.dashPos[stringIDX].size()) {
					//There is another element after di
					//ASSERT : child.dashPos[stringIDX][di] < child.dashPos[stringIDX][di+1]
					if (child.dashPos[stringIDX][di] < child.dashPos[stringIDX][di+1]) {
						//PASS
					} else {
						//Swap to restore invariant.
						int temp = child.dashPos[stringIDX][di];
						child.dashPos[stringIDX][di] = child.dashPos[stringIDX][di+1];
						child.dashPos[stringIDX][di+1] = temp;  
					}
				}
				if ( di > 0 ) {
					//There is one element before di.
					//ASSERT : child.dashPos[stringIDX][di] > child.dashPos[stringIDX][di-1]
					if (child.dashPos[stringIDX][di] > child.dashPos[stringIDX][di-1]) {
						//PASS
					} else {
						//Swap to restore invariant.
						int temp = child.dashPos[stringIDX][di];
						child.dashPos[stringIDX][di] = child.dashPos[stringIDX][d-1];
						child.dashPos[stringIDX][d-1] = temp;  
					}
				}
				//std::sort(child.dashPos[stringIDX]); //Possibly slowing us down.
				setChildCost_singleDash(state, child , stringIDX);
				nbd.push_back(child);
			}
			if (state.dashPos[stringIDX][di] < stringLengths[stringIDX]-1 ) {
				SeqState child = state;
				++child.dashPos[stringIDX][di];
				//Check if the di'th position needs to be sorted.
				/*
				Feasible alternative to sorting is to assert child.dsahPos[stringIDX][di] > child.dsahPos[stringIDX][di+1] 
															and also to assert child.dashPos[stringIDX][di] < childdashPos[stringIDX][di-1]
				*/
				if ( di+1 < child.dashPos[stringIDX].size()) {
					//There is another element after di
					//ASSERT : child.dashPos[stringIDX][di] < child.dashPos[stringIDX][di+1]
					if (child.dashPos[stringIDX][di] < child.dashPos[stringIDX][di+1]) {
						//PASS
					} else {
						//Swap to restore invariant.
						int temp = child.dashPos[stringIDX][di];
						child.dashPos[stringIDX][di] = child.dashPos[stringIDX][di+1];
						child.dashPos[stringIDX][di+1] = temp;  
					}
				}
				if ( di > 0 ) {
					//There is one element before di.
					//ASSERT : child.dashPos[stringIDX][di] > child.dashPos[stringIDX][di-1]
					if (child.dashPos[stringIDX][di] > child.dashPos[stringIDX][di-1]) {
						//PASS
					} else {
						//Swap to restore invariant.
						int temp = child.dashPos[stringIDX][di];
						child.dashPos[stringIDX][di] = child.dashPos[stringIDX][d-1];
						child.dashPos[stringIDX][d-1] = temp;  
					}
				}
				//std::sort(child.dashPos[stringIDX]); //Possibly slowing us down.
				setChildCost_singleDash(state, child , stringIDX);
				nbd.push_back(child);
			}
		}
	}

	
	//Code that handles neighbours of varying length.
	//Random distribution devices from c++11 's  random class.
	std::random_device rd;
	std::mt19937 engine(rd()); //Some cool mersenne twister algorithm
	
	for(int i = 0; i<LONGER_LENGTH_CHILDREN; ++i) { //Vary these parameters to decide how many longer length children are wanted
		SeqState child = state;
		for( int stringIDX = 0; stringIDX < k ; ++stringIDX) {
			//insert a random dash.
			//uniform_int_distrib's are lightweight.
			int pos = std::uniform_int_distribution<int>{0 , stringLengths[stringIDX]}(engine); //engine is the mt19937 random number generator engine.
			child.dashPos[stringIDX].push_back(pos);
			std::sort(child.dashPos[stringIDX].begin() , child.dashPos[stringIDX].end()); //Necessary to keep it sorted.		
		} 
		++child.length;
		child.cost = evalCost(child);
		nbd.push_back(child); //Generates one random child of larger length.
	}
	//Remove a dash from the child only if possible.
	if( state.length > minimumFinalLength ) {
		for(int i = 0; i< SHORTER_LENGTH_CHILDREN ; ++i) { //Vary these parameters to decide how many shorter length children are wanted.
			SeqState child = state;
			for (int stringIDX = 0; stringIDX < k ; ++stringIDX) {
				//Remove a dash.	
				//ASSERT : for all stringIDX , dashPos[stringIDX].size()>=1
				child.dashPos[stringIDX].pop_back();
			}
			--child.length;
			child.cost = evalCost(child);
			nbd.push_back(child);
		}
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

void SeqProblem::setChildCost_singleDash(SeqState& parent , SeqState& child , int stringIDX) {
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