/* Compilation: 	
 * 						g++ -o Client Client.cpp Msg.cpp Book.cpp
 * Execution -> Sous 1 terminal different:	
 * 			Client: 	./Client localhost
 * 
 * 	Message en entrée: 8=FIX.4.2|9=0087|35=S|34=0|49=ISTY_TRADING_SYTEM|56=EXCHANGE_A|52=20131110-16:46:24|98=0|108=30|141=Y|10=183
 * 8=FIX.4.2|9=315|35=S|34=1|49=EXCHANGE_A|56=ISTY_TRADING_SYTEM|52=20131110-16:46:27|117=123|131=1|55=INTEL|133=105|135=10000|132=100|134=10000|60=20131110-16:46:27|64=20131113|10=088|
 * 		Sans "|" a la fin
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
#include "../include/Book.h"
#include "../include/Client.h"

void error(const char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
	int sockfd, portno, numMsg, nbBook=0, indBook;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[1024];
	
	/* Verification du nombre d'arguments */
	if (argc < 2) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
	
	/* Saisie et creation du premier message client */
	printf("Please enter the message: ");
    bzero(buffer,1024);
	fgets(buffer,1024,stdin);
	std::string fix(buffer);
	Msg *msg[MAXMSG];
	msg[0] = new Msg(fix); // ->Creer un destructeur
	
	/* Envoi du message sur le bon port */
	if (msg[0]->getMsgType() == "S"){
		portno = 20001;
	}
	if (msg[0]->getMsgType() == "D"){
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
    
	write(sockfd,buffer,strlen(buffer));
	numMsg=1;
    Book *book[MAXBOOK];
	
	/* Ecoute le serveur */
	while(numMsg<MAXMSG) {
		bzero(buffer, 1024);
		read(sockfd, buffer, 1024);
		printf("%s\n", buffer);
		/* Ligne recu = Creation d'un nouveau message */
		msg[numMsg] = new Msg(buffer);
		/* Construction du book */
		int numSymbol=msg[numMsg]->tagName.Symbol;
		int numMsgType=msg[numMsg]->tagName.MsgType;
		/* Si le message possede un type et un symbole */
		printf("numMsgType:%d, numSymbol: %d\n", numMsgType,numSymbol);
		if(numMsgType!=0 && numSymbol!=0){
			indBook=0;
			int numBidSize=msg[numMsg]->tagName.BidSize;
			int numBidPx=msg[numMsg]->tagName.BidPx;
			int numOfferSize=msg[numMsg]->tagName.OfferSize;
			int numOfferPx=msg[numMsg]->tagName.OfferPx;
			std::string valSymbol= msg[numMsg]->getTag(msg[numMsg]->tagName.Symbol);
			if(numBidSize!=0 && numBidPx!=0){
				while(indBook<nbBook && ( book[indBook]->getSymbol().compare(valSymbol) != 0) ){
					indBook++;
				}
				if(indBook<nbBook && indBook<MAXBOOK){
					book[indBook] = new Book(valSymbol);
					nbBook++;
				}
				std::string valBidSize= msg[numMsg]->getTag(msg[numMsg]->tagName.BidSize);
				std::string valBidPx= msg[numMsg]->getTag(msg[numMsg]->tagName.BidPx);
				//int valBid = atoi(valBidSize.c_str());
				book[indBook]->insertBid(atoi(valBidSize.c_str()),atoi(valBidPx.c_str()));
				book[indBook]->display();
			}else if(numOfferSize!=0 && numOfferPx!=0){
				while(indBook<nbBook && ( book[indBook]->getSymbol().compare(valSymbol) != 0) ){ 
					indBook++;
				}
				if(indBook<nbBook && indBook<MAXBOOK){
					book[indBook] = new Book(valSymbol);
					nbBook++;
				}
				std::string valOfferSize= msg[numMsg]->getTag(msg[numMsg]->tagName.OfferSize);
				std::string valOfferPx= msg[numMsg]->getTag(msg[numMsg]->tagName.OfferPx);
				book[indBook]->insertBid(atoi(valOfferSize.c_str()),atoi(valOfferPx.c_str()));
				book[indBook]->display();
			}
		}
		numMsg++;
		
   	}
    
   	close(sockfd);
    	return 0;
}
