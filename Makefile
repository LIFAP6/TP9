# LIFAP6 - Automne 2017 - R. Chaine
main.ex : main.o pgm.o noeud.o arc.o
# L'executable main.ex doit être remis à jour si certains des fichiers 
# main.o liste.o et element.o sont plus rêcents
	g++ -g main.o pgm.o noeud.o arc.o
main.o : main.cpp Image/pgm.h Image/noeud.h
	g++ -std=c++11 -Wall -ansi -pedantic -c main.cpp

pgm.o : Image/pgm.h Image/pgm.cpp
	g++ -Wall -c Image/pgm.cpp

arc.o : Image/arc.h Image/arc.cpp
	g++ -Wall -c Image/arc.cpp

noeud.o : Image/noeud.cpp Image/noeud.h
	g++ -Wall -c Image/noeud.cpp