#include <iostream>
#include <stdio.h>

using namespace std;

class Book {
    private:
    string provenance[10];
    int volume[10];
    float bid[10];
    float offer[10];

    public:
    Book(){
        for(int i=0;i<10;i++){
            provenance[i]="null";
            volume[i] = 0;
            bid[i]=0;
            offer[i]=0;
        }
    }

    void afficher_book(){
        printf("Provid\t|\tVolume\t|\tBid\t|\tOffer\t|\n");
        for(int i=0;i<10;i++){
            cout << provenance[i] <<"\t|\t"<< volume[i] <<"\t|\t"<< bid[i] <<"\t|\t"<< offer[i] <<"\t|\n";
        }
    }

    //Ajout d'un bid, cad que l'on insert en fonction du bid pour que le tableau soit trié de façon décroissante
    void ajouter_par_bid(string s, int v,float b,float o){
        int i,j;
        for(i=0;i<10;i++){
            if(b>=bid[i]){
                for(j=9;j>i;j--){
                    bid[j]=bid[j-1];
                    offer[j]= offer[j-1];
                    provenance[j]= provenance[j-1];
                    volume[j]= volume[j-1];
                }
            bid[i] = b;
            offer[i]=o;
            provenance[i]= s;
            volume[i]= v;
            break;
            }
        }
    }

    //Ajout d'un bid, cad que l'on insert en fonction de l'offre pour que le tableau soit trié de façon croisante
    void ajouter_par_offer(string s, int v,float b,float o){
        int i,j;
        for(i=0;i<10;i++){
            if(o>=offer[i]){
                for(j=9;j>i;j--){
                    bid[j]=bid[j-1];
                    offer[j]= offer[j-1];
                    provenance[j]= provenance[j-1];
                    volume[j]= volume[j-1];
                }
            bid[i] = b;
            offer[i]=o;
            provenance[i]= s;
            volume[i]= v;
            break;
            }
        }
    }
};

int main()
{
    Book mesBid, mesOffer;
    mesBid.ajouter_par_bid("ibm",4,1.0452,1.2654);
    mesBid.ajouter_par_bid("faceb",11,1.0689,1.9054);
    mesBid.afficher_book();

    mesOffer.ajouter_par_offer("ibm",4,1.0452,1.2654);
    mesOffer.ajouter_par_offer("faceb",11,1.0689,1.1054);
    mesOffer.afficher_book();
    return 0;
}
