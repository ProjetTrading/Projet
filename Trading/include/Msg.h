#ifndef MSG_H
#define MSG_H
#include <unistd.h>
#include <string>
#include <map>
//#include <vector>

#define SEP '|' // '^' possible
#define EQU '='


enum Tags { Account=1, BeginSeqNo=7, BeginString=8, BodyLength=9, CheckSum=10, ClOrdID=11, Commission=12, CommType=13, CumQty=14, 
		Currency=15, EndSeqNo=16, ExecID=17, IOIID=23, IOIQltyInd=25, IOIRefID=26, IOIQty=27, IOITransType=28, MsgSeqNum=34, MsgType=35, 
		OrderID=37, OrderQty=38, PossDupFlag=43, Price=44, SecurityID=48, SenderCompID=49, SenderSubID=50, SendingTime=52, Quantity=53, Text=58 }; 

class Msg
{
    private: 
		//std::vector<std::int> vTags; /* vecteur de Tags du message */
        std::map<int, std::string> mpTags; /* liste des Tags du message */
    public:
		/* constructeur, remplissage de la liste de Tags à partir du par. */
        Msg(const std::string &); 
        /* destructeur */
        
        /*****************************
         *         Accesseur         *
		 *****************************/
        std::string getSenderCompID();
        std::string getTargetCompID();
	std::string getMsgType();
        
        /*****************************
         *        Modificateur       *
         *****************************/
         // Si n'existe pas, alors il sera créer !
        void setSenderCompID(std::string str);
        void setTargetCompID(std::string str);
        
        ~Msg();
        std::string toString();
        /* retourne true si Logon accepte, false sinon */
        bool accLogon();
        /* retourne true si QuoteRequest accepte, false sinon */
        bool accQuoteRequest();
        /* retourne true si QuoteRequest accepte, false sinon */
        bool accSingleQuote();
		/* affiche la liste de Tags */
		void displayTags();
		//std::map<int, std::string> getMpTags();
};

#endif
