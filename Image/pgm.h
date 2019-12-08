#include <iostream>
#include <vector>
#include "noeud.h"
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
    };
#endif