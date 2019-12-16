#include <iostream>
#include <vector>
#include "noeud.h"
#include "arc.h"
using namespace std;
#ifndef PGMIMAGE
#define PGMIMAGE
    class PGMImage{
        private:
            vector<Noeud> pgmArray;
            int numCol;
            int numRow;
            int maxIntensity;
            int imageBruit;

            //Ford-Fulkerson
            vector<Noeud> rechercheChaineAmeliorante(vector<Noeud> &pgmImage, vector<Arc> &listePredecesseur, vector<Arc> &listeSuccesseur);
            int calculFlotResiduel(vector<Noeud> &chaineAmeliorante);

        public:
            //Constructeur
            PGMImage();
            PGMImage(string filePath);

            //Destructeur
            ~PGMImage();

            //Surcharge d'opérateur
            PGMImage &operator=(const PGMImage &node);
            //ostream &operator<<(std::ostream &os);

            //Import/export de l'image
            void loadImage(string filePath);
            void saveTo(string filePath);

            //Accès à un élément
            int getElementNord(int i, int j);
            int getElementSud(int i, int j);
            int getElementOuest(int i, int j);
            int getElementEst(int i, int j);

            //Modification de l'intensité d'un noeud
            void updateNoeud(int i, int j, int value);

            //Affichage
            void displayImage();

            //Algorithme Ford-Fulkerson
            vector<Noeud> fordFulkerson();
    };
#endif