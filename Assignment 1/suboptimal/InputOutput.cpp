#include <iostream>
#include <vector>
#include "formulation.cpp"

using namespace std;

void input(SeqProblem& p)
{
	cin >> p.clockTime;
		p.clockTime *= 60; // In seconds.
	cin >> p.aSize;
	string s;
	p.alphabet.resize(p.aSize);
	for(int i = 0; i < p.aSize; ++i)
	{
		cin >> s;
		p.alphabet[i] = s[0];
		p.charToInt[s[0]] = i;
	}
	p.alphabet.push_back('-');
	p.charToInt['-'] = p.aSize;
	cin >> p.k;
	p.sequences.resize(p.k);
	p.stringLengths.resize(p.k);
	p.sumOfLengths = 0;
	for(int i = 0; i < p.k; ++i)
	{
		cin >> s;
		p.sequences[i] = s;
		p.stringLengths[i] = s.size();
		p.sumOfLengths += s.size();
	}
	cin >> p.CC;
	p.MC.resize(p.aSize+1);
	for(int i = 0; i < p.aSize + 1; ++i)
	{
		//AKSHAY STYLE :P int y = p.charToInt[alphabet[i]];
		p.MC[i].resize(p.aSize+1);
		for(int j = 0; j < p.aSize + 1; ++j)
		{
			// AKSHAY STYLE :P int z = (int) p.alphabet[j];
			cin >> p.MC[i][j];
		}
	}
	cin >> s;
} //Works.

void output(SeqState& n)
{
	n.print();
} //Should work.