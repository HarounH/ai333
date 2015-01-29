#include <iostream>
#include <vector>

using namespace std;

void input(SeqProblem& p)
{
	cin >> p.clockTime;
	cin >> p.aSize;
	string s;
	alphabet.resize(aSize);
	for(int i = 0; i < aSize; ++i)
	{
		cin >> s;
		p.alphabet[i] = s[0];
	}
	cin >> k;
	sequences.resize(k);
	for(int i = 0; i < k; ++i)
	{
		cin >> s;
		p.sequences[i] = s;
	}
	cin >> p.CC;
	MC.resize(aSize + 1);
	for(int i = 0; i < aSize + 1; ++i)
	{
		MC[i].resize(aSize + 1);
		for(int j = 0; j < aSize + 1; ++j)
			cin >> p.MC[i][j];
	}
	cin >> s;
}

void output(SeqNode& n)
{
	for(int i = 0; i < n.data.size(); i++)
		cout<<n.data<<"\n";
}