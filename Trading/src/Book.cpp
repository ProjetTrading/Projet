#include <iostream>
#include <stdio.h>
#include <string>
#include "../include/Book.h"

/* Constructeur */
Book::Book(std::string symbol){
	this->symbol=symbol;
	int i;
	for(i=0;i<SIZE;i++){
		bid[i].value=0.0;
		bid[i].size=0;
		offer[i].value=0.0;
		offer[i].size=0;
	}
}
/* Constructeur par défaut*/
Book::Book(){
	this->symbol="unknown";
	int i;
	for(i=0;i<SIZE;i++){
		bid[i].value=0.0;
		bid[i].size=0;
		offer[i].value=0.0;
		offer[i].size=0;
	}
}

/* Destructeur */
Book::~Book() {
	// Suppressions de donnees
}

/* Affichage du Book */
void Book::display(){
	//std::cout << std::string( 50, '\n' );
	std::cout << "\n\t\t--------------" << symbol << "--------------\n\t\t|\tBID\t|\tOFFER\t|\t\t\n";
	std::cout << "\t\t|\t" << bid[0].value << "\t|\t" << offer[0].value << "\t|\t\t\n";
	std::cout << "------------------------------" << symbol << "------------------------------\n";
	std::cout << "|\tQty\t|\tBid\t|\tOffer\t|\tQty\t|\n";
	for(int i=0;i<SIZE;i++){
		std::cout << "|\t" << bid[i].size <<"\t|\t"<< bid[i].value <<"\t|\t"<< offer[i].value << "\t|\t" << offer[i].size << "\t|\n";
	}
}

/* Insertion d'un bid dans un tri décroissant */
void Book::insertBid(int size, float bi){
	int i,j;
	for(i=0;i<SIZE;i++){
		if(bi>=bid[i].value){
			for(j=SIZE-1;j>i;j--){
				bid[j]=bid[j-1];
			}
		bid[i].value = bi;
		bid[i].size = size;
		break;
		}
	}
}

/* Insertion d'une offer dans un tri croissant */
void Book::insertOffer(int size, float off){
	int i,j;
	for(i=0;i<SIZE;i++){
		if(off>=offer[i].value){
			for(j=SIZE-1;j>i;j--){
				offer[j]= offer[j-1];
			}
		offer[i].value =off;
		offer[i].size = size;
		break;
		}
	}
}

/* Retourne le symbole */
std::string Book::getSymbol(){
	return this->symbol;
}

