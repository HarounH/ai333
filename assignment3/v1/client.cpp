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



using namespace std;
/* Complete the function below to print 1 integer which will be your next move 
   */
int N,M,K, time_left, _player; 

#include "game_player.h"
#include "game_player.cpp"
Game_Player player;



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
    sscanf(recvBuff, "%d %d %d %d %d", &_player, &N, &M, &K, &time_left);


    cout<<"Player "<<_player<<endl;
    cout<<"Time "<<time_left<<endl;
    cout<<"Board size "<<N<<"x"<<M<<" :"<<K<<endl;
    
    float _time_left = time_left; //Neccessary because thats how the world rotates.
    player.init( N , M , K , _time_left ,  _player);
//$$$$$$$$$$$$$ GAME INITIALIZATION COMPLETE. 

    float TL; //Timetaken, maybe?
    int om,oro,oc; // Opponent move, Opponent row, Opponent column.
    int m,r,c; // Your Move , Your Row, Your column.
	int d=3; //Used for game state. 
    
    char s[100]; //Unused.
	int x=1; //Used for gamestate, but not really needed.

    if(_player == 1)
    {
        
        memset(sendBuff, '0', sizeof(sendBuff)); 
        string temp;

        player.output_move(m,r,c);
        //CHANGESMADE
        
        snprintf(sendBuff, sizeof(sendBuff), "%d %d %d", m, r , c);
        write(sockfd, sendBuff, strlen(sendBuff)); //sending move to server.

        memset(recvBuff, '0',sizeof(recvBuff));
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1); //What did i read? A confirmation?
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
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1); //Reads opponents next move from the server.
        recvBuff[n] = 0;
        
        sscanf(recvBuff, "%d %d %d %d", &om,&oro,&oc,&d);
        
        cout << om<<" "<<oro<<" "<<oc << " "<<d<<endl; //Opponent move, row and column.
    	
        //CHANGES MADE:
        player.update_state(om,oro,oc,d);


        if(d==1) {
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
	    
        player.output_move(m , r, c);
        
        snprintf(sendBuff, sizeof(sendBuff), "%d %d %d", m, r , c);
        write(sockfd, sendBuff, strlen(sendBuff)); //Write your move onto the server.

        memset(recvBuff, '0',sizeof(recvBuff));
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1); //Reads server's reply.
        
        recvBuff[n] = 0;
        sscanf(recvBuff, "%f %d", &TL, &d);//d=3 indicates game continues.. d=2 indicates lost game, d=1 means game won.
    	
        cout<<TL<<" "<<d<<endl;
    	if(d==1)
    	{
    		cout<<"You win!! Yayee!! :D ";
            x=0;
    		break;
    	}
    	else if(d==2)
    	{
    		cout<<"Loser :P ";
            x=0;
    		break;
    	}
    }

    cout<<endl<<"The End"<<endl;
    return 0;
}
















