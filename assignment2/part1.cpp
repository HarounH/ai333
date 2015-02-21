#include <iostream>
#include <vector>

using namespace std;
//NODE 0 is reserved
int N, M, K;
vector< vector< bool > > edges; //Stores the adjacency matrix
//vector< vector< int > > adjlist;//stores the adjacency list format UNNECESSARY
//vector< vector< bool > > paths; //stores whether a path exists from i to j UNNECESASRY

enum MODE{
	PRINT_DEBUG, PRINT_ENCODING
};

#include "io_1.cpp"


/*
Clause numbering :
	0 => False
	1-g^2 => edge[i][j]
	g^2 + ( 1 - gk ) => g[i][p]
	g^2 + gk + (1-gkk) => x[i][p][q]

		HENCE MAPPING :
		e[i][j] = i*g + j;
		if ( i*g+j < g^2) then (i*g + j)%g 
*/


void make_nonempty_subgraph(); // k_AND(i_OR(g[i][k]))
void make_node_in_graph();	   // i_AND(k_OR(g[i][k]))
void make_complete_graph();    // ijk_AND( !g[i][k] or !g[j][k] or e[i][j])
void make_edge_in_graph();	   // if(e[i][j]) then { g[x1][1] + g[x2][2] .... g[xg][k]} | xi belongs to {i,j}
void make_notsubgraph();	   // very complicated.

void generate_clauses();
int main(int argc, char** argv) {
	input_1();
	//updatePaths(paths); //Unnecessary.
	generate_clauses();
	
	output_1(PRINT_DEBUG);
	return 0;
}
//Controls the loop itself.
void generate_clauses() {
	make_nonempty_subgraph();
}

void make_nonempty_subgraph() {
	for(int k=1; k<K+1; ++k) {
		//For each k, OR of g[i][k]
	}
}