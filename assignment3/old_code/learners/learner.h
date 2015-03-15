#ifndef LEARNER_H
#define LEARNER_H

#include "formulation.cpp"

#define LOGFILE "LOG_"


class Learner {
	int version;
	vector<double> newc; //Coefficients.
	vector<double> oldc;
	Player player;

	Learner() {}
	~Learner() {}

	Move learningMinimax(int max_d , double max_t );
	double learningMaxValue(double alpha , double beta , int cutoff_d , int cur_d ,  double tl , Player& p);
	double learningMinValue(double alpha , double beta , int cutoff_d , int cur_d ,  double tl , Player& p);
	void play(); //Calls the player's playing function.

	double read_coeff();
	double write_coeff();
	double adjustCoeff(double expectation , double reality);
}
#endif