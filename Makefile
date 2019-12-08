# LIFAP6 - Automne 2017 - R. Chaine
main.ex : main.o pgm.o
# L'executable main.ex doit être remis à jour si certains des fichiers 
# main.o liste.o et element.o sont plus rêcents
	g++ -g main.o pgm.o
main.o : main.cpp Image/pgm.h
	g++ -Wall -ansi -pedantic -c main.cpp

pgm.o : Image/pgm.h Image/pgm.cpp Image/noeud.cpp Image/noeud.h
	g++ -Wall -c Image/pgm.cpp Image/noeud.h

noeud.o : Image/noeud.cpp Image/noeud.h
	g++ -Wall -c Image/noeud.h