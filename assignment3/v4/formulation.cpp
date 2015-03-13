#ifndef FORMULATION_CPP
#define FORMULATION_CPP


#define S_PRINT false
#define M_PRINT true
#define P_PRINT true
#define JUMP_EVAL 100.0
#define WALL_EVAL 0.0

#include "formulation.h"

//BFS to check if both players
#include "bfs.cpp"

//Comms between Client and Player.
#include "communications.cpp"
//Initializations and the sort.
#include "misc.cpp"
//Checking for connectivity between Positions.
#include "connectivity.cpp"
//Generating all the moves - and applying them.
#include "move_gen.cpp"




//Minimax and eval
#include "minimax.cpp"
#include "eval.cpp"
#endif