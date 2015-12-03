//Darren Bellew | C13729611

#include "unp.h"
#include <stdio.h>
#include <string.h>
#define AMOUNT 5


int main(int argc, char **argv)  {
	char cmd[16];
	char path[64];
	char vers[16];
	char *celebs[AMOUNT] = {"Jorgie", "Kieron", "Ferne", "George", "Vicky"};
	int *votes[AMOUNT] = {0, 0, 0, 0, 0};


	int listenfd, connfd;
	struct sockaddr_in servaddr;

	char buff[MAXLINE+1], recvline[MAXLINE+1];


	if(argc != 2)  {
		err_quit("usage: ./server <port no.>");
	}

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	servaddr.sin_port = htons(atoi(argv[1]));

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	while(1)  {
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		int n;
		//because the client is sending a buff of size 3, with vote at [0]
		char inputBuff[3];
		int *tempInt[AMOUNT];
		char *sendBuff[AMOUNT+AMOUNT];


		while((n = read(connfd, recvline, MAXLINE)) > 0)  {

			recvline[n] = 0;
			if(fputs(recvline, stdout) == EOF)  {
				err_sys("fputs error");
			}
			if(strstr(recvline, "\r\n\r\n")>0)  {
				break;
			}
		}

		sscanf(recvline, "%s",inputBuff);
		//convert the character of the vote to an integer
		int i = inputBuff[0] - '0';
		votes[i]++;

		//prepare to send the list of celebs | votes
		i = 0;
		while(i < AMOUNT+AMOUNT){
			int temp = i / 2;
			//to seperate them nicely
			sendBuff[i++] = celebs[temp];
			sendBuff[i++] = (char) votes[temp];
		}

		Write(connfd, sendBuff, strlen(sendBuff));
		Close(connfd);
	}




}