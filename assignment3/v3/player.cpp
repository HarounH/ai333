#ifndef PLAYER_CPP
#define PLAYER_CPP
#include "player.h"

//Initialization and apply move and also communicate to client.
#include "misc.cpp"

//Get moves.
#include "valid_move.cpp"
#include "move_generator.cpp"

//Do Minimax
#include "minimax.cpp"
#include "eval.cpp"

bool State::is_endgame() { return ( (player_1.r == N)||(player_2.r == 1) ); }

#endif