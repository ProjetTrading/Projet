#ifndef MSG_H
#define MSG_H
#include <unistd.h>
#include <string>
#include <vector>

#define SEP '|'
#define EQU '='

class Msg
{
    private: 
		std::vector<std::string> vTags; /* vecteur de Tags du message */
    public:
		/* Enumeration des tags */
		/*enum enTags { Account=1, BeginSeqNo=7, BeginString=8, BodyLength=9, CheckSum=10, ClOrdID=11, Commission=12, CommType=13, CumQty=14, 
		Currency=15, EndSeqNo=16, ExecID=17, IOIID=23, IOIQltyInd=25, IOIRefID=26, IOIQty=27, IOITransType=28, MsgSeqNum=34, MsgType=35, 
		OrderID=37, OrderQty=38, PossDupFlag=43, Price=44, SecurityID=48, SenderCompID=49, SenderSubID=50, SendingTime=52, Quantity=53, 
		Symbol=55, Text=58, TransactTime=60, FutSettDate=64, QuoteID=117, QuoteReqID=131, BidPx=132, OfferPx=133, BidSize=134, OfferSize=135, 
		ExecType=150, LASTTAG=ExecType}; 
		enum enTags : int { Account, BeginSeqNo, BeginString, BodyLength, CheckSum, ClOrdID, Commission, CommType, CumQty, 
		Currency, EndSeqNo, ExecID, IOIID, IOIQltyInd, IOIRefID, IOIQty, IOITransType, MsgSeqNum, MsgType, 
		OrderID, OrderQty, PossDupFlag, Price, SecurityID, SenderCompID, SenderSubID, SendingTime, Quantity, 
		Symbol, Text, TransactTime, FutSettDate, QuoteID, QuoteReqID, BidPx, OfferPx, BidSize, OfferSize};
		*/
		typedef int enTags;
		struct {
			enTags Account;
			enTags BeginSeqNo;
			enTags BeginString;
			enTags BodyLength;
			enTags CheckSum;
			enTags ClOrdID;
			enTags Commission;
			enTags CommType;
			enTags CumQty;
			enTags Currency;
			enTags EndSeqNo;
			enTags ExecID;
			enTags IOIID;
			enTags IOIQltyInd;
			enTags IOIRefID;
			enTags IOIQty;
			enTags IOITransType;
			enTags MsgSeqNum;
			enTags MsgType;
			enTags OrderID;
			enTags OrderQty;
			enTags PossDupFlag;
			enTags Price;
			enTags SecurityID;
			enTags SenderCompID;
			enTags SenderSubID;
			enTags SendingTime;
			enTags Quantity;
			enTags Symbol;
			enTags Text;
			enTags TransactTime;
			enTags FutSettDate;
			enTags QuoteID;
			enTags QuoteReqID;
			enTags BidPx;
			enTags OfferPx;
			enTags BidSize;
			enTags OfferSize;
		} tagName;
		//enTags tagName; 
		
		/* Constructeur par défaut */
        Msg();
		/* Constructeur, remplissage de la liste de Tags à partir du par. */
        Msg(const std::string &);      
        /* Destructeur */
        ~Msg();
        /* Affectation de l'enum pour l'associer au vecteur */
        void defineEnum(int);
        /*****************************
         *         Accesseur         *
		 *****************************/
        std::string getSenderCompID();
        //std::string getTargetCompID();
		std::string getMsgType();
        /* Retourne la valeur du tag souhaité */
		std::string getTag(int);
        /*****************************
         *        Modificateur       *
         *****************************/
         // Si n'existe pas, alors il sera créer !
        void setSenderCompID(std::string str);
        //void setTargetCompID(std::string str);
        
        /* Retourne true si Logon accepte, false sinon */
        bool accLogon();
        /* Retourne true si QuoteRequest accepte, false sinon */
        bool accQuoteRequest();
        /* Retourne true si QuoteRequest accepte, false sinon */
        bool accSingleQuote();
		/* Retounre la liste de Tags sous forme de chaine de caracteres */
		std::string toString();
};

#endif
