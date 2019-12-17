#include<stdlib.h>
#include<stdio.h>

#include<iostream>
using namespace std;

#include "Image/pgm.h"

int main(){
    //Chargement de l'image
    PGMImage image = PGMImage("File/file.pgm");
    //Affichage de l'image
    image.displayImage();

    //Affichage de l'image
    image.displayImage();

    //Application de l'algorithme Ford Fulkerson
    image.fordFulkerson();

    //Affichage de l'image modifiée
    image.displayImage();

    //Sauvegarde de l'image
    image.saveTo("File/modified_image.pgm");
    return 0;
}