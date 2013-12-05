#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream> // pour std::istringstream

#include "../include/Msg.h"

std::string Msg::getSenderCompID() {
	return mpTags[SenderCompID];
}
void Msg::setSenderCompID(std::string str) {
	mpTags[SenderCompID] = str;
}

std::string Msg::getTargetCompID() {
	return mpTags[TargetCompID];
}
void Msg::setTargetCompID(std::string str) {
	mpTags[TargetCompID] = str;
}

std::string Msg::toString() {
	std::string str;
	std::map<int, std::string>::iterator im;
	im = mpTags.begin();
	
	for(im=mpTags.begin(); im != mpTags.end(); im++) {
		std::ostringstream oss;
		oss << (*im).first;
		if(im == mpTags.begin())
			str += "|";
		str += oss.str() + "=" + (*im).second + "|";
		
	}
	return str;
}
Msg::Msg(const std::string& strMsg)
{
	std::string tmpTag, defTag[2];
	int i,numTag;
	
    std::istringstream ssMsg(strMsg);
    while (std::getline(ssMsg, tmpTag, SEP)) {
		std::istringstream ssTag(tmpTag);
		i=0;
		while (std::getline(ssTag, defTag[i], EQU)) {
			i++;
		}
		if(i!=2){
			std::cout << "Erreur: Orthographe du Tag";// Traiter l'erreur
		}
		/* cast en int du numero de tag */
		std::istringstream ssNumTag(defTag[0]);
		ssNumTag >> numTag;
		mpTags[numTag] = defTag[1];
    }
	if(mpTags.empty()){
		std::cout << "Erreur: Map de Tags vide";// Traiter l'erreur
	}
}

/* destruction des objets dans l'ordre inverse de creation*/
Msg::~Msg()
{
}

/* retourne true si Logon accepte, false sinon */
bool Msg::accLogon()
{	
	bool acc=false;
	if(mpTags.find(35) == mpTags.end()){
		std::cout<<"Erreur: Type de message manquant"<<std::endl;// Traiter l'erreur
	}
	else if(mpTags[35]=="A"){// type de message est Logon
		/*if(nomClient="AAA"){ acc=true;}*/ // Nom du client est correct
		acc=true;
	}
	return acc;
}

/* retourne true si Quote Request accepte, false sinon */
bool Msg::accQuoteRequest()
{
	bool acc=false;
	if(mpTags.find(35) == mpTags.end()){
		std::cout<<"Erreur: Type de message manquant"<<std::endl;// Traiter l'erreur
	}
	else if(mpTags[35]=="R"){// type de message est Quote Request
		// et ...
		acc=true;
	}
	return acc;
}

/* retourne true si Single Quote accepte, false sinon */
bool Msg::accSingleQuote()
{	
	bool acc=false;
	if(mpTags.find(35) == mpTags.end()){
		std::cout<<"Erreur: Type de message manquant"<<std::endl;// Traiter l'erreur
	}
	else if(mpTags[35]=="S"){//type de message est Single Quote)
		// et ...
		acc=true;
	}
	return acc;
}

/* affiche la liste de Tags */
void Msg::displayTags(){
	std::map<int,std::string>::iterator pIt; // Pointeur iterateur
	for(pIt=mpTags.begin(); pIt!=mpTags.end(); pIt++){
		std::cout << (*pIt).first << ":" << (*pIt).second << std::endl;
	}
}

