#ifndef FORM_H
#define FORM_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <stack>

class Position {
public:
	int r,c;
	Position(int R,int C) { r=R;c=C; }
	Position(pair<int,int> p) { r=p.first; c=p.second; }
	Position(const Position C) {r=C.r; c=C.c;}
	~Position() {} //Does Nothing.
	Position& operator=(Position& o) { r=o.r; c=o.c; return *this;}
	Position& operator=(pair<int,int> o) { r=o.first; c=o.second; return *this;}
	pair<int,int> makepair() { pair<int,int> p; p.first=r; p.second=c; return p; }

	Position up();
		bool isup(Position& o);
	Position down();
		bool isdown(Position& o);
	Position right();
		bool isright(Position& o);
	Position left();
		bool isleft(Position& o);
	Position d_up();
		bool isdup(Position& o);
	Position d_down();
		bool isddown(Position& o);
	Position d_right();
		bool isdright(Position& o);
	Position d_left();
		bool isdleft(Position& o);
	Position up_right();
		bool isupright(Position& o);
	Position up_left();
		bool isupleft(Position& o);
	Position down_right();
		bool isdownright(Position& o);
	Position down_left();
		bool isdownleft(Position& o);

	int l1_norm(Position& x) { return abs(r-x.r) + abs(c-x.c); }
	void print();
};

class Move {
public:
	int m,pn; Position from, Position to;
	double eval; //Evaluations of the state are put in here, temporarily. Thing is, we evaluate states. and states encapsulate all moves played.
	double my_shortest_path, op_shortest_path;

	Move(int M, int R, int C) 	{ m=M; to.r = R; to.c = C; }
	Move& operator=(Move& mov) 	{ m=mov.m; pn=mov.pn; from=mov.from;to=mov.to; eval=mov.eval; 	 }
	bool operator==(Move& mov) 	{ return (m==mov.m && from==mov.from && to=mov.to && pn==mov.pn);}
	bool operator<(Move mov) 	{ return eval>mov.eval; }
	bool operator>(Move mov) 	{ return eval<mov.eval; }
	void print();
}pass_move(0,0,0);

class State {
public:
	Move causal_move;
	int N, int M, int K; int pn,mypn,opn; /* pn=present player, mypn = my player number , opn = other player. */
	int plies;
	Position pos_present , pos_other;
	int n_present_walls , n_other_walls;
	vector< vector< bool > > is_wall_H, is_wall_V;
	set< pair<int,int> > wall_H,wall_V;
	vector< vector< bool > > can_wall_H , can_wall_V; /* tells you if you can place a wall at a given place, WITHOUT LOOKING at shortest path. */


	void init(int n, int m , int k , int _mypn);
	State& operator=(const State& s);
	
	/* Queries about game state. */
	bool is_endgame();
	bool i_won();
	bool i_lost();

	/* Updating game state. */
	void toggle_player();
	void apply_move(Move& m);
	void unapply_move(Move& m);

	/* Queries for point location. */
	bool in_bounds(Position& p); /* Tells you whether p is on the board or not. */
	bool in_bounds_wall(int r,int c); /* Tells you whether or not in_bounds_wall is valid place at game-start. */

	/* Queries for is a wall is present relative to given position. */
	bool wall_up(Position& p) { return ( (p.r<=1) || ((is_wall_H[p.r][p.c]) || (is_wall_H[p.r][p.c+1] )) ); }
	bool wall_down(Position& p) { return ( ((p.r)>=N) || ((is_wall_H[p.r+1][p.c]) || (is_wall_H[p.r+1][p.c+1] )) ); }
	bool wall_right(Position& p) { return ( ((p.c)>=M) || ((is_wall_V[p.r][p.c+1]) || (is_wall_V[p.r+1][p.c+1] )) ); }
	bool wall_left(Position& p) { return ( (p.c<=1) || (is_wall_V[p.r][p.c]) || (is_wall_V[p.r+1][p.c]) );}
	
	bool wall_d_up(Position& p) { return ( (p.r<=2)||(is_wall_H[p.r-1][p.c])||(is_wall_H[p.r-1][p.c+1]) ); }
	bool wall_d_down(Position& p) { return ( (p.r>=(N-1))||(is_wall_H[p.r+2][p.c])||(is_wall_H[p.r+2][p.c+1]) ); }
	bool wall_d_right(Position& p) { return ( (p.c>=(M-1))||(is_wall_V[p.r][p.c+2])||(is_wall_V[p.r+1][p.c+2]) ); }
	bool wall_d_left(Position& p) { return ( (p.c<=2)||(is_wall_V[p.r][p.c-1])||(is_wall_V[p.r+1][p.c-1]) ); }
	
	/* Queries for is one can move to a position above. */
	bool connected_up(Position& p);
	bool connected_down(Position& p);
	bool connected_right(Position& p);
	bool connected_left(Position& p);

	bool connected_d_up(Position& p);
	bool connected_d_down(Position& p);
	bool connected_d_right(Position& p);
	bool connected_d_left(Position& p);

	bool connected_up_right(Position& p);
	bool connected_up_left(Position& p);
	bool connected_down_right(Position& p);
	bool connected_down_left(Position& p);

	/* Generating moves. */
	void get_all_jumps(vector<Move>& moves);
	void get_all_jumps(vector<Move>& moves , Position& p);	
	void get_all_walls(vector<Move>& moves);
	void get_all_jumps(stack<Move>& moves);
	void get_all_jumps(stack<Move>& moves , Position& p);	
	void get_all_walls(stack<Move>& moves);

	/* State evaluation. */
	double evaluate();
	
	double shortest_path(int forpn); //Gets the shortest path to goal for the given player.
	double shortest_path(int forpn , Position& goal); //Gets the shortest path to goal for the given player to the goal state.
	
	bool touchesWall(int r, int c);
	bool inLocality(int r, int c);
};

class Player { 
public:
	State gblState , locState;
	int pn,remaining_walls; double total_time; double remaining_time;
	int plies;
	
	double get_time_schedule(); //gets you the time to be spent on this move.

	void print();

	/* For learning */
	vector<double> feature_coeffs;
	vector<double> coeff_val;
	void adjust_coeff(vector<double>& feature_list , vector<double> feature_coeffs_list , double)
	void read_coeff_from_file();
	void write_coeff_from_file();	
	
	/* Interact with client.cpp */
	void init();
	void read_move_from_client_cpp(int& m, int& r , int& c);
	void send_move_to_client_cpp(int& m, int& r , int& c);
	void read_time_left_from_client_cpp(double tl);

	Move best_move;
	
	double max_value(double a, double b, int cutoff, int curdept, float tl);
	double min_value(double a, double b, int cutoff, int curdept, float tl);

	Move ordinary_mmx(int depth, float timelimit);
	Move iterative_mmx(int d, double t);
	Move itd_mmx(float timelimit);
	Move learn_mmx(int depth, float timel);
}

#endif