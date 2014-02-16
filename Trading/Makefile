CPP=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=Client Serveur

SRCDIR=src
HEADDIR=include
LIBDIR=Objet
BINDIR=bin

all: $(EXEC)


Client: bin/Client.o bin/Msg.o bin/Book.o
	$(CPP) -o $@ $^ $(LDFLAGS)

Serveur: bin/Serveur.o bin/Msg.o
	$(CPP) -o $@ $^ $(LDFLAGS)

bin/Client.o: src/Client.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)

bin/Serveur.o: src/Serveur.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)

bin/Msg.o: src/Msg.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)
	
bin/Book.o: src/Book.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)




#Permet de faire un clean même si un fichier clean existe
.PHONY: clean mrproper

clean:
	@rm -rf bin/*.o

mrproper: clean
	@rm -rf $(EXEC)
