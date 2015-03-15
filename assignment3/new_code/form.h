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
	Position() {}
	Position(int R,int C) { r=R;c=C; }
	Position(pair<int,int> p) { r=p.first; c=p.second; }
	Position(const Position& C) {r=C.r; c=C.c;}
	~Position() {} //Does Nothing.
	Position& operator=(Position& o) { r=o.r; c=o.c; return *this;}
	Position& operator=(pair<int,int>& o) { r=o.first; c=o.second; return *this;}
	Position& operator=(const Position& o) { r=o.r; c=o.c; return *this;}
	Position& operator=(const pair<int,int>& o) { r=o.first; c=o.second; return *this;}
	// Position& operator=(Position& o) { r=o.r; c=o.c; return *this;}
	// Position& operator=(pair<int,int> o) { r=o.first; c=o.second; return *this;}
	bool operator==(const Position& _p) { return ((r==_p.r)&&(c==_p.c)); }
	bool operator==(const pair<int,int>& _p) { return ((this->r == _p.first) && (this->c == _p.second)); }

	pair<int,int> makepair() { pair<int,int> p; p.first=r; p.second=c; return p; }

	Position up() ;
	Position down() ;
	Position right() ;
	Position left() ;

	Position d_up() ;
	Position d_down() ;
	Position d_right() ;
	Position d_left() ;

	Position up_right() ;
	Position up_left() ;
	Position down_right();
	Position down_left();

	bool is_up(Position& p) ;
	bool is_down(Position& p) ;
	bool is_right(Position& p);
	bool is_left(Position& p) ;

	bool is_d_up(Position& p) ;
	bool is_d_down(Position& p) ;
	bool is_d_right(Position& p);
	bool is_d_left(Position& p);

	bool is_up_right(Position& p) ;
	bool is_up_left(Position& p) ;
	bool is_down_right(Position& p);
	bool is_down_left(Position& p) ;

	int l1_norm(Position& x) ;
	double l2_norm(Position& p);
	void print();
};

class Move {
public:
	int m,r,c,pn; Position from; Position to;
	double eval; //Evaluations of the state are put in here, temporarily. Thing is, we evaluate states. and states encapsulate all moves played.
	double my_shortest_path, op_shortest_path;
	int mmx_d; //Depth in the game tree.

	Move() { mmx_d = -1; }
	~Move() {}
	Move(int M, int R, int C) 	{ m=M; to.r = R; to.c = C; r=R; c=C; mmx_d = -1; }
	Move& operator=(Move mov) 	{ /* SORT and MMX had problems with this. So I want to make sure that this is correct. each time. */
		m=mov.m; 
		pn=mov.pn; 
		from=mov.from;
		to=mov.to; 
		r=mov.r;
		c=mov.c;
		eval=mov.eval; 
		my_shortest_path=mov.my_shortest_path; 
		op_shortest_path=mov.op_shortest_path;
		mmx_d = mov.mmx_d;
		return *this;
	}
	bool operator==(Move& mov) 	{ return ((m==mov.m) && (from==mov.from) && (to==mov.to) && (pn==mov.pn) && (mmx_d==mov.mmx_d));}
	// bool operator<(Move mov) 	{ return eval>mov.eval; }
	// bool operator>(Move mov) 	{ return eval<mov.eval; }
	void print();
};

class State {
public:
	stack<Move> causal_moves;
	int N; int M; int K; int pn,mypn,opn; /* pn=present player, mypn = my player number , opn = other player. */
	int plies;
	Position pos_present , pos_other;
	int n_present_walls , n_other_walls;
	vector< vector< bool > > is_wall_H, is_wall_V;
	set< pair<int,int> > wall_H,wall_V;
	vector< vector< bool > > can_wall_H , can_wall_V; /* tells you if you can place a wall at a given place, WITHOUT LOOKING at shortest path. */

	State() {}
	~State() {}
	void init( int _N , int _M , int _K , int _pn);// , float max_time );
	State& operator=(const State& s);
	
	void print(); //Yay! A print function!
	/* Queries about game state. */
	bool is_endgame();
	bool i_won();
	bool i_lost();
	bool present_lost();
	bool present_won();
	/* Updating game state. */
	void toggle_player();
	void apply_move(Move& m);
	void unapply_move(Move& m);

	/* Queries for point location. */
	bool in_bounds(Position& p); /* Tells you whether p is on the board or not. */
	bool in_bounds(int r,int c); /* Tells you whether p is on the board or not. */
	bool in_bounds_wall(int r,int c); /* Tells you whether or not in_bounds_wall is valid place at game-start. */
	bool in_bounds_wall(Position& p); /* Tells you whether or not in_bounds_wall is valid place at game-start. */

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

	/* Queries for validity of moves/walls */
	bool valid_wall(Move& m);
	bool valid_jump(Move& m);
	bool valid_move(Move& m) { return (valid_wall(m)&&valid_jump(m)) ;}
	/* Generating moves. */
	void get_all_jumps(vector<Move>& moves);
	void get_all_jumps(vector<Move>& moves , Position& p);	
	void get_all_walls(vector<Move>& moves);
	void get_all_moves(vector<Move>& moves) { get_all_jumps(moves); get_all_walls(moves); }

	void get_all_jumps_stack(stack<Move>& moves);
	void get_all_jumps_stack(stack<Move>& moves , Position& p);	
	void get_all_walls_stack(stack<Move>& moves);
	
	void get_all_moves_stack(stack<Move>& moves) { get_all_jumps_stack(moves); get_all_walls_stack(moves); }
	
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
	int pn,remaining_walls; float total_time; float remaining_time;
	int plies;
	
	float get_time_schedule(); //gets you the time to be spent on this move.

	void print();

	/* For learning */
	vector<double> feature_coeffs;
	vector<double> coeff_val;
	void adjust_coeff(vector<double>& feature_list , vector<double> feature_coeffs_list , double expectation, double reality);
	void read_coeff_from_file();
	void write_coeff_from_file();	
	
	/* Interact with client.cpp */
	void init( int _N , int _M , int _K , int _pn , float max_time );
	void read_move_from_client_cpp(int& m, int& r , int& c);
	void send_move_to_client_cpp(int& m, int& r , int& c);
	void read_time_left_from_client_cpp(float tl);

	Move best_move;
	
	double max_value(double a, double b, int cutoff, int curdept, float tl);
	double min_value(double a, double b, int cutoff, int curdept, float tl);

	Move ordinary_mmx(int depth, float timelimit);
	//Move iterative_mmx(int d, double t);
	//Move itd_mmx(float timelimit);
	//Move learn_mmx(int depth, float timel);
};
void Player::init( int _N , int _M , int _K , int _pn , float max_time ) {
	pn = _pn;
	total_time = max_time;
	remaining_time = max_time;
	remaining_walls = _K;
	plies = 0;
	gblState.init(_N,_M,_K , pn);
	locState.init(_N,_M,_K , pn);
	//Add stuff?

	// gblState.print(S_PRINT);
	// locState.print(S_PRINT);
	return;

}
#endif