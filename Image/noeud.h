#include <vector>
using namespace std;
    
#ifndef NOEUDHEADER
#define NOEUDHEADER
    #define START 0
    #define MIDDLE 1
    #define END 2
    #define ALPHA 125
    #define BRUIT 125
    #define NOTEXPLORED 0
    #define NOTFINISHEDEXPLORING 1
    #define FINISHEDEXPLORING 2
    class Noeud{
        private:
            int i;
            int j;
            int valeur;
            int typeNode;
            vector<Noeud> adjascences;
            bool exploredStatus;

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
            bool isMarked();

            //Setter
            void setValue(int newValue);
            int getArcWeight(int i);
            void setMarkedStatus(bool newStatus);

            //Autre
            int getMaxWeight(Noeud otherNoeud);
            vector<Noeud> getSuccesseurs();
            vector<Noeud> getPredecesseurs();

            //operator==
            bool operator==(const Noeud first);
    };
#endif