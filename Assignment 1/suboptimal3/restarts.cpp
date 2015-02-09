#include <algorithm>
void randomRestart();
void lengthAveragedRestart();
void evalDelta_l();

void restart( MODE mode = RESTART_RANDOM) {
	if ( mode == RESTART_RANDOM ) {
		randomRestart();
	} else if ( mode == RESTART_MEANLENGTH ) {
		lengthAveragedRestart();
	}
	cost = evalCost();
}

void randomRestart() {
	//length init
	uniform_int_distribution<int> linit(minFinalLength , minFinalLength + ((maxFinalLength-minFinalLength)/k));
	length = linit(engine);
	//dash init
	uniform_int_distribution<int> dinit( 0 , length);
	for(int idx = 0; idx<k; ++idx) {
		//#############################################################################DELETION BEGIN
		for(int didx = dashpos[idx].size()-1 ; didx >= 0 ; --didx) {
			sequences[idx].erase( sequences[idx].begin() + ( dashpos[idx][didx]+didx) ); 
		}
		//Assert : All the strings are back to normal. - CHECKED.
		//#############################################################################DELETION END
		dashpos[idx].resize(0);
		//############################################################################# INSERTION BEGIN
		for(int didx = 0; didx < length - seqLengths[idx]; ++didx) {
			dashpos[idx].push_back( (dinit(engine)%(seqLengths[idx] + 1)) ); // Because the valuesa at dashpos[idx][didx] represent how many chracters before the didx'th dash.
		}
		//###########################################################################SORTING DASHPOS BEGIN
		sort(dashpos[idx].begin() , dashpos[idx].end());
		//###########################################################################SORTING DASHPOS END
		for(int didx = 0; didx< length - seqLengths[idx]; ++didx) {
			sequences[idx].insert( didx + dashpos[idx][didx], 1, '-' ); //Insert dashes in the appropriate locations
		}
		//############################################################################## INSERTION END
	}
}

int evalDelta_l( MODE mode = SCHEDULE_RANDOM) {
	int dl = 0;
	if(mode == SCHEDULE_RANDOM) {
		dl = length - minFinalLength;
	} else if ( mode == SCHEDULE_BYRESTARTS ) {
		//needs to be inversely proportional to nrestarts
		dl = (maxFinalLength-minFinalLength)/nrestarts ;
	}
	return dl;
}
void lengthAveragedRestart() {
	int delta_l = min( length - minFinalLength , evalDelta_l( SCHEDULE_RANDOM ) );
	uniform_int_distribution<int> linit( length - delta_l , length + delta_l );
	length = linit(engine);
	//dash init
	uniform_int_distribution<int> dinit( 0 , length);
	for(int idx = 0; idx<k; ++idx) {
		//#############################################################################DELETION
		for(int didx = dashpos[idx].size()-1 ; didx >= 0 ; --didx) {
			sequences[idx].erase( sequences[idx].begin() + ( dashpos[idx][didx]+didx) ); 
		}
		//Assert : All the strings are back to normal. - CHECKED.
		dashpos[idx].resize(0);
		//############################################################################# INSERTION
		for(int didx = 0; didx < length - seqLengths[idx]; ++didx) {
			dashpos[idx].push_back( dinit(engine)%(seqLengths[idx] + 1) ); // Because the valuesa at dashpos[idx][didx] represent how many chracters before the didx'th dash.
		}
		sort(dashpos[idx].begin() , dashpos[idx].end());
		for(int didx = 0; didx< length - seqLengths[idx]; ++didx) {
			sequences[idx].insert( didx + dashpos[idx][didx], 1, '-' ); //Insert dashes in the appropriate locations
		}
		//############################################################################## INSERTION COMPLETE
	}	
}