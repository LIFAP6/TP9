#include <vector>
using namespace std;
#ifndef NOEUD
#define NOEUD
    #define START 0
    #define MIDDLE 1
    #define END 2
    #define ALPHA 125
    #define BRUIT 125
    class Noeud{
        private:
            int i;
            int j;
            int valeur;
            int typeNode;
            vector<Noeud> adjascences;

        public:
            //Constructeur
            Noeud();
            Noeud(int i, int j, int valeur,int typeNode);

            //Destructeur
            ~Noeud();

            //Opération sur le vecteur
            void ajouterUnNoeud(Noeud nouveauNoeud);
            void supprimerUnNoeud(Noeud noeudASupprimer);
            Noeud &getElement(int i);

            //Getter
            vector<Noeud> getListeAdjascence();
            int getValue();
            int getNodeType();

            //Setter
            void setValue(int newValue);
            int getArcWeight(int i);
            
    };
#endif