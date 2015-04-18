inline double rng(long acc=10000000) {
	return (rand()%acc)/(double)acc;
}

void get_spiral_walls(std::vector<Move>& moves) {
	Move mov;
	mov.pn = pn;
	mov.from = pos_present;
	bool possible = true;
	std::vector<Position> corners(4);
	int delta = 0;
	#define RD 0
	#define RU 1
	#define LU 2
	#define LD 3
	bool flagRDRU , flagRULU , flagLULD , flagLDRD;
	flagLDRD = flagRULU = flagLULD = flagRDRU = true;
	while(possible) {
		if (pos_other.r + delta > N) {
			flagRULU = false;
		}
		if (pos_other.r - delta <=0 ) {
			flagLDRD = false;
		}
		if ( pos_other.c + delta > M) {
			flagRDRU = false;
		}
		if (pos_other.c - delta <= 0) {
			flagLULD = false;
		}
		corners[RD] = pos_other + make_pair(delta,-delta);
		corners[RU] = pos_other + make_pair(delta,delta);
		corners[LU] = pos_other + make_pair(-delta,delta);
		corners[LD] = pos_other + make_pair(-delta,-delta);
		for(int i=-delta; i<=delta; ++i) {
			if ( flagRULU ) {
				mov.r=pos_other.r + delta;
				mov.c=pos_other.c + i;
				mov.m=1;
				if ( valid_wall(mov) && in_bounds_wall(mov.r,mov.c)) {
					moves.push_back(mov);
				}
				mov.m=2;
				if ( valid_wall(mov) && in_bounds_wall(mov.r,mov.c)) {
					moves.push_back(mov);
				}
			}
			if ( flagLULD ) {
				mov.c=pos_other.c - delta;
				mov.r=pos_other.r + i;
				if ( valid_wall(mov) && in_bounds_wall(mov.r,mov.c)) {
					moves.push_back(mov);
				}
				mov.m=2;
				if ( valid_wall(mov) && in_bounds_wall(mov.r,mov.c)) {
					moves.push_back(mov);
				}
			}
			if ( flagLDRD ) {
				mov.r=pos_other.r - delta;
				mov.c=pos_other.c + i;
				if ( valid_wall(mov) && in_bounds_wall(mov.r,mov.c)) {
					moves.push_back(mov);
				}
				mov.m=2;
				if ( valid_wall(mov) && in_bounds_wall(mov.r,mov.c)) {
					moves.push_back(mov);
				}
			}
			if ( flagRDRU ) {
				mov.c=pos_other.c + delta;
				mov.r=pos_other.r + i;
				if ( valid_wall(mov) && in_bounds_wall(mov.r,mov.c)) {
					moves.push_back(mov);
				}
				mov.m=2;
				if ( valid_wall(mov) && in_bounds_wall(mov.r,mov.c)) {
					moves.push_back(mov);
				}
			}
		}
		delta++;
		possible = flagRDRU && flagLDRD && flagLULD && flagRULU;
	}
	return;
	#undef RD
	#undef RU
	#undef LU
	#undef LD
}

Move State::get_complete_random_wall() {
	Move mov;
	mov.pn = pn;
	mov.from = pos_present;
	bool valid = false;
	while(!valid) {
		if ( rng() >0.5 ) {mov.m = 1;} else {mov.m = 2;} //vertical v/s horizontal with P = 0.5
		mov.r = 2 + (N-2)*rng(); //goes between 2 -> N-1
		mov.c = 2 + (M-2)*rng();	
		valid = valid_wall(mov)&&in_bounds_wall(mov.r,mov.c);
	}
	mov.to = Position(mov.r,mov.c);
	return mov;
}

Move State::get_biased_random_wall() { //with a mean equal to the other players' position. 
	Move mov;
	mov.pn = pn;
	mov.from = pos_present;
	bool valid = false;
	while(!valid) {
		if ( rng() >0.5 ) {mov.m = 1;} else {mov.m = 2;}  //vertical v/s horizontal with P = 0.5
		mov.r = pos_other.r + (N-2)*(rng() - 0.5); //goes between 2 -> N-1
		mov.c = pos_other.c + (M-2)*(rng() - 0.5);	
		valid = valid_wall(mov)&&in_bounds_wall(mov.r,mov.c);
	}
	mov.to = Position(mov.r,mov.c);
	return mov;	
}