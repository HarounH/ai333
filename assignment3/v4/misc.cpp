#ifndef MISC_CPP
#define MISC_CPP

void State::print(bool sp) {
	if ( sp ) {
		cout << " Present Player=" << pn << "\n";
		pos_present.print(sp);
		cout << "\n Other Player @"; pos_other.print(sp);

		std::set< pair<int,int> >::iterator it;
		cout << "\n Horizontal walls at: \n";
		for( it=pos_wall_H.begin(); it != pos_wall_H.end(); ++it) {
			cout << "Horizontal::: \t\t("<< (*it).first<<","<< (*it).second <<")\n"; 
		}
		cout << "\n Vertical walls at: \n";
		for( it=pos_wall_V.begin(); it != pos_wall_V.end(); ++it) {
			cout << "Vertical:::::\t\t("<< (*it).first<<","<< (*it).second <<")\n"; 
		}

		cout << " Printing is_wall_H ... NOTE: ITS ONLY THE CENTRES OF THE WALLS \n";
		for(int r=1; r<=N; ++r) {
			for(int c=1; c<=M; ++c) {
				cout << is_wall_H[r][c] << " ";
			}
			cout << "\n";
		}

		cout << " Printing is_wall_V ... NOTE: ITS ONLY THE CENTRES OF THE WALLS \n";
		for(int r=1; r<=N; ++r) {
			for(int c=1; c<=M; ++c) {
				cout << is_wall_V[r][c] << " ";
			}
			cout << "\n";
		}
	}
}

void State::init(int n, int m , int k) {
	N = n;
	M = m;
	K = k;
	pn = 1;
	n_present_walls = K; n_other_walls = K;
	pos_present = make_pair(1,(M+1)/2);
	pos_other = make_pair(N, (M+1)/2 );

	is_wall_H.resize(N+3);
	is_wall_V.resize(N+3);

	for(int i = 0; i<N+2; ++i) {
		is_wall_V[i].resize(M+3,false); //Extra size to allow for easy life later on.
		is_wall_H[i].resize(M+3,false); //Extra size to allow for easy life later on.
	}
	//Add stuff?
	return;
}

State& State::operator=(const State& s) {
	N = s.N; M = s.M; K = s.K;
	
	pos_present = s.pos_present;
	pos_other = s.pos_other;
	n_present_walls = nos_prese_wallsnt;
	n_other_walls = s.n_other_walls;

	is_wall_H = s.is_wall_H;
	is_wall_V = s.is_wall_V;
	pos_wall_H = s.pos_wall_H;
	pos_wall_V = s.pos_wall_V;

	return *this;
}

void Player::init( int _N , int _M , int _K , int _pn , float max_time ) {
	pn = _pn;
	total_time = max_time;
	remaining_time = max_time;
	remaining_walls = _K;
	gblState.init(_N,_M,_K);
	locState.init(_N,_M,_K);
	//Add stuff?
	return;
}

void Player::print(bool pr) {
	cout << "####PLAYER####\n";
	cout << "\tpn="<<pn<<"\n";
}
#endif