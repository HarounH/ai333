#ifndef EVAL_2_CPP
#define EVAL_2_CPP
double Eval::eval_move(State& s, Move& m) {
	if ( m.m== 0 ) {
		m.eval = JUMP_EVAL;
	} else {
		//I want to check gaps and distance from players. Does distance from players really matter?
		//How do i define a gap?
	}
	return 0.0;
}

#endif
