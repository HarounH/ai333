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
#include <ctime>
#include "AIEngine.h"
#include "Game.h"
#include "Player.cpp"

using namespace std;
/* Complete the function below to print 1 integer which will be your next move 
   */
int N,M,K, time_left, player;





int main(int argc, char *argv[])
{
    srand (time(NULL));
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    char sendBuff[1025];
    struct sockaddr_in serv_addr; 

    if(argc != 3)
    {
        printf("\n Usage: %s <ip of server> <port no> \n",argv[0]);
        return 1;
    } 

    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2])); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    cout<<"Quoridor will start..."<<endl;

    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d %d %d %d %d", &player, &N, &M, &K, &time_left);


    cout<<"Player "<<player<<endl;
    cout<<"Time "<<time_left<<endl;
    cout<<"Board size "<<N<<"x"<<M<<" :"<<K<<endl;
    float TL;
    int om,oro,oc;
    int m,r,c;
	int d=3;
    char s[100];
	int x=1;
	
	GameState gs(N, M, K);
	BasePlayer b;
	AIEngine<BasePlayer> ai(b, player-1);
	int depth = 2;
    if(player == 1)
    {
        
        memset(sendBuff, '0', sizeof(sendBuff)); 
        string temp;
        Move mov = ai.minimax(gs, depth);
		gs.applyMove(mov);
		m = mov.choice;
		r = mov.pos.first+1;
		c = mov.pos.second+1;
		cout << "Move: " << m <<" "<<r<<" "<<c<<"\n";
        snprintf(sendBuff, sizeof(sendBuff), "%d %d %d", m, r , c);
        write(sockfd, sendBuff, strlen(sendBuff));

	memset(recvBuff, '0',sizeof(recvBuff));
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
        recvBuff[n] = 0;
        sscanf(recvBuff, "%f %d", &TL, &d);
	cout<<TL<<" "<<d<<endl;
	if(d==1)
	{
		cout<<"You win!! Yayee!! :D ";
		x=0;
	}
	else if(d==2)
	{
		cout<<"Loser :P ";
		x=0;
	}
    }

    while(x)
    {
        memset(recvBuff, '0',sizeof(recvBuff));
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
        recvBuff[n] = 0;
        sscanf(recvBuff, "%d %d %d %d", &om,&oro,&oc,&d);
	cout << om<<" "<<oro<<" "<<oc << " "<<d<<endl;
	    Move omov(om, oro-1, oc-1);
		gs.applyMove(omov);
    	if(d==1)
	{
		cout<<"You win!! Yayee!! :D ";
		break;
	}
	else if(d==2)
	{
		cout<<"Loser :P ";
		break;
	}
        memset(sendBuff, '0', sizeof(sendBuff)); 
        string temp;
        Move mov = ai.minimax(gs, depth);
		gs.applyMove(mov);
		m = mov.choice;
		r = mov.pos.first+1;
		c = mov.pos.second+1;
		cout << "Move: " << m <<" "<<r<<" "<<c<<"\n\n\n\n";
        snprintf(sendBuff, sizeof(sendBuff), "%d %d %d", m, r , c);
        write(sockfd, sendBuff, strlen(sendBuff));

	memset(recvBuff, '0',sizeof(recvBuff));
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
        recvBuff[n] = 0;
        sscanf(recvBuff, "%f %d", &TL, &d);//d=3 indicates game continues.. d=2 indicates lost game, d=1 means game won.
	cout<<TL<<" "<<d<<endl;
	if(d==1)
	{
		cout<<"You win!! Yayee!! :D ";
		break;
	}
	else if(d==2)
	{
		cout<<"Loser :P ";
		break;
	}
    }
    cout<<endl<<"The End"<<endl;
    return 0;
}
















