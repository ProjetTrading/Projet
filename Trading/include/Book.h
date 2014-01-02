#ifndef BOOK_H
#define BOOK_H
#include <unistd.h>
#include <string>

#define SIZE 10

struct bidOffer {
	float value;
	int size;
};

class Book
{
    private: 
		/* Nom de la valeur, ex: INTEL*/
		std::string symbol;
		bidOffer bid[SIZE];
		bidOffer offer[SIZE];
    public:
		/* Constructeur avec un nom de symbole */
		Book(std::string);
		/* Constructeur par défaut */
        Book();
        /* Destructeur */
		~Book();
		/* Affichage du Book */
		void display();
		/* Insertion d'un bid dans un tri décroissant */
		void insertBid(int, float);
		/* Insertion d'une offer dans un tri croissant */
		void insertOffer(int, float);
		/* Retourne le symbole */
		std::string getSymbol();
};

#endif
