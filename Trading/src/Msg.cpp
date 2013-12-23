#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream> // pour std::istringstream

#include "../include/Msg.h"

std::string Msg::getSenderCompID() {
	return vTags[SenderCompID];
}

void Msg::setSenderCompID(std::string str) {
	vTags[SenderCompID] = str;
}
/*
std::string Msg::getTargetCompID() {
	return vTags[TargetCompID];
}
void Msg::setTargetCompID(std::string str) {
	vTags[TargetCompID] = str;
}
*/

// Inutile donc a enlever car des booleens ont été definis pour les verifications
std::string Msg::getMsgType(){
	return vTags[MsgType];
}


std::string Msg::toString() {
	std::string str="|";
	/*std::map<int, std::string>::iterator im;
	im = mpTags.begin();
	
	for(im=mpTags.begin(); im != mpTags.end(); im++) {
		std::ostringstream oss;
		oss << (*im).first;
		if(im == mpTags.begin())
			str += "|";
		str += oss.str() + "=" + (*im).second + "|";
		
	}*/
	for(int i=0;i<vTags.size();++i) {
		std::ostringstream oss;
		oss << i;
		str += oss.str() + "=" + vTags[i] + "|";
	}  
	
	
	return str;
}

/* Constructeur */
Msg::Msg(const std::string& strMsg)
{
	std::string tmpTag, defTag[2];
	int i,numTag;
	/* Initialisation a 0 de LASTTAG éléments (valeur du dernier tag) pour le vecteur de tags */
	//vTags.resize(200);
	vTags.resize(LASTTAG,"null");
	/* Allocation de LASTTAG éléments (valeur du dernier tag) pour le vecteur de tags */
	//vTags.reserve(LASTTAG);
    std::istringstream ssMsg(strMsg);
    /* Tant qu'il reste des séparateurs */
    while (std::getline(ssMsg, tmpTag, SEP)) {
		std::istringstream ssTag(tmpTag);
		i=0;
		/* Séparation du numéro du tag et de sa valeur */
		while (std::getline(ssTag, defTag[i], EQU)) {
			i++;
		}
		if(i!=2){
			std::cout << "Erreur: Orthographe du Tag";// Traiter l'erreur
		}
		/* Cast en int du numero de tag */
		std::istringstream ssNumTag(defTag[0]);
		ssNumTag >> numTag;
		vTags[numTag] = defTag[1];
    }
	if(vTags[MsgType]=="null"){
		std::cout << "Erreur: Vecteur -> MsgType manquant";// Traiter l'erreur
	}
}

/* destruction des objets dans l'ordre inverse de creation*/
Msg::~Msg()
{
}
// A REMPLACER PAR VECTOR
/* retourne true si Logon accepte, false sinon */
bool Msg::accLogon()
{	
	bool acc=false;
	if(vTags[35]=="A"){// type de message est Logon
		/*if(nomClient="AAA"){ acc=true;}*/ // Nom du client est correct
		acc=true;
	}
	return acc;
}

/* retourne true si Quote Request accepte, false sinon */
bool Msg::accQuoteRequest()
{
	bool acc=false;
	if(vTags[35]=="R"){// type de message est Quote Request
		// et ...
		acc=true;
	}
	return acc;
}

/* retourne true si Single Quote accepte, false sinon */
bool Msg::accSingleQuote()
{	
	bool acc=false;
	if(vTags[35]=="S"){//type de message est Single Quote)
		// et ...
		acc=true;
	}
	return acc;
}

