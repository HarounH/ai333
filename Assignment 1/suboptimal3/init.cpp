#include <algorithm>
void init( MODE mode) {
	if (mode == INIT_APPEND_BACK) {
		//length init
		uniform_int_distribution<int> linit(minFinalLength , minFinalLength + ((maxFinalLength-minFinalLength)/k));
		length = linit(engine);
		dashpos.resize(k);
		for(int idx=0; idx < k; ++idx) {
			while( sequences[idx].size() < length ) {
				sequences[idx].push_back('-');
				dashpos[idx].push_back( seqLengths[idx] );
			}
		}
	}
	cost = evalCost();
	initcost = cost;
}
