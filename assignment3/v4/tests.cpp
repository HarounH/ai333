#include <iostream>
using namespace std;

#include "formulation.cpp"

int main(int argc, char** argv) {
	State w;
	w.init(9,9,10,2);
	w.pos_present.r = 8;
	w.pos_present.c = 6;
	w.pos_other.r = 4;
	w.pos_other.c = 1;
	w.is_wall_H[2][5] = true;
	w.wall_H.insert(make_pair(2,5));
	w.is_wall_V[2][7] = true;
	w.wall_V.insert(make_pair(2,7));
	 w.is_wall_V[6][6] = true;
	w.wall_V.insert(make_pair(6,6));
	w.print(true);

	w.pn = 2;
	
	for (int r = 1; r<=w.N ; r++)
	{
		for (int c=1 ; c<=w.N ; c++)
		{
			cout << w.inLocality(r,c) << " " ;
		}
		cout << endl;
	}
			
	// vector<Move> movs;
	// w.get_all_walls(movs);
// 	Eval e;
// 	for(int i=0; i<movs.size(); ++i) {
// 		movs[i].print(true);
// 		cout << w.evaluate() << " upon not applying\n";
// 		w.apply_move(movs[i]);
// 		cout << w.evaluate() << " upon applying\n";
// 		w.unapply_move(movs[i]);
// 	}
	// if ( M_PRINT ) {
	// 	cout << "-----------------------\n";
	// 	vector<Move> moves;
	// 	//locState.get_all_walls(moves);
	// 	locState.get_all_jumps(moves);
	// 	for(int i=0; i<moves.size(); ++i) moves[i].print(M_PRINT);
	// 	cout << "-----------------------\n";

	cout << "\n\n\n\n";
		//
	// Eval e;
	// cout << e.shortest_path(w,1) << "\n";
	// cout << e.shortest_path(w,2) << "\n";
	return 1;

} 