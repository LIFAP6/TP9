#include <iostream> // cout, cerr
#include <fstream>  // ifstream
#include <sstream>  // stringstream
#include <vector>
using namespace std;
#include <sys/stat.h>

#include "pgm.h"
#include "noeud.h"

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
    pgmArray = std::vector<Noeud>();
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
    pgmArray = std::vector<Noeud>();
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
            cout << pgmArray[i * numCol + j].getValue() << " ";
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
        pgmArray = std::vector<Noeud>();

        // Première ligne : version
        getline(infile, inputLine);
        if (inputLine.compare("P2") != 0)
            cerr << "Erreur de version" << endl;
        else
            cout << "Version : " << inputLine << endl;

        // Seconde ligne : commentaire
        getline(infile, inputLine);
        cout << "Commentaire : " << inputLine << endl;

        // Continue avec une ligne discontinue en string
        ss << infile.rdbuf();

        // Troisième ligne : taille
        ss >> numCol >> numRow >> maxIntensity;
        cout << numCol << " colonnes et " << numRow << " lignes." << endl;

        //Ajout du noeud S
        pgmArray.insert(std::end(pgmArray), Noeud(0, 0, 255, START));
        //Ajout des noeuds à partir du fichier
        for (int i = 0; i < (numRow * numCol); i++)
        {
            int value;
            ss >> value;
            Noeud noeud = Noeud(i%numCol, i/numRow, value,MIDDLE);
            pgmArray.insert(std::end(pgmArray), noeud);
        }
        //Ajout du noeud S
        pgmArray.insert(std::end(pgmArray), Noeud(0, 0, 0, END));

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
                    fileOutput << pgmArray[i * numCol + j].getValue() << endl;
                }else{
                    fileOutput << pgmArray[i * numCol + j].getValue() << " ";
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
        return pgmArray[(i - 1) * numCol + j].getValue();
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
        return pgmArray[(i + 1) * numCol + j].getValue();
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
        return pgmArray[i * numCol + (j+1)].getValue();
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
        return pgmArray[i * numCol + (j-1)].getValue();
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
        pgmArray[i * numRow + j].setValue(newValue);
    }
}

/**
 * Fonction de recherche de chaine améliorante
 * @return vector<Noeud> chaine améliorante si le puit est marqué
 * @return vector<Noeud> vector vide si la chaine est vide
 */
vector<Noeud> PGMImage::rechercheChaineAmeliorante(vector<Noeud> pgmImage){
    vector<Noeud> file = vector<Noeud>();
    vector<Noeud> chaineAmeliorante = vector<Noeud>();

    //La source est "marquée"
    pgmImage.insert(std::end(pgmImage), pgmImage[0]);
    pgmImage.at(1).setMarkedStatus(true);
    
    //Tant que la file est vide et le puit n'est pas marqué
    do
    {
        //On considère x comme le premier élément de la file
        Noeud x = Noeud();
        //On enlève le premier élément de la pile
        pgmImage.erase(pgmImage.begin());

        //On regarde ses successeurs
        vector<Noeud>successeurs = x.getSuccesseurs();
        for(Noeud successeur:successeurs){
            //Si le successeur n'est pas marqué et son flot est inférieur à sa capacité maximum
            if(successeur.isMarked()!=true && true){
                //On ajoute le successeur à la file
                pgmImage.insert(std::end(pgmImage), successeur);
            }
        }

        //On regarde ses prédecesseurs
        vector<Noeud> predecesseurs = x.getPredecesseurs();
        for(Noeud predecesseur:predecesseurs){
            //Si le prédecesseur n'est pas marqué et son flot est strictement positif
            if(predecesseur.isMarked()!=true && true){
                //On ajoute le prédecesseur à la file
                pgmImage.insert(std::end(pgmImage), predecesseur);
            }
        }
    } while (file != vector<Noeud>() && pgmArray.back().isMarked != true);

    //Si le puit est marqué
    if(pgmImage.back().isMarked()){
        //Chaine améliorante
        return chaineAmeliorante;
    }else{
        //Pas de chaîne améliorante
        cout << "Aucune chaine améliorante ici!" << endl;
        return vector<Noeud>();
    }
}

/**
 * Algorithme de Ford-Fulkerson
 */
vector<Noeud> PGMImage::fordFulkerson(){
    vector<Noeud> newPGMImage = pgmArray;
    vector<Noeud> chaineAmeliorante = rechercheChaineAmeliorante(newPGMImage);
    do
    {
        //Calcul de la capacité résiduelle dans la chaîne améliorante
        int flotResiduel = calculFlotResiduel(chaineAmeliorante);

        //Recherche d'une chaîne améliorante
        chaineAmeliorante = rechercheChaineAmeliorante(newPGMImage);

        //On augmente ici

        //On diminue ici
    } while (chaineAmeliorante != vector<Noeud>());

    //On retourne l'image modifiée
    return newPGMImage;
}

/**Passer par des arcs avec deux paramètres
 * mu+ -> arc i->j
 * mu- -> arc j->i
 * retourner valeur minimale
 * 
 */
int PGMImage::calculFlotResiduel(vector<Noeud>chaineAmeliorante){
    int flotResiduel = INTMAX_MAX;
    for(vector<Noeud>::size_type i=0;i<chaineAmeliorante.size();i++){
        int newFlotResiduel = -1/*Capacité - flot de l'arc*/;
        if(newFlotResiduel<flotResiduel){
            flotResiduel = newFlotResiduel;
        }
    }
    return flotResiduel;
}