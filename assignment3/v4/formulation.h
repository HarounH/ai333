using namespace std;

#include<vector>
#include<set>
#include<cmath>

#ifndef FORMULATION_H
#define FORMULATION_H

class Position;
class Move;
class State;
class Player;
class Eval;

#define COMMA ","

class Position{
public:
	int r,c;
	
	void print(bool pr) { if(pr) { cout << "pos_(" << r << COMMA << c << ")" ;} }

	Position() {}
	~Position() {}
	Position(int _r , int _c) { r=_r; c=_c; }
	Position( pair<int,int> x ) { r=x.first ; c=x.second; }

	Position& operator=(const Position& _p) { r = _p.r; c=_p.c; return *this; }
	Position& operator=(const pair<int,int>& _p) { r = _p.first; c=_p.second; return *this; }

	bool operator==(const Position& _p) { return ((r==_p.r)&&(c==_p.c)); }
	bool operator==(const pair<int,int>& _p) { return ((this->r == _p.first) && (this->c == _p.second)); }

	pair<int,int> makepair() { pair<int,int> p; p.first=r; p.second=c; return p; }

	Position up() { Position p(r-1,c); return p; }
	Position down() { Position p(r+1,c); return p; }
	Position right() { Position p(r,c+1); return p; }
	Position left() { Position p(r,c-1); return p; }

	Position d_up() { Position p(r-2,c); return p; }
	Position d_down() { Position p(r+2,c); return p; }
	Position d_right() { Position p(r,c+2); return p; }
	Position d_left() { Position p(r,c-2); return p; }

	Position up_right() { Position p(r-1,c+1); return p; }
	Position up_left() { Position p(r-1,c-1); return p; }
	Position down_right() { Position p(r+1,c+1); return p; }
	Position down_left() { Position p(r+1,c-1); return p; }

	bool is_up(Position& p) {  return (((*this).r==(p.r-1))&&((*this).c==(p.c))); }
	bool is_down(Position& p) {  return (((*this).r==(p.r+1))&&((*this).c==(p.c))); }
	bool is_right(Position& p) {  return (((*this).r==(p.r))&&((*this).c==(p.c+1))); }
	bool is_left(Position& p) {  return (((*this).r==(p.r))&&((*this).c==(p.c-1))); }

	bool is_d_up(Position& p) { return (((*this).r==(p.r-2))&&((*this).c==(p.c))); }
	bool is_d_down(Position& p) { return (((*this).r==(p.r+2))&&((*this).c==(p.c))); }
	bool is_d_right(Position& p) { return (((*this).r==(p.r))&&((*this).c==(p.c+2))); }
	bool is_d_left(Position& p) { return (((*this).r==(p.r))&&((*this).c==(p.c-2))); }

	bool is_up_right(Position& p) {  return (((*this).r==(p.r-1))&&((*this).c==(p.c+1))); }
	bool is_up_left(Position& p) {  return (((*this).r==(p.r-1))&&((*this).c==(p.c-1)))  ;}
	bool is_down_right(Position& p) { return (((*this).r==(p.r+1))&&((*this).c==(p.c+1))) ; }
	bool is_down_left(Position& p) { return (((*this).r==(p.r+1))&&((*this).c==(p.c-1)))  ;}

};

class Move {
public:
	int m,r,c;
	int pn;
	Position from,to;
	double eval; //Optional


	void print(bool pr=false) { cout << "MOVE:: pn=" << pn << "  m=" << m << "\tFROM="; from.print(pr); cout << "\tTO="; to.print(pr) ; cout<< "\n"; }

	Move() {}
	~Move() {}
	Move(int _m, int _r , int _c) { m = _m; r=_r; c=_c; to.r = r; to.c = c; }
	
	Move& operator=(const Move& _m) { m=_m.m; r=_m.r; c=_m.c; pn=_m.pn; from=_m.from; to=_m.to; return *this; }
	bool operator==(const Move& _m) { return ((m==_m.m)&&(r==_m.r)&&(c==_m.c)&&(pn==_m.pn)&&(from==_m.from)&&(to==_m.to)); }

	bool is_jump() { return m==0; }
	bool is_hor_wall() { return m==1; }
	bool is_ver_wall() { return m==2; }
};

class State {
public:
	int N,M,K;
	int pn , mypn;
	Position pos_present , pos_other;
	int n_present_walls , n_other_walls;

	vector< vector< bool > > is_wall_H, is_wall_V;
	set< pair<int,int> > wall_H, wall_V; /* POSSIBLE WIERD STUFF. CONSULT SURAG. */

	double eval;


	State() {}
	~State() {}
	void init(int n, int m , int k , int _mypn);

	State& operator=(const State& s);

	bool paths_exists();
	void apply_move(Move& m);
	void unapply_move(Move& m);

	bool is_endgame() { if ( pn==1 ) { return ((pos_present.r==N)||(pos_other.r==1)); } else {return ((pos_present.r==1)||(pos_other.r==N)); }}
	bool is_win() { if ( pn==1 ) { return (pos_present.r==N); } else {return (pos_present.r==1); }}
	bool is_loss() { if ( pn==1) { return ((pos_other.r==1)); } else {return ((pos_other.r==N)); }}
	
	bool I_won() 
	{
		if (mypn == pn)
		{
			if (mypn == 1) return pos_present.r == N;
			else 		   return pos_present.r == 1;
		}
		
		else
		{
			if (mypn == 1) return pos_other.r == N;
			else		   return pos_other.r == 1;
		}
	}
	
	bool I_lost() 
	{
		if (mypn == pn)
		{
			if (mypn == 1) return pos_other.r == 1;
			else 		   return pos_other.r == N;
		}
		
		else
		{
			if (mypn == 1) return pos_present.r == 1;
			else		   return pos_present.r == N;
		}
	}
	
	void print(bool pr);
	void toggle_player();

	bool in_bounds(Position& p) { return ((p.r>=1)&&(p.r<=N)&&(p.c>=1)&&(p.c<=M)); }

	bool valid_move(Move& m) { return valid_wall(m)&&valid_jump(m) ;}
	bool valid_wall(Move& m);
	bool valid_jump(Move& m);

	//BFS?
	bool connected(Position& from , Position& to);
	
	//Connectivity.
	bool wall_up(Position& p) { return ( (p.r<=1) || ((is_wall_H[p.r][p.c]) || (is_wall_H[p.r][p.c+1] )) ); }
	bool wall_down(Position& p) { return ( ((p.r)>=N) || ((is_wall_H[p.r+1][p.c]) || (is_wall_H[p.r+1][p.c+1] )) ); }
	bool wall_right(Position& p) { return ( ((p.c)>=M) || ((is_wall_V[p.r][p.c+1]) || (is_wall_V[p.r+1][p.c+1] )) ); }
	bool wall_left(Position& p) { return ( (p.c<=1) || (is_wall_V[p.r][p.c]) || (is_wall_V[p.r+1][p.c]) );}
	
	bool wall_d_up(Position& p) { return ( (p.r<=2)||(is_wall_H[p.r-1][p.c])||(is_wall_H[p.r-1][p.c+1]) ); }
	bool wall_d_down(Position& p) { return ( (p.r>=(N-1))||(is_wall_H[p.r+2][p.c])||(is_wall_H[p.r+2][p.c+1]) ); }
	bool wall_d_right(Position& p) { return ( (p.c>=(M-1))||(is_wall_V[p.r][p.c+2])||(is_wall_V[p.r+1][p.c+2]) ); }
	bool wall_d_left(Position& p) { return ( (p.c<=2)||(is_wall_V[p.r][p.c-1])||(is_wall_V[p.r+1][p.c-1]) ); }
	
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
	//END OF CONNECTIVITY.

	//Move generators.
	void get_all_jumps(vector<Move>& moves);
	void get_all_jumps(vector<Move>& moves , Position& p);	
	void get_all_walls(vector<Move>& moves);
	void get_all_moves(vector<Move>& moves) { get_all_jumps(moves);get_all_walls(moves);}

	double evaluate();
};

class Eval {
public:
	Eval() {}
	~Eval() {}

	double shortest_path(State& s , int _pn);
	double diff_shortest_path(State& s) { return (shortest_path(s,((s.pn==1)?(2):(1)))) - shortest_path(s,s.pn) ; } 
};
class Player {
public: 
	State gblState , locState;
	int pn;
	double total_time;
	double remaining_time;
	int remaining_walls;
	Eval evaluator;

	Player() {};
	~Player() {};	

	//Misc
	void print(bool pr);
	void init( int _N , int _M , int _K , int _pn , float max_time );
	void read_time_left_from_client_cpp(float _t);
	void send_move_to_client_cpp(int& m , int& r , int& c);
	void read_move_from_client_cpp(int& m ,int& r, int& c);
	//Minimax
	
	Move minimax( int depth , float time_limit );
    double max_value(double alpha, double beta, int cutoff, int curDepth, float time_limit);
  	double min_value(double alpha, double beta, int cutoff, int curDepth, float time_limit);
	Move best_move;
	
};

#endif