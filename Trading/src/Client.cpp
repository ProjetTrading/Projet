/* Compilation: 	
 * 						g++ -o Client Client.cpp Msg.cpp Book.cpp
 * Execution -> Sous 1 terminal different:	
 * 			Client: 	./Client localhost
 * 
 * 	Message en entrée: 	8=FIX.4.2|9=0087|35=A|34=0|49=ISTY_TRADING_SYTEM|56=EXCHANGE_A|52=20131110-16:46:24|98=0|108=30|141=Y|10=183
 * 						Sans "|" a la fin
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
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

/* Retourne l'indice du book si le book existe pour un symbole donné, sinon -1 */
int bookIndice(Book *book[], int nbBook, std::string msgSymbol){
	int indBook=0;
	int bookExist=-1;
	while(indBook<nbBook && bookExist==-1){
		if(book[indBook]->getSymbol().compare(msgSymbol) != 0){
			indBook++;
		}else{
			bookExist=indBook;
		}
	}
	return bookExist;
}

int main(int argc, char *argv[]){
	int sockfd, portno, numMsg=0, nbBook=0, bookInd=0;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[1024];
	Book *book[MAXBOOK];
	Msg *msg[MAXMSG];
	
	/* Verification du nombre d'arguments */
	if (argc < 2) {
		error("ERROR: argc < 2 -> usage: argv[0] hostname port\n");
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR: opening socket -> socket() function\n");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		error("ERROR: no such host -> gethostbyname() function\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr)); //memset ?
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	
	/* Affichage et creation du premier message client */
    bzero(buffer, 1024);
    std::strcpy(buffer, "8=FIX.4.2|9=0087|35=A|34=0|49=ISTY_TRADING_SYTEM|56=EXCHANGE_A|52=20131110-16:46:24|98=0|108=30|141=Y|10=183");
    std::cout << "Entrée: \n<---" << buffer << "--->\n";
	msg[numMsg] = new Msg(buffer);
	serv_addr.sin_port = htons(20001);
	/* Test de connexion */
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
		error("ERROR: connection -> connect() function\n");
	}
    else{
		write(sockfd,buffer,strlen(buffer));
	}
	
	
	
	/* Ecoute le serveur */
	while(numMsg<MAXMSG) {
		numMsg++; // numMsg=1 apres le premier message
		bzero(buffer, 1024);
		read(sockfd, buffer, 1024);
		std::cout << buffer <<"\n";
		/* Ligne recu = Creation d'un nouveau message */
		msg[numMsg] = new Msg(buffer);
		
		/* ----------------------------------ENVOI DU MESSAGE SUR LE BON PORT ----------------------------------*/
		if (msg[numMsg]->getMsgType() != "D"){
			portno = 20001;
		}else{
			portno = 20002;
		}
		serv_addr.sin_port = htons(portno);
		write(sockfd,buffer,strlen(buffer));
		
		/* ---------------------------------------CONSTRUCTION DU BOOK--------------------------------------- */
		int numSymbol=msg[numMsg]->tagName.Symbol;
		int numMsgType=msg[numMsg]->tagName.MsgType;
		//std::cout << "numMsgType: " << numMsgType << ", numSymbol: " << numSymbol << " \n"; //Affichage de test
		/* Si le message possede un type et un symbole */
		if(numMsgType!=-1 && numSymbol!=-1){
			//std::cout << "Msg OK\n";
			int numBidSize=msg[numMsg]->tagName.BidSize;
			int numBidPx=msg[numMsg]->tagName.BidPx;
			int numOfferSize=msg[numMsg]->tagName.OfferSize;
			int numOfferPx=msg[numMsg]->tagName.OfferPx;
			std::string valSymbol= msg[numMsg]->getTag(msg[numMsg]->tagName.Symbol);
			if(numBidSize!=-1 && numBidPx!=-1){
				//std::cout << "Bid donné\n";
				bookInd=bookIndice(book, nbBook, valSymbol);
				/* Creation du book s'il n'existe pas */
				if(bookInd==-1 && nbBook<MAXBOOK){
					bookInd=nbBook;
					book[bookInd] = new Book(valSymbol);
					nbBook++; // augmentation du nombre de book
				}
				std::string valBidSize= msg[numMsg]->getTag(msg[numMsg]->tagName.BidSize);
				std::string valBidPx= msg[numMsg]->getTag(msg[numMsg]->tagName.BidPx);
				book[bookInd]->insertBid(atoi(valBidSize.c_str()),atoi(valBidPx.c_str()));
				book[bookInd]->display();
			}
			if(numOfferSize!=-1 && numOfferPx!=-1){
				//std::cout << "Offer donné\n";
				bookInd=bookIndice(book, nbBook, valSymbol);
				/* Creation du book s'il n'existe pas */
				if(bookInd==-1 && nbBook<MAXBOOK){
					bookInd=nbBook;
					book[bookInd] = new Book(valSymbol);
					nbBook++; // augmentation du nombre de book
				}
				std::string valOfferSize= msg[numMsg]->getTag(msg[numMsg]->tagName.OfferSize);
				std::string valOfferPx= msg[numMsg]->getTag(msg[numMsg]->tagName.OfferPx);
				/* Insertion des données de l'offre dans le book */
				book[bookInd]->insertOffer(atoi(valOfferSize.c_str()),atoi(valOfferPx.c_str()));
				book[bookInd]->display();
			}
		}
		numMsg++;
		/* ---------------------------------------FIN CONSTRUCTION DU BOOK--------------------------------------- */
   	}
    
   	close(sockfd);
    	return 0;
}
