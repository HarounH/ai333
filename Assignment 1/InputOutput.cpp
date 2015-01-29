#include <iostream>
#include <vector>

using namespace std;

void input(SeqProblem& p)
{
	cin >> p.clockTime;
	cin >> p.aSize;
	string s;
	p.alphabet.resize(aSize);
	for(int i = 0; i < aSize; ++i)
	{
		cin >> s;
		p.alphabet[i] = s[0];
	}
	cin >> p.k;
	p.sequences.resize(p.k);
	p.stringLengths.resize(p.k);
	for(int i = 0; i < p.k; ++i)
	{
		cin >> s;
		p.sequences[i] = s;
		p.stringLengths[i] = s.size();
	}
	cin >> p.CC;
	p.MC.resize(aSize + 1);
	for(int i = 0; i < aSize + 1; ++i)
	{
		p.MC[i].resize(aSize + 1);
		for(int j = 0; j < aSize + 1; ++j)
			cin >> p.MC[i][j];
	}
	cin >> s;
}

void output(SeqNode& n)
{
	for(int i = 0; i < n.data.size(); ++i)
		cout<<n.data<<"\n";
}