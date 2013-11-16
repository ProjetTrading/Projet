#ifndef SERVEUR_H
#define SERVEUR_H


class Serveur {
	private :
		int sock_fd, newsock_fd, port;
		struct sockaddr_in serveur_addr, client_addr;
		
	public :
		Serveur(int port);
		~Serveur();
		
		void server_on();
};



#endif


