#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream> // pour std::istringstream
#include "../include/Msg.h"
#define MAXSYMBOL 20

/* Modification de l'envoyeur */
void Msg::setSenderCompID(std::string str) {
	vTags[tagName.SenderCompID] = str;
}

/* Modification du destinataire */
void Msg::setTargetCompID(std::string str) {
	vTags[tagName.TargetCompID] = str;
}


/* Retourne le type de message */
std::string Msg::getMsgType(){
	return vTags[tagName.MsgType];
}

/* Retourne la valeur du tag souhaité */
std::string Msg::getTag(int numTag){
	if ((unsigned)numTag<vTags.size()) //cast de numTag pour eviter warning de comparaison
		return vTags[numTag];
	else return "error";
}

std::string Msg::toString() {
	std::string str="";
	for(unsigned int i=0;i<vTags.size();++i) {
		std::ostringstream oss;
		oss << i;
		str += oss.str() + "=" + vTags[i] + "|";
	}
	return str;
}

/* Constructeur */
Msg::Msg(const std::string& strMsg){
	initEnum(); //initialise tous les champs de l'enum
	std::string tmpTag, defTag[2];
	int i,numTag;
    std::istringstream ssMsg(strMsg);
    /* Tant qu'il reste des séparateurs */
    while (std::getline(ssMsg, tmpTag, SEP)) {
		std::istringstream ssTag(tmpTag);
		i=0,numTag=0;
		/* Séparation du numéro du tag et de sa valeur */
		while (std::getline(ssTag, defTag[i], EQU)) {
			i++;
		}
		if(i!=2){
			std::cerr << "Erreur: Orthographe du Tag\n";// Traiter l'erreur
		}
		/* Cast en int du numero de tag */
		std::istringstream ssNumTag(defTag[0]);
		ssNumTag >> numTag;
		defineEnum(numTag); 
		vTags.push_back(defTag[1]);
    }
	if(vTags[tagName.MsgType]=="null"){
		std::cerr << "Erreur: Vecteur -> MsgType manquant";// Traiter l'erreur
	}
}

/* destruction des objets*/
Msg::~Msg(){
}

/* Initialise tous les champs de l'enum */
void Msg::initEnum(){
	//tagName={-1};
	int init=-1;
	tagName.Account=init;
	tagName.BeginSeqNo=init;
	tagName.BeginString=init;
	tagName.BodyLength=init;
	tagName.CheckSum=init;
	tagName.ClOrdID=init;
	tagName.Commission=init;
	tagName.CommType=init;
	tagName.CumQty=init;
	tagName.Currency=init;
	tagName.EndSeqNo=init;
	tagName.ExecID=init;
	tagName.IOIID=init;
	tagName.IOIQltyInd=init;
	tagName.IOIRefID=init;
	tagName.IOIQty=init;
	tagName.IOITransType=init;
	tagName.MsgSeqNum=init;
	tagName.MsgType=init;
	tagName.OrderID=init;
	tagName.OrderQty=init;
	tagName.PossDupFlag=init;
	tagName.Price=init;
	tagName.SecurityID=init;
	tagName.SenderCompID=init;
	tagName.SenderSubID=init;
	tagName.SendingTime=init;
	tagName.Quantity=init;
	tagName.Symbol=init;
	tagName.TargetCompID=init;
	tagName.Text=init;
	tagName.TransactTime=init;
	tagName.FutSettDate=init;
	tagName.QuoteID=init;
	tagName.QuoteReqID=init;
	tagName.BidPx=init;
	tagName.OfferPx=init;
	tagName.BidSize=init;
	tagName.OfferSize=init;
}

/* Affectation de l'enum pour l'associer au vecteur */
void Msg::defineEnum(int numTag){
	int last=numTag%10;
		switch(last){ //selon l'unité pour limiter le nombre de test, les autres tags ne sont pas géré
			case 0: 
				if(numTag==10){
					tagName.CheckSum=vTags.size();
				}else if(numTag==50){
					tagName.SenderSubID=vTags.size();
				}else if(numTag==60){
					tagName.TransactTime=vTags.size();
				}
				break;
			case 1: 
				if(numTag==1){
					tagName.Account=vTags.size();
				}else if(numTag==11){
					tagName.ClOrdID=vTags.size();
				}else if(numTag==131){
					tagName.QuoteReqID=vTags.size();
				}
				break;
			case 2: 
				if(numTag==12){
					tagName.Commission=vTags.size();
				}else if(numTag==52){
					tagName.SendingTime=vTags.size();
				}else if(numTag==132){
					tagName.BidPx=vTags.size();
				}
				break;
			case 3: 
				if(numTag==13){
					tagName.CommType=vTags.size();
				}else if(numTag==23){
					tagName.IOIID=vTags.size();
				}else if(numTag==43){
					tagName.PossDupFlag=vTags.size();
				}else if(numTag==53){
					tagName.Quantity=vTags.size();
				}else if(numTag==133){
					tagName.OfferPx=vTags.size();
				}
				break;
			case 4: 
				if(numTag==14){
					tagName.CumQty=vTags.size();
				}else if(numTag==34){
					tagName.MsgSeqNum=vTags.size();
				}else if(numTag==44){
					tagName.Price=vTags.size();
				}else if(numTag==64){
					tagName.FutSettDate=vTags.size();
				}else if(numTag==134){
					tagName.BidSize=vTags.size();
				}
				break;
			case 5: 
				if(numTag==35){ // Les plus courants en premier
					tagName.MsgType=vTags.size();
				}else if(numTag==55){
					tagName.Symbol=vTags.size();
				}else if(numTag==135){
					tagName.OfferSize=vTags.size();
				}else if(numTag==15){
					tagName.Currency=vTags.size();
				}else if(numTag==25){
					tagName.IOIQltyInd=vTags.size();
				}
				break;
			case 6: 
				if(numTag==16){
					tagName.EndSeqNo=vTags.size();
				}else if(numTag==26){
					tagName.IOIRefID=vTags.size();
				}else if(numTag==56){
					tagName.TargetCompID=vTags.size();
				}
				break;
			case 7: 
				if(numTag==7){
					tagName.BeginSeqNo=vTags.size();
				}else if(numTag==17){
					tagName.ExecID=vTags.size();
				}else if(numTag==27){
					tagName.IOIQty=vTags.size();
				}else if(numTag==37){
					tagName.OrderID=vTags.size();
				}else if(numTag==117){
					tagName.QuoteID=vTags.size();
				}
				break;
			case 8: 
				if(numTag==8){
					tagName.BeginString=vTags.size();
				}else if(numTag==28){
					tagName.IOITransType=vTags.size();
				}else if(numTag==38){
					tagName.OrderQty=vTags.size();
				}else if(numTag==48){
					tagName.SecurityID=vTags.size();
				}else if(numTag==58){
					tagName.Text=vTags.size();
				}
				break;
			case 9: 
				if(numTag==9){
					tagName.BodyLength=vTags.size();
				}else if(numTag==49){
					tagName.SenderCompID=vTags.size();
				}
				break;
			default: 
				std::cerr << "Erreur inconnue dans l'affectation d'enum";// Traiter l'erreur
				break; 
	}
}

/* retourne true si Logon accepte, false sinon */
bool Msg::accLogon(){
	bool acc=false;
	if(vTags[tagName.MsgType]=="A" && vTags[tagName.SenderCompID]=="ISTY_TRADING_SYTEM"){// type de message:Logon et client:ISTY_TRADING_SYTEM
		acc=true;
	}
	return acc;
}

/* retourne true si Quote Request accepte, false sinon */
bool Msg::accQuoteRequest(){
	bool acc=false;
	if(vTags[tagName.MsgType]=="R"){// type de message est Quote Request
		acc=true;
	}
	return acc;
}

/* retourne true si Single Quote accepte, false sinon */
bool Msg::accSingleQuote(){	
	bool acc=false;
	if(vTags[tagName.MsgType]=="S"){//type de message est Single Quote)
		acc=true;
	}
	return acc;
}

