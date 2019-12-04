#include <vector>
using namespace std;
#ifndef NOEUD
#define NOEUD
    class Noeud{
        private:
            int i;
            int j;
            int valeur;
            vector<Noeud> adjascences;

        public:
            //Constructeur
            Noeud();
            Noeud(int i, int j, int valeur);

            //Destructeur

            void ajouterUnNoeud(Noeud nouveauNoeud);
            void supprimerUnNoeud(Noeud noeudASupprimer);
            vector<Noeud> getListeAdjascence();
    };
#endif