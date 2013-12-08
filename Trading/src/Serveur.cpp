/* Compilation: 
 * 				Serveur: g++ -o Serveur Serveur.cpp Msg.cpp
 * Execution -> Sous 1 terminal different:	
 * 				Serveur: ./Serveur 20001
 */
#include <iostream>
#include <map>
//pour bzero
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include "../include/Msg.h"
#include "../include/Serveur.h"


Serveur::Serveur(int numeroPort) {

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &serveur_addr, sizeof(serveur_addr));
	port = numeroPort;
	serveur_addr.sin_family = AF_INET;
	serveur_addr.sin_addr.s_addr = INADDR_ANY;
	serveur_addr.sin_port = htons(port);
	bind(sock_fd, (struct sockaddr *) &serveur_addr, sizeof(serveur_addr));
	taille_client = sizeof(client_addr);
	
}
Serveur::~Serveur() {
	close(newsock_fd);
	close(sock_fd);
}
void Serveur::server_on() {
	
	char msg[1024];
	
	listen(sock_fd, 0);
	
 	newsock_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &taille_client);
 	
	if(fork() != 0) {//Premier fork sert à répondre à un message client
			
		bzero(msg, 1024);
		read(newsock_fd, msg, 1024);
		printf("Message reçu : %s\n", msg);
		
		std::string fix(msg), cpy;
		
		//je ne sais pas trop qu'
		Msg fix2(fix);
		cpy = fix2.getSenderCompID();
		fix2.setSenderCompID(fix2.getTargetCompID());
		fix2.setTargetCompID(cpy);
		
		write(newsock_fd, fix2.toString().c_str(), 1024);
				
		wait();
	}
	else { //Deuxieme fork envoie toutes les secondes un messages au client
		std::fstream fichier("fix_msg", std::ios::in);
		if(fichier) {
			
			std::string msg_fix_to_send;
			
			while(std::getline(fichier, msg_fix_to_send)) {
				sleep (1);
				write(newsock_fd, msg_fix_to_send.c_str(), 1024);
			}
			
			fichier.close();
		}
		else
			std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
			
	}

	
	return;
}


int main(int argc, char **argv) {

	Serveur s(atoi(argv[1]));
	s.server_on();

	return 0;
}
