#ifndef MSG_H
#define MSG_H
#include <map>
#include <string>

#define SEP '|' // '^' possible
#define EQU '='

class Msg
{
    private: 
        std::map<int, std::string> mpTags; /* liste des Tags du message */
    public:
		/* constructeur, remplissage de la liste de Tags à partir du par. */
        Msg(const std::string&); 
        /* destructeur */
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
