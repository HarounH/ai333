#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include "Game.h"

using namespace std;

class Player {
public:
	virtual double operator()(GameState& gs, int myPlayer) = 0;   //need to know if my player is player 1 or player 2
};

#endif