#ifndef IO_CPP
	#define IO_CPP
#include <iostream>
#include <vector>
#include <limits>

#define SMALL_INT std::numeric_limits<int>::min()
#define NODE_EXPANSION_RATE 10000000
using namespace std;

void input()
{
	cin >> timeLimit;
		timeLimit *= 60; // In seconds.
	cin >> aSize;
	string s;
	idxToChar.resize(aSize);
	for(int i = 0; i < aSize; ++i)
	{
		cin >> s;
		idxToChar[i] = s[0];
		charToIdx[s[0]] = i;
	}
	idxToChar.push_back('-');
	charToIdx['-'] = aSize;
	cin >> k;
	sequences.resize(k);
	seqLengths.resize(k);
	minFinalLength = 0; //Starts at zero and works its way up. It is also the length of the longest sequence.
	maxFinalLength = 0;

	for(int i = 0; i < k; ++i)
	{
		cin >> s;
		sequences[i] = s;
		seqLengths[i] = s.size();
		maxFinalLength += s.size();
		if ( minFinalLength < s.size() ) {
			minFinalLength = s.size();
		}
	}
	cin >> cc;
	
	mc.resize(aSize+1);
	
	for(int i = 0; i < aSize + 1; ++i)
	{
		//AKSHAY STYLE :P int y = p.charToInt[alphabet[i]];
		mc[i].resize(aSize+1);
		for(int j = 0; j < aSize + 1; ++j)
		{
			// AKSHAY STYLE :P int z = (int) p.alphabet[j];
			cin >> mc[i][j];
		}
	}
	cin >> s;
	TIME_BUFFER = 4.0*pow( (minFinalLength*k) , 2)/NODE_EXPANSION_RATE;
} //Works.

void print( MODE mode = PRINT_OUTPUT ) {
	
	if ( mode == PRINT_OUTPUT) {

	} else if (mode == PRINT_DEBUG) {
		cout << " length = " << length << "\n";
		cout << " cost =   " << cost << "\n";
		cout << " dashpos =\n"; 
		for(int idx = 0; idx<k; ++idx) {
			for(int didx = 0; didx < dashpos[idx].size(); ++didx) {
				cout << dashpos[idx][didx] << " ";
			}
			cout << "\n";
		}
	} else if (mode == PRINT_STATE ) {
		cout << " time_limit = " << timeLimit << "\n";
		cout << " time_buffer = " << TIME_BUFFER << "\n";
		cout << " alphabet_size = " << aSize << "\n";
		cout << " alphabets = " ;
		for(int i=0; i< aSize; ++i) cout << idxToChar[i] << "@" << charToIdx[idxToChar[i]] << ", ";
			cout << "\n";
		cout << " num_sequences = " << k << "\n";
		cout << " sequences : \n" ;
		for(int i=0; i<k; ++i) cout << " length = " << seqLengths[i] << "\n";

		cout << " cc = " << cc << "\n";
		for(int i=0; i<= aSize; ++i) {
			for(int j=0; j<=aSize; ++j) {
				cout << mc[i][j] << " ";
			}
		cout << "\n";
		}
	}
	//Necessary print.
	for(int i=0; i<k; ++i) {
		cout << sequences[i] << "\n";
	}
}

#endif