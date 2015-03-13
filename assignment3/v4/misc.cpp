#ifndef MISC_CPP
#define MISC_CPP

void State::print(bool sp) {
	if ( sp ) {
		cout << " Present Player=" << pn << "\n";
		pos_present.print(sp);
		cout << "\n Other Player @"; pos_other.print(sp);

		std::set< pair<int,int> >::iterator it;
		cout << "\n Horizontal walls at: \n";
		for( it=wall_H.begin(); it != wall_H.end(); ++it) {
			cout << "Horizontal::: \t\t("<< (*it).first<<","<< (*it).second <<")\n"; 
		}
		cout << "\n Vertical walls at: \n";
		for( it=wall_V.begin(); it != wall_V.end(); ++it) {
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

void State::init(int n, int m , int k , int _mypn) {
	N = n;
	M = m;
	K = k;
	pn = 1;
	mypn = _mypn;
	n_present_walls = K; n_other_walls = K;
	pos_present = make_pair(1,(M+1)/2);
	pos_other = make_pair(N, (M+1)/2 );

	is_wall_H = vector<vector<bool> >(N+3, vector<bool>(M+3,false));		// SNair - changed way of declaration
	is_wall_V = vector<vector<bool> >(N+3, vector<bool>(M+3,false));
	
//	is_wall_H.resize(N+3);
//	is_wall_V.resize(N+3);

//	for(int i = 0; i<N+2; ++i) {
//		is_wall_V[i].resize(M+3,false); //Extra size to allow for easy life later on.
//		is_wall_H[i].resize(M+3,false); //Extra size to allow for easy life later on.
//	}
	//Add stuff?
	return;
}

State& State::operator=(const State& s) {
	N = s.N; M = s.M; K = s.K; pn = s.pn;
	mypn = s.mypn;
	pos_present = s.pos_present;
	pos_other = s.pos_other;
	n_present_walls = s.n_present_walls;
	n_other_walls = s.n_other_walls;

	is_wall_H = s.is_wall_H;
	is_wall_V = s.is_wall_V;
	wall_H = s.wall_H;
	wall_V = s.wall_V;

	return *this;
}

void Player::init( int _N , int _M , int _K , int _pn , float max_time ) {
	pn = _pn;
	total_time = max_time;
	remaining_time = max_time;
	remaining_walls = _K;
	gblState.init(_N,_M,_K , pn);
	locState.init(_N,_M,_K , pn);
	//Add stuff?

	gblState.print(S_PRINT);
	locState.print(S_PRINT);
	return;
}

void Player::print(bool pr) {
	cout << "####PLAYER####\n";
	cout << "\tpn="<<pn<<"\n";
	cout << "\twls="<< remaining_walls << "\n";
}
#endif