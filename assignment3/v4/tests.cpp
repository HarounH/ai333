#include <iostream>
using namespace std;

#include "formulation.cpp"

int main(int argc, char** argv) {
	State w;
	w.init(9,9,10);
	w.pos_present.r = 6;
	w.pos_present.c = 5;
	w.is_wall_H[7][5] = true;
	w.wall_H.insert(make_pair(7,5));
	w.is_wall_V[6][4] = true;
	w.wall_V.insert(make_pair(6,4));
	w.is_wall_V[6][6] = true;
	w.wall_V.insert(make_pair(6,6));
	w.print(true);
	cout << "\n\n\n\n";
	
	Eval e;
	cout << e.shortest_path(w,1) << "\n";
	cout << e.shortest_path(w,2) << "\n";
	return 1;
} 