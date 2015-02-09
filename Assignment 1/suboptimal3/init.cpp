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
	} else if ( mode == INIT_RANDOM ) {
		uniform_int_distribution<int> linit(minFinalLength , minFinalLength + ((maxFinalLength-minFinalLength)/k));
		length = linit(engine);
		//dash init
		dashpos.resize(k);
		uniform_int_distribution<int> dinit( 0 , length);
		for(int idx = 0; idx<k; ++idx) {
			dashpos[idx].resize(0);
			//############################################################################# INSERTION BEGIN
			for(int didx = 0; didx < (length - seqLengths[idx]) ; ++didx) {
				dashpos[idx].push_back( (dinit(engine)%(seqLengths[idx] + 1)) ); // Because the valuesa at dashpos[idx][didx] represent how many chracters before the didx'th dash.
			}
			//###########################################################################SORTING DASHPOS BEGIN
			sort(dashpos[idx].begin() , dashpos[idx].end());
			//###########################################################################SORTING DASHPOS END
			for(int didx = 0; didx< length - seqLengths[idx]; ++didx) {
				sequences[idx].insert( didx + dashpos[idx][didx] , 1, '-' ); //Insert dashes in the appropriate locations
			}
			//############################################################################## INSERTION END
		}
	}
	cost = evalCost();
	initcost = cost;
}
