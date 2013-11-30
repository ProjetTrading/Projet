#ifndef SERVEUR_H
#define SERVEUR_H


class Serveur {
	private :
		int sock_fd, newsock_fd, port;
		struct sockaddr_in serveur_addr, client_addr;
		socklen_t taille_client;
		
	public :
		Serveur(int port);
		~Serveur();
		
		void server_on();
};



#endif


