double evalCost() {
	double ans=0.0;
	for(int idx1 = 0; idx1 < k ; ++idx1) {
		ans += cc*dashpos[idx1].size();
		for(int idx2 = 0; idx2 < k ; ++idx2) {
			for(int pos=0; pos<length; ++pos) {
				ans += mc[ charToIdx[ sequences[idx1][pos] ] ][ charToIdx[ sequences[idx2][pos] ] ];
			}
		}
	}
	return ans;
}

double evalCost_move(Move move) {
	//Given idx, given origDidx, newDidx.
	double dcost=0.0;
	//ASSERT : No cost for cc.
	for(int sidx=0; sidx<k; ++sidx) {
		if (sidx != move.idx) {
			double newcost = mc[ charToIdx[ sequences[move.idx][move.newDptr] ] ][ charToIdx[ sequences[sidx][move.origDptr] ] ]
			 				+ mc[ charToIdx[ sequences[move.idx][move.origDptr] ] ][ charToIdx[ sequences[sidx][move.newDptr] ] ];
			double oldcost = mc[ charToIdx[ sequences[move.idx][move.origDptr] ] ][ charToIdx[ sequences[sidx][move.origDptr] ] ] 
							+ mc[ charToIdx[ sequences[move.idx][move.newDptr] ] ][ charToIdx[ sequences[sidx][move.newDptr] ] ];
			dcost = newcost - oldcost;
		}
	}
	return dcost;
}