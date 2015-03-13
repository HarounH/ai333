#ifndef EVAL_2_CPP
#define EVAL_2_CPP

#include "formulation.h"

#define LOCALITY_THRESHOLD 2.5*2.5

#define WALL_EVAL2 100.0

double Eval::eval_move(State& s, Move& m) {

	if ( m.m== 0 ) {
		m.eval = JUMP_EVAL;
	} else {
		//I want to check gaps and distance from players. Does distance from players really matter?
		//How do i define a gap?
		if ( (m.to.dist_l2(s.pos_present) < LOCALITY_THRESHOLD) || 
			( m.to.dist_l2(s.pos_other)) < LOCALITY_THRESHOLD
			) {
			//High priority.
			m.eval = WALL_EVAL2 + 10.0;
		}
		//Check if a wall in the adjacent spots or not.

		if ( ((m.c<s.M) && s.is_wall_V[m.r][m.c+1]) || ( (m.c>=2) && s.is_wall_V[m.r][m.c-1]) || //is_wall_V[m.r][m.c] || is_wall_V[m.r][m.c]
			 ( (m.r<s.N) && s.is_wall_H[m.r+1][m.c]) || ( (m.r>=2) && s.is_wall_H[m.r-1][m.c]) //|| is_wall_H[m.r][m.c] || is_wall_H[m.r][m.c] 
			) {
				m.eval = WALL_EVAL2 + 11.0;
				//High priority.
		} else {
			m.eval = WALL_EVAL2 - 11.0;
			//Not so high Priority.
		}
	}
	// cout << "Ending Starting move eval\n";
	// cout << "evaluation=" << m.eval << "\n";
	return m.eval;
}

#endif
