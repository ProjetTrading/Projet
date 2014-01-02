#ifndef SERVEUR_H
#define SERVEUR_H
#include <unistd.h>
#include <string>

class Serveur {
	private :
		int sock_fd, newsock_fd, port;
		struct sockaddr_in serveur_addr, client_addr;
		socklen_t taille_client;
		
	public :
		/* Constructeur */
		Serveur(int port);
		/* Destructeur */
		~Serveur();
		/* Demarrage du serveur */
		void server_on();
};



#endif


