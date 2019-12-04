#include<stdlib.h>
#include<stdio.h>

#include<iostream>
using namespace std;

#include "Image/pgm.h"

int main(){
    PGMImage image = PGMImage("File/file.pgm");
    image.displayImage();
    image.updateNoeud(0, 0, 3);
    image.displayImage();
    image.saveTo("File/newImage.pgm");
    return 0;
}