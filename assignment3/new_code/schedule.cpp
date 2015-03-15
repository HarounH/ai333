#ifndef SCHEDULE_CPP
#define SCHEDULE_CPP
/* How much time should i devote to each move? 
	Lets say I devote time_schedule[i] to the i-th plie.

	\math \from_0_\to_inf_ SUM(time_schedule[i]) = 2*total_time. Time taken by me and the opponent.
*/
#define TIME_EARLY 8
#define TIME_MID 16
#define TIME_FACTOR 10

double Player::get_time_schedule() {
	//I should return a small number initially.
	if ( plies< TIME_EARLY ) { //first 8 plies.
		return ((remaining_time>1.0)?(1.0):(remaining_time/TIME_FACTOR)); //1 second
	} else if ( plies < TIME_MID ) {
		return (remaining_time>1.0)?(1.0):(remaining_time/TIME_FACTOR);
	}else {
		return (remaining_time/TIME_FACTOR); //GP that sums up to 10.
	}

}
#endif