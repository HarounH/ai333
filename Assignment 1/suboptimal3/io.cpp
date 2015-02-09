#ifndef IO_CPP
	#define IO_CPP
#include <iostream>
#include <vector>
#include "formulation.cpp"
#include <limits>

#define SMALL_INT std::numeric_limits<int>::min()
#define NODE_EXPANSION_RATE 100000
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
	inSequences.resize(k);
	seqLengths.resize(k);
	minFinalLength = 0; //Starts at zero and works its way up. It is also the length of the longest sequence.
	maxFinalLength = 0;

	for(int i = 0; i < k; ++i)
	{
		cin >> s;
		inSequences[i] = s;
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

void output()
{
	printState();
} //Should work.

#endif