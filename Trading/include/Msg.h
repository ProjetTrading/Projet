#ifndef MSG_H
#define MSG_H


#define SEP '|' // '^' possible
#define EQU '='


enum {SenderCompID = 49, TargetCompID = 56, BeginString = 8, BodyLength = 9, MsgType = 35, MsgSeqNum = 34, SendingTime = 52, QuoteID = 117, QuoteReqID = 131, Symbol = 55, OfferPx = 133, BidPx = 132, OfferSize = 135, BidSize = 134, TransactTime = 60, FutSettDate = 64, CheckSum = 10};

class Msg
{
    private: 
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
        
        /*****************************
         *        Modificateur       *
         *****************************/
         // Si n'existe pas, alors il sera créer !
        void setSenderCompID(std::string str);
        void setTargetCompID(std::string str);
        
        ~Msg();
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

#endif // MSG_H
