#include "form.cpp"

using namespace std;
int main(int argc, char** argv) {
	State w;
	w.pn = 1;
	w.pos_present = makepair(8,8);
	w.pos_other = makepair(1,6);
	w.n_present_walls = 0;
	w.n_other_walls = 0;

	std::vector<Move> mov;
	w.get_all_moves(mov);
}