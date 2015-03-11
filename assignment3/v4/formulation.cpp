#ifndef FORMULATION_CPP
#define FORMULATION_CPP


#define S_PRINT true
#define M_PRINT true
#define P_PRINT true
#include "formulation.h"

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