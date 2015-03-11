#ifndef FORMULATION_H
#define FORMULATION_H

class Position;
class Move;
class State;
class Player;

#define COMMA ","

class Position{
public:
	int r,c;
	
	void print(bool pr) { if(pr) { cout << "pos_(" << r << COMMA << c << ")" ;} }

	Position() {}
	~Position() {}
	Position(int _r , int _c) { r=_r; c=_c; }
	Position( pair<int,int> x ) { r=x.first ; c=x.second; }

	Position& operator=(const Position _p) { r = _p.r; c=_p.c; return *this; }
	Position& operator=(const pair<int,int> _p) { r = _p.first; c=_p.second; return *this; }

	bool operator==(const Position _p) { return ((r==_p.r)&&(c==_p.c)); }
	bool operator==(const pair<int,int>& _p) { return ((this->r == _p.first) && (this->c == _p.second)); }

	pair<int,int>& pair() { pair<int,int> p; p.first=r; p.second=r; return p; }

	Position& up() { Position p(r-1,c); return p; }
	Position& down() { Position p(r+1,c); return p; }
	Position& right() { Position p(r,c+1); return p; }
	Position& left() { Position p(r,c-1); return p; }

	Position& d_up() { Position p(r-2,c); return p; }
	Position& d_down() { Position p(r+2,c); return p; }
	Position& d_right() { Position p(r,c+2); return p; }
	Position& d_left() { Position p(r,c-2); return p; }

	Position& up_right() { Position p(r-1,c+1); return p; }
	Position& up_left() { Position p(r-1,c-1); return p; }
	Position& down_right() { Position p(r+1,c+1); return p; }
	Position& down_left() { Position p(r+1,c-1); return p; }

	bool is_up(Position& p) {  return (((*this).r==(p.r-1))&&(*this).c==(p.c))); }
	bool is_down(Position& p) {  return (((*this).r==(p.r+1))&&(*this).c==(p.c))); }
	bool is_right(Position& p) {  return (((*this).r==(p.r))&&(*this).c==(p.c+1))); }
	bool is_left(Position& p) {  return (((*this).r==(p.r))&&(*this).c==(p.c-1))); }

	bool is_d_up(Position& p) { return (((*this).r==(p.r-2))&&(*this).c==(p.c))); }
	bool is_d_down(Position& p) { return (((*this).r==(p.r+2))&&(*this).c==(p.c))); }
	bool is_d_right(Position& p) { return (((*this).r==(p.r))&&(*this).c==(p.c+2))); }
	bool is_d_left(Position& p) { return (((*this).r==(p.r))&&(*this).c==(p.c-2))); }

	bool is_up_right(Position& p) {  return (((*this).r==(p.r-1))&&(*this).c==(p.c+1))) }
	bool is_up_left(Position& p) {  return (((*this).r==(p.r-1))&&(*this).c==(p.c-1)))  }
	bool is_down_right(Position& p) { return (((*this).r==(p.r+1))&&(*this).c==(p.c+1)))  }
	bool is_down_left(Position& p) { return (((*this).r==(p.r+1))&&(*this).c==(p.c-1)))  }

};

class Move {
public:
	int m,r,c;
	int pn;
	Position from,to;
	double eval;
	void print(bool pr=false) { cout << "MOVE:: pn=" << pn << "  m=" << m << "\tFROM="; from.print(pr); cout << "\tTO="; to.print(pr) << "\n"; }

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
	int pn;
	Position pos_present , pos_other;
	int n_present_walls , n_other_walls;

	vector< vector< bool > > is_wall_H, is_wall_V;
	std::set< pair<int,int> > wall_H, wall_V;



	State() {}
	~State() {}
	void init(int n, int m , int k);

	State& operator=(const State& s);

	void apply_move(Move& m);
	void unapply_move(Move& m);

	bool is_endgame() { if ( pn==1 ) { return ((pos_present.r==N)||(pos_other.r==1)); } else {return ((pos_present.r==1)||(pos_other.r==N)); }}
	bool is_win() { if ( pn==1 ) { return (pos_present.r==N); } else {return (pos_present.r==1); }}
	bool is_loss() { if ( pn==1) { return ((pos_other.r==1)); } else {return ((pos_other.r==N)); }}
	void print(bool pr);
	void toggle_player();

	bool in_bounds(Position& p) { return ((p.r>=1)&&(p.r<=N)&&(p.c>=1)&&(p.c<=M)); }

	bool valid_wall(Move& m);
	bool valid_jump(Move& m);

	//BFS?
	bool connected(Position& from , Position& to);
	
	//Connectivity.
	bool connected_up(Position& p);
	bool connected_down(Position& p);
	bool connected_right(Position& p);
	bool connected_left(Position& p);

	bool connected_double_up(Position& p);
	bool connected_double_down(Position& p);
	bool connected_double_right(Position& p);
	bool connected_double_left(Position& p);

	bool connected_up_right(Position& p);
	bool connected_up_left(Position& p);
	bool connected_down_right(Position& p);
	bool connected_down_left(Position& p);
	//END OF CONNECTIVITY.

	//Move generators.
	void get_all_jumps(vector<Move>& moves);
	void get_all_walls(vector<Move>& moves);
	void get_all_moves(vector<Move>& moves) { get_all_jumps(moves);get_all_walls(moves);}

};

class Player {
	State gblState , locState;
	int pn;
	double total_time;
	double remaining_time;
	int remaining_walls;

	Move best_move;

	Player() {};
	~Player() {};	

	//Misc
	void print(bool pr);
	void init( int _N , int _M , int _K , int _pn , float max_time );
	void read_time_left_from_client_cpp(float _t);
	void send_move_to_client_cpp(int& m , int& r , int& c);
	void read_move_from_client_cpp(int& m ,int& r, int& c);
	//Minimax

};
#endif