#include <iostream>

#include <stdlib.h>

//pour bzero
#include <strings.h>

#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "Msg.h"
#include "Serveur.h"

using namespace std;

Serveur::Serveur(int numeroPort) {

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &serveur_addr, sizeof(serveur_addr));
	port = numeroPort;
	serveur_addr.sin_family = AF_INET;
	serveur_addr.sin_addr.s_addr = INADDR_ANY;
	serveur_addr.sin_port = htons(port);
	bind(sock_fd, (struct sockaddr *) &serveur_addr, sizeof(serveur_addr));
	
}
Serveur::~Serveur() {
	close(newsock_fd);
	close(sock_fd);
}
void Serveur::server_on() {
	
	const char msg[512];
	string serverName("ISTY_TRADING_SYSTEM");
	taille_client = sizeof(client_addr);
	
	listen(sock_fd, 0);
	
 	newsock_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &taille_client);
 	
	if(fork() == 0) {//Premier fork sert à répondre à un message client
		
		while(1) {
			
			bzero(msg, 512);
			read(newsock_fd, msg, 4096);
			
			Msg fix(msg);
			fix.setTargetID(fix.getClientID());
			fix.setClientID(serverName);
			
			string msgSend = fix.reconstituerMsgFIX();
			
			write(newsock_fd, msgSend.c_str(), 512);
				
		}
	}
	else {//Deuxieme fork envoie toutes les secondes un messages au client
		while (1) {
			Msg fix(8, "FIX4.2", 9, "315", 35, "S", 34, "2", 49, "EXCHANGE_ISTY_TRADING");
			string msgSend = fix.reconstituerMsgFIX();
			write(newsock_fd, msgSend.c_str(), 512);
			
			//La certain paramètre du message FIX envoyé doivent changer comme par exemple 34=i, et i augmente de 1 a chq envoi avec des setX
			
		}
		
	}
	
	return;
}


int main(int argc, char **argv) {

	Serveur s(atoi(argv[1]));
	s.server_on();

	return 0;
}
