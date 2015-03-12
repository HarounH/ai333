#ifndef EVAL_CPP
#define EVAL_CPP

#include <time.h>

double State::evaluate()
{
	return (rand()%100) ;
	if ( pn==1 ) {
		return (pos_present.r - 1)*(rand()%100);
	} else {
		return (pos_present.r - N)*(-1.0)*(rand()%100);
	}
}

#endif