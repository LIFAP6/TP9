#include "arc.h"
#include <iostream>
using namespace std;

/**
 * Constructeur par paramètre
 */
Arc::Arc(Noeud* _predecessor, Noeud* _successor, int _flowValue, int _flowCapacity){
    predecessor = _predecessor;
    successor = _successor;
    flowValue = _flowValue;
    flowCapacity = _flowCapacity;
}

/**
 * Destructeur
 */
Arc::~Arc(){
    cout << "Suppression de l'arc." << endl;
}

/**
 * Setter de la valeur de flot
 * @param newFlow nouvelle valeur du flot
 */
void Arc::incrementFlowValue(int newFlow){
    flowValue += newFlow;
}

/**
 * Setter de la capacity de flot
 * @param newFlow nouvelle capacité du flot
 */
void Arc::decrementFlowCapacity(int newFlow){
    if(newFlow>flowValue){
        flowValue = 0;
    }else{
        flowCapacity -= newFlow;
    }
}

/**
 * Vérifie si la valeur de flot ne peut être augmentée
 * @return true impossible d'ajouter plus
 * @return false possibilité d'ajouter plus
 */
bool Arc::fullFlow(){
    return flowCapacity == flowValue;
}