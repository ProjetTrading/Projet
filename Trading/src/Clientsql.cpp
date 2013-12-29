/**
  *
  * Pour compiler : g++ Clientsql.cpp -o Clientsql -lsqlite3
  *
  */

#include <iostream>
#include <sqlite3.h>

using namespace std;

int main()
{
    sqlite3 *db;
    if (sqlite3_open("labase.db", &db) == SQLITE_OK)   // labase.db a remplacer par notre BD
        cout << "Ouverture de la BD avec succès\n";
    else
        cout << "Erreur lors de l'ouverture de la BD\n";

    sqlite3_close(db);
    return 0;
} 
