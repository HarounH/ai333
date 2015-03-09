#ifndef GRAPH_CPP
#define GRAPH_CPP
#include "game_player.h"
/*

class Graph { //The Graph tells me if two cells are adjacent to each other.
	int N,M;
	//N - M States and booleans connecting them.
	vector< vector< bool > > adjacent;

	Graph(); //Does Nothing.
	void init( int& _N , int& _M ); //Resizes the matrices.

	void apply_move(Move& m); //if the move is of type 1 or 2 , make appropriate changes.
};

*/

Graph::Graph() {
	//Pass;
}

void Graph::init( int& _N , int& _M) {
	this->N = _N;
	this->M = _M;
	adjacent.resize(N-1);
	for(int i=0; i<(N-1); ++i) {
		adjacent[i].resize(M-1);
	}
	return;
}

void apply_move(Move& m) {
	if ( m.m == 0 ) {
		return;
	} else {

	}
}
#endif