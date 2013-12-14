/* Compilation: 	g++ -o Client Client.cpp Msg.cpp
 * Execution -> Sous 1 terminal different:	
 * 				Client: 	./Client localhost
 * 
 * 				Message en entrée: 8=FIX.4.2|9=0087|35=S|34=0|49=ISTY_TRADING_SYTEM|56=EXCHANGE_A|52=20131110-16:46:24|98=0|108=30|141=Y|10=183
 * 				Pas de "|" a la fin car erreur sinon
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "../include/Msg.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	char buffer[1024];

	if (argc < 2) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}

	printf("Please enter the message: ");
    	bzero(buffer,1024);
	fgets(buffer,1024,stdin);

	std::string fix(buffer);
	Msg fix2(fix);
	
	if (fix2.getMsgType() == "S"){
		portno = 20001;
	}

	if (fix2.getMsgType() == "D"){
		portno = 20002;
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
	(char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
	serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
	//printf("Please enter the message: ");
    //bzero(buffer,1024);
    	
    	write(sockfd,buffer,strlen(buffer));
   
    	while(1) {
    	 	bzero(buffer, 1024);
   		read(sockfd, buffer, 1024);
   		printf("%s\n", buffer);
   	}
    
   	close(sockfd);
    	return 0;
}
