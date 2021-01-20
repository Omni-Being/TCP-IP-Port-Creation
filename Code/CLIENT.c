
// Client

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>


void error(char *msg)
{
	perror(msg);
	exit(0);
}


int main(int argc, char *argv[])
{
	int sockfd,portno,n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];

	if(argc<3)
	{
		fprintf(stderr,"\nUsage %s host port.",argv[0]);
		exit(0);
	}

	portno=atoi(argv[2]);

	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd<0)
	{
		error("\nERROR! Opening socket.");
	}

	server=gethostbyname(argv[1]);

	if(server==NULL)
	{
		fprintf(stderr, "\nERROR! No such host found.");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port=htons(portno);

	if(connect(sockfd,&serv_addr,sizeof(serv_addr))<0)
	{
		error("\nERROR! Connection error.");
	}

	printf("\nEnter the message to be send :--  ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n=write(sockfd,buffer,strlen(buffer));
	if(n<0)
	{
		error("\nERROR! Writing to socket.");
	}

	printf("\nMessage successfully send.\n");
	return 0;
}
