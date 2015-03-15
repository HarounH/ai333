#ifndef LEARNER_CPP
#define LEARNER_CPP
#include<fstream>

#include "learner.h"

#define INF 10000000.0

void read_coeff() {
	//Read all limes until the last line.

}

void write_coeff() {
	fstream writer;
		writer.
}

Move Learner::learningMinimax(int max_d , double max_t) {
	double expectation = player.locState.evaluate( newc ); //Get the expectation of the given state.
	//I now have the expected value, so i shall do minimax and get the actual value.
	double reality = learningMaxValue( -INF , +INF , max_d , 0 , max_t , player);

	//Doesn't really attemp to figure out why it lost.
	adjustCoeff( expectation , reality ); //Has the coefficients built in.
	play();
}

double Learner::learningMaxValue(double a , double b , int max_d , int cur_d , double tl , Player& pl) {
	if ( (cur_d == max_d) || pl.locState.is_endgame() ) {
		return locState.evaluate();
	} else {
		std::vector<Move> moves;
		double ret = -INF;
		pl.locState.get_all_moves(moves);
		//TODO : Sort the moves vector?
		for(int i=0; i<moves.size(); ++i) {
			pl.locState.apply_move(moves[i]);
			//Now at a min_node.
			double ret_temp = max(ret , learningMinValue(a,b,max_d,cur_d+1,tl,pl));
			if ( ret_temp > ret ) {
				//If I'm at least as good, I should tell him first.
				ret = ret_temp;
				if ( cur_d == 0 ) {
					pl.best_move = moves[i];
				}
			}
			if ( ret >= b ) {
				locState.unapply_move(moves[i]);
				return ret;
			}
			a = max(a,ret);
			pl.locState.unapply_move(moves[i]);
		}
	}
	return ret;
}


double Learner::learningMinValue(double a , double b , int max_d , int cur_d , double tl , Player& pl) {
	if ( (cur_d == max_d) || pl.locState.is_endgame() ) {
		return pl.locState.evaluate();
	} else {
		std::vector<Move> moves;
		pl.locState.get_all_moves(moves);
		double ret = INF;
		
		for(int i=0; i<moves.size(); ++i) {
			pl.locState.apply_move(moves[i]);
			//Now at a min_node.
			double ret_temp = max(ret , learningMaxValue(a,b,max_d,cur_d+1,tl,pl));
			if ( ret <= a ) {
				locState.unapply_move(moves[i]);
				return ret;
			}
			b = min(b,ret);
			pl.locState.unapply_move(moves[i]);
		}
	}
	return ret;
}


#endif