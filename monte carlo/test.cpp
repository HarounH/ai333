#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <iostream>
#include <cstdlib>
#include <queue>

#include <ctime>

using namespace std;
/* Complete the function below to print 1 integer which will be your next move 
   */
int N,M,K, time_left, player;
double timetaken_formove;
#include <fstream>
fstream logfile;

#include "form.cpp"
int exploredNode::node_count = 0;

using namespace std;
int main(int argc, char** argv) {
	State w;
	w.init(9,9,10,1);
	w.pos_present = make_pair(1,4);
	w.pos_other = make_pair(2,5);
	w.n_present_walls = 4;
	w.n_other_walls = 3;
	w.toggle_player();


	Move m(0,1,5);
	m.from = w.pos_present;
	cout << " before playing move, pos_present="; m.from.print();
	w.apply_move(m);
	w.print();
	w.unapply_move(m);
	w.print();
	return -1;	
}