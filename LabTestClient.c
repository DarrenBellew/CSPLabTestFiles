#include "unp.h"

int main(int argc, char **argv)  {
	int sockfd, n, count=0;
	char sendbuff[MAXLINE + 1],recvbuff[MAXLINE + 1], vote;
	struct sockaddr_in servaddr;
	
	if (argc != 3)
		err_quit("usage: ./celebvote <IPaddress> <Port Number>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	strcpy(sendbuff,""); //initialize outgoing buffer

	do  {
		printf("\nEnter the number of the celebrity you want to keep:\n");
		printf("\n1. Jorgie\n2. Kieron\n3. Ferne\n4. George\n5. Vicky\n");

		vote = getc(stdin); //retrieve vote from keyboard

		if(vote > '0' && vote < '8') //only accept valid number 
		(5)
		{
		sendbuff[count++] = vote;
		}

	} while(vote < '1' || vote > '7'); //out of range numbers are ignored

	sendbuff[count++] = '\r';
	sendbuff[count] = '\n';

	Write(sockfd, sendbuff, strlen(sendbuff));

	while ( (n = read(sockfd, recvbuff, MAXLINE)) > 0)
	{
		recvbuff[n] = 0; // null terminate rbuff prior to screen print

	 	if (fputs(recvbuff, stdout) == EOF) // screen print contents of read buffer
			err_sys("fputs error");

	 	if (strstr(recvbuff, "\r\n") > 0) 	{
	 		break;
	 	}
	}


 	if (n < 0)
 		err_sys("read error");
	exit(0);
}