#include <iostream>
using namespace std;

#include "formulation.cpp"
/*
int main(int argc, char** argv) {
	State w;
	w.init(9,9,10);
	w.print(true);
	cout << "\n\n\n\n";
	w.pos_present.r = 6;
	w.pos_present.c = 5;
	w.is_wall_V[7][5] = true;
	Position t(6,5);
	w.wall_V.insert( make_pair(6,5) );

	w.print(true);
	std::vector<Move> movs;
	w.get_all_jumps(movs);

	for(int i=0; i< movs.size(); ++i) {
		movs[i].print(true);
		cout << "\n";
	}
	return 1;
} */