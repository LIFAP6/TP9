#include "noeud.h"
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;
//Constructeurs
/**
 * Constructeur par défaut
 */
Noeud::Noeud(){
    cout << "Constructeur par défaut d'un noeud" << endl;
}

/**
 * Constructeur par paramètre
 * @param x [int] indice abscisse
 * @param y [int] indice ordonnée
 * @param value [int] valeur de la coloration
 * @param typeNoeud [int] le type de noeud (Entrée, Sortie, Noeud au milieu)
 */
Noeud::Noeud(int x, int y, int value,int typeNoeud){
    i = x;
    j = y;
    valeur = value;
    typeNode = typeNoeud;
}

//Opération sur la liste d'adjascence
void Noeud::ajouterUnNoeud(Noeud nouveauNoeud){
    adjascences.insert(end(adjascences), nouveauNoeud);
}

void Noeud::supprimerUnNoeud(Noeud noeudASupprimer){
    if(find(adjascences.begin(), adjascences.end(), adjascences) != adjascences.end()){
        adjascences.erase(remove(adjascences.begin(),adjascences.end(),noeudASupprimer),adjascences.end());
    }else{
        cerr << "L'élément est absent de la liste d'adjascence!" << endl;
    }
}

Noeud& Noeud::getElement(int i){
    return adjascences.at(i);
}

//Getter

/**
 * Getter de la valeur
 */
int Noeud::getValue(){
    return valeur;
}

//Setter
/**
 * Setter de la valeur
 * 
 */
void Noeud::setValue(int newValue){
    valeur = newValue;
}

int Noeud::getArcWeight(int i){
    int nodeType = getElement(i).getNodeType();
    if(nodeType == START){
        int value = -1 * exp((255 - getElement(i).getValue()) / (255));
        return value;
    }else if(nodeType == END){
        int value = -1 * log((getElement(i).getValue()) / (255));
        return value;
    }else{
    switch (nodeType)
    {
        case START:
            int value = -1 * exp((255 - value) / (255));
            return value;
        case MIDDLE:
            int value = exp(-1*(pow(value-getElement(i).getValue(),2)/(pow(BRUIT,2))));
            return value;
        case END:
            int value = -1 * log((value) / (255));
            return value;
        
        default:
            cerr << "Erreur dans le calcul" << endl;
            return -1;
            break;
        }
    }
}