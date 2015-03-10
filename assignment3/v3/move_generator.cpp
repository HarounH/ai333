#ifndef MOVE_GENERATOR_CPP
#define MOVE_GENERATOR_CPP

#include "valid_move.cpp"

void State::get_all_moves(std::vector<Move>& moves) {
	Move mov;
		mov._pn = present_player;
		mov._pr = pos_present_player.r;
		mov._pc = pos_present_player.c;
		
	//Part1 : 12 Moves.

	//part2 : Wall moves.
}
#endif