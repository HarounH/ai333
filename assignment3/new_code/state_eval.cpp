#ifndef STATE_EVAL_CPP
#define STATE_EVAL_CPP

#include <time.h>
#define BIG_PATH 1000;
double nmt_cal(int diff)
{
	if (diff<=2) return 0;
	
	else return (diff-2)*(diff-2);
}

double State::evaluate()
{
	Move mov = causal_moves.top();
	if(mov.m!=0 && mov.eval!=-1 ) { //Return asap.
		return mov.eval;
	}
 
 	double b = causal_moves.top().my_shortest_path;							// my shortest path to goal
 	double c = causal_moves.top().op_shortest_path;							// opp shortest path to goal
 	if ( b==-1 ) {
 		b = shortest_path(mypn);
 		Move temp = causal_moves.top();
 		causal_moves.pop();
 		temp.my_shortest_path = b;
 		causal_moves.push(temp);
 		if (b==-1) {
 			b = BIG_PATH;
 		}
 	}
 	if ( c==-1) {
 		c = shortest_path(opn);
		Move temp = causal_moves.top();
		causal_moves.pop();
 		temp.my_shortest_path = c;
 		causal_moves.push(temp); 		if ( c==-1 ) {
 			c= BIG_PATH; //This ensures that once you've lost, you're just trying to minimize your path.
 		}
 	}
	double a = c-b;															// my shortest path - opp shortest path
//	cout << "----------\n"; cout << "b= " << b << " " << "c= " << c << " a= " << a << "\n"; pos_present.print(true) ; cout << endl ; pos_other.print(true) ; cout << endl;
	if (is_endgame()) { return 1000000; }
 	if (i_won()) { /*cout <<"eval: " << 100000<<endl; */return (100000 + a);}
 	if (i_lost()) {/*cout <<"eval: " << 100000<<endl;*/ return (-100000 + a);}

	double wc;

	if (plies<50) {
		wc = ((50-plies)/50)*((50-plies)/50)*((this->mypn==this->pn)?(this->n_present_walls):(this->n_other_walls));
	}	// only for the walls I used (wall_cost)
	else wc = 0.0;
	
	double nmt = ((this->mypn==this->pn)?(this->n_other_walls - this->n_present_walls):(this->n_present_walls-this->n_other_walls));	
	nmt = nmt_cal(nmt);
	// not more than three walls than oponent
		
 	double e=  a*abs(a) - 5*b + 3*wc - 3.5*nmt - causal_moves.size();
	Move temp = causal_moves.top();
	causal_moves.pop();
	temp.eval = e;
	causal_moves.push(temp);
	return e;
	// double ans = w.diff_shortest_path(*this);
	// return ans;
//	return (rand()%10) ;
	// if ( pn==1 ) {
	// 	return (pos_present.r - 1)*(rand()%100);
	// } else {
	// 	return (pos_present.r - N)*(-1.0)*(rand()%100);
	// }
}

#endif