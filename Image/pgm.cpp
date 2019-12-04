#include <iostream> // cout, cerr
#include <fstream>  // ifstream
#include <sstream>  // stringstream
#include <vector>
using namespace std;
#include <sys/stat.h>

#include "pgm.h"

/**
 * Constructeur par import du fichier pgm
 * @param filePath chemin du fichier
 */
PGMImage::PGMImage(string filePath){
    //Chargement de l'image
    cout << "Instance d'une image pgm à l'adresse : " << filePath << "." << endl;
    loadImage(filePath);
}

/**
 * Constructeur par défaut
 */
PGMImage::PGMImage(){
    cout << "Instance par défaut" << endl;
    numCol = 0;
    numRow = 0;
    maxIntensity = 0;
    pgmArray = std::vector<int>();
}

/**
 * Destructeur
 */
PGMImage::~PGMImage(){
    cout << "Destruction de l'image PGM" << endl;
}

/**
 * Surcharge de l'opérateur d'affectation
 * @param rawImage valeur de base 
 */
PGMImage& PGMImage::operator=(const PGMImage &rawImage){
    cout << "Opérateur d'affectation" << endl;
    numCol = rawImage.numCol;
    numRow = rawImage.numRow;
    maxIntensity = rawImage.maxIntensity;
    int newPgmArray[numRow * numCol];
    pgmArray = std::vector<int>();
    for (int i = 0; i < (numRow * numCol);i++){
        pgmArray[i] = rawImage.pgmArray[i];
    }
}

/**
 * Fonction d'affichage du graphe
 */
void PGMImage::displayImage(){
    cout << "Image pgm" << endl;
    cout << "Intensité maximale : " << maxIntensity << endl;
    cout << "Nombre de colonnes : "<< numCol << " et nombre de lignes :" << numRow << "." << endl;
    for (int i = 0; i < numRow ; i++){
        for(int j = 0 ; j<numCol ; j++){
            cout << pgmArray[i * numCol + j] << " ";
        }
        cout << endl;
    }
}

/**
 * Import du fichier
 * @param filePath le chemin du fichier
 */
void PGMImage::loadImage(string filePath)
{
    //Lecture du fichier
    ifstream infile(filePath);
    //Si celui-ci est introuvable
    if (infile.fail())
    {
        cerr << "Le fichier à l'adresse " << filePath << " est introuvable!" << endl;
    }
    //Sinon
    else
    {
        stringstream ss;
        string inputLine = "";
        pgmArray = std::vector<int>();

        // First line : version
        getline(infile, inputLine);
        if (inputLine.compare("P2") != 0)
            cerr << "Erreur de version" << endl;
        else
            cout << "Version : " << inputLine << endl;

        // Second line : comment
        getline(infile, inputLine);
        cout << "Commentaire : " << inputLine << endl;

        // Continue with a stringstream
        ss << infile.rdbuf();
        // Third line : size
        ss >> numCol >> numRow >> maxIntensity;
        cout << numCol << " colonnes et " << numRow << " lignes." << endl;
        for (int i = 0; i < (numRow * numCol);i++)
        {
            int value;
            ss >> value;
            pgmArray.insert(std::end(pgmArray),value);
        }
        cout << endl;
        cout << "Taille obtenue : " << pgmArray.size() << endl;
        infile.close();
    }
}

/**
 * Fonction d'export de l'image
 * @param filePath fonction d'export
 */
void PGMImage::saveTo(string filePath){
    struct stat buffer;
    //Le fichier est déjà présent
    if(stat(filePath.c_str(),&buffer) != -1){
        cerr << "Fichier déjà présent. Fin de la fonction de sauvegarde." << endl;
    }else{
        //Création de l'instance d'écriture du fichier
        ofstream fileOutput(filePath);
        cout << endl;
        cout << "Début de la sauvegarde du fichier." << endl;

        //Version du fichier
        cout << "Ecriture de la version." << endl;
        fileOutput << "P2" << endl;
        //Commentaire
        cout << "Ecriture du commentaire." << endl;
        fileOutput << "# feep.ascii.pgm." << endl;
        //Largeur et hauteur
        cout << "Ecriture de la largeur et de la hauteur." << endl;
        fileOutput << numCol << " " << numRow << endl;
        //Intensité maximale
        cout << "Ecriture de l'intensité maximale." << endl;
        fileOutput << maxIntensity << endl;
        //Table
        cout << "Ecriture de la table." << endl;
        for (int i = 0; i < numRow ; i++){
            for(int j = 0 ; j<numCol ; j++){
                if(j == (numCol-1)){
                    fileOutput << pgmArray[i * numCol + j] << endl;
                }else{
                    fileOutput << pgmArray[i * numCol + j] << " ";
                }
            }
        }
        cout << "Fin de sauvegarde du fichier" << endl;
        fileOutput.close();
    }
}

/**
 * Accès à l'élément au "nord" du noeud actuel
 * @param i Index i dans le graphe
 * @param j Index j dans le graphe
 * @return -1 en cas de noeud inexistant | sinon l'intensité de l'élément
 */
int PGMImage::getElementNord(int i, int j){
    if(i>0){
        cout << "Accès au noeud présent à l'indice x:" << i - 1 << " et y:" << j << "." << endl;
        return pgmArray[(i - 1) * numCol + j];
    }else{
        cerr << "Il n'existe pas d'éléments au nord du noeud choisi!" << endl;
        return -1;
    }
}


/**
 * Accès à l'élément au "sud" du noeud actuel
 * @param i Index i dans le graphe
 * @param j Index j dans le graphe
 * @return -1 en cas de noeud inexistant | sinon l'intensité de l'élément
 */
int PGMImage::getElementSud(int i, int j){
    if(i<numRow){
        cout << "Accès au noeud présent à l'indice x:" << i + 1 << " et y:" << j << "." << endl;
        return pgmArray[(i + 1) * numCol + j];
    }else{
        cerr << "Il n'existe pas d'éléments au nord du noeud choisi!" << endl;
        return -1;
    }
}


/**
 * Accès à l'élément à "l'est" du noeud actuel
 * @param i Index i dans le graphe
 * @param j Index j dans le graphe
 * @return -1 en cas de noeud inexistant | sinon l'intensité de l'élément
 */
int PGMImage::getElementEst(int i, int j){
    if(j<numCol){
        cout << "Accès au noeud présent à l'indice x:" << i << " et y:" << j + 1 << "." << endl;
        return pgmArray[i * numCol + (j+1)];
    }else{
        cerr << "Il n'existe pas d'éléments au nord du noeud choisi!" << endl;
        return -1;
    }    
}


/**
 * Accès à l'élément à "l'ouest" du noeud actuel
 * @param i Index i dans le graphe
 * @param j Index j dans le graphe
 * @return -1 en cas de noeud inexistant | sinon l'intensité de l'élément
 */
int PGMImage::getElementOuest(int i, int j){
    if(j>0){
        cout << "Accès au noeud présent à l'indice x:" << i << " et y:" << j - 1 << "." << endl;
        return pgmArray[i * numCol + (j-1)];
    }else{
        cerr << "Il n'existe pas d'éléments au nord du noeud choisi!" << endl;
        return -1;
    }    
}

/**
 * Met à jour l'intensité d'un noeud
 * @param i l'index en abscisse
 * @param j l'index en ordonnées
 * @param newValue la nouvelle valeur
 */
void PGMImage::updateNoeud(int i, int j, int newValue){
    if(i<0 || i>=numRow){
        cerr << "L'index est incorrecte." << endl;
    }else if(j<0 || j>=numCol){
        cerr << "L'ordonnée est incorrecte." << endl;
    }else if(newValue<0){
        cerr << "La nouvelle valeur est négative!" << endl;
    }else{
        pgmArray[i * numRow + j] = newValue;
    }
}