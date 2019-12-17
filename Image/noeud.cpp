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

/**
 * Poids maximal entre deux noeuds
 * @param otherNode [Noeud] l'autre noeud
 * @return valeur max entre deux noeuds
 */

//Opération sur la liste d'adjascence
void Noeud::ajouterUnNoeud(Noeud nouveauNoeud){
    adjascences.insert(end(adjascences), nouveauNoeud);
}

void Noeud::supprimerUnNoeud(Noeud noeudASupprimer){
    for (unsigned int ind = 0; ind < adjascences.size();ind++){
        if(noeudASupprimer.i == adjascences[ind].i && noeudASupprimer.j == adjascences[ind].j){
            adjascences.erase(adjascences.begin() + ind);
        }
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

int Noeud::getArcWeight(Noeud otherNode){
    int nodeType = otherNode.getNodeType();
    int value;
    if (nodeType == START)
    {
        value = -1 * exp((255 - otherNode.getValue()) / (255));
        return value;
    }else if(nodeType == END){
        value = -1 * log((otherNode.getValue()) / (255));
        return value;
    }else{
    switch (nodeType)
    {
        case START:
            value = -1 * exp((255 - value) / (255));
            return value;
        case MIDDLE:
            value = exp(-1*(pow(value-otherNode.getValue(),2)/(pow(BRUIT,2))));
            return value;
        case END:
            value = -1 * log((value) / (255));
            return value;
        
        default:
            cerr << "Erreur dans le calcul" << endl;
            return -1;
            break;
        }
    }
}

int Noeud::getNodeType(){
    return typeNode;
}

Noeud::~Noeud(){
    cout << "Suppression du noeud" << endl;
}
           
int Noeud::getMaxWeight(Noeud noeud){
    return (noeud.getValue() - valeur);
}

bool Noeud::operator==(const Noeud first){
    return true;
}

void Noeud::setMarkedStatus(bool newMarkedStatus){
    exploredStatus = newMarkedStatus;
}

vector<Noeud> Noeud::getSuccesseurs(){
    return adjascences;
}

bool Noeud::isMarked(){
    return exploredStatus;
}

vector<Noeud> Noeud::getPredecesseurs(){
    vector<Noeud> predecesseurs = vector<Noeud>();
    return vector<Noeud>();
}