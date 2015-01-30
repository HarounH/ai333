#ifndef SEQ_H
#define SEQ_H
#include <iostream>
#include <vector>

using namespace std;

class SeqNode {
public:
	double currentCost;
	vector<int> position;
	vector<string> auxData;
	double heuristicCost;
	double totalCost;
};

class SeqProblem {
public:
	double clockTime;
	int aSize;
	int k;
	double CC;
	vector< vector<double> > MC;
	vector<string> sequences;
	vector<int> stringLengths;
	vector<char> alphabet;
	SeqNode initialState;
	void getSuccessors(SeqNode& n, vector<SeqNode>& successors);
	bool goalTest(SeqNode& n);
	double pathCost(SeqNode& s, SeqNode& t);
};


class SearchAgent {
public:
	double heuristicFunc(SeqProblem& p, SeqNode& n)
	{
		return 0;
	}
};

bool SeqProblem::goalTest(SeqNode& n)
{
	for (int i = 0; i < stringLengths.size(); i++)
	{
		if (n.position[i] != stringLengths[i])
			return false;
		for (int j = i + 1; j < stringLengths.size(); j++)
		{
			if (n.position[j] != stringLengths[j])
				return false;
			if (n.auxData[i].size() != n.auxData[j].size())
				return false;
		}
	}
	return true;
}


/*
This has quite a bit of copying.
Working on it.
*/
void SeqProblem::getSuccessors(SeqNode& n, vector<SeqNode>& successors)
{
	/**for each 2^k possible tuples (consisting of 0's and 1's)
	//new position is position+tuple
	//new cost is previous cost + (CC * number of ones in tuple) + (sum of all cost pairs for that position)
	//possibly update auxData
	//call heuristic function
	//update total cost
	//push into vector
	**/
	successors.reserve(1 << k);
	bool invalid = false;
	for(int i = 1; i < (1 << k); ++i)
	{
		SeqNode s;
		s.currentCost = 0;
		s.position.resize(k);
		vector<int> tuple(k);
		invalid = false;
		int j = i;
		int tupleIndex = 0;
		s.auxData.resize(k);
		copy(n.auxData.begin(), n.auxData.end(), s.auxData.begin());
		while (j != 0)
		{
			int bit = j & 1;
			s.position[tupleIndex] = n.position[tupleIndex] + bit;
			tuple[tupleIndex] = bit;
			if (s.position[tupleIndex] > stringLengths[tupleIndex])
			{
				invalid = true;
				break;
			}
			j >>= 1;
			tupleIndex++;
		}
		if(invalid)
			continue;
		for(int y = 0; y < k; y++)
		{
			if(tuple[y] == 0)
			{
				s.currentCost += CC;
				if(s.position[y] < stringLengths[y])
					s.auxData[y].insert(s.auxData[y].begin() + s.position[y], '-');
				else
					s.auxData[y].push_back('-');
			}
			for(int z = y + 1; z < k; z++)
			{
				if(tuple[y] == 0 && tuple[z] == 0);
				else if(tuple[y] == 0)
					s.currentCost += MC[(int) '-'][(int) sequences[z][s.position[z] - 1]];
				else if(tuple[z] == 0)
					s.currentCost += MC[(int) sequences[y][s.position[y] - 1]][(int) '-'];
				else
					s.currentCost += MC[(int) sequences[y][s.position[y] - 1]][(int) sequences[z][s.position[z] - 1]];
			}
		}
		s.currentCost += n.currentCost;
		SearchAgent sa;
		s.heuristicCost = sa.heuristicFunc(*this, s);
		s.totalCost = s.currentCost + s.heuristicCost;
		successors.push_back(s);
	}
}

#endif