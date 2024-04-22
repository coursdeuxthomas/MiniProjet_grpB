#include "cartes.h"
#include <iostream>
using namespace std;

void CarteDeRevision::setRecto(const string& recto) {
    this->recto_ = recto; // Définit le contenu du côté recto de la carte avec la valeur fournie en param 
}

void CarteDeRevision::setVerso(const std::string& verso) {
    this->verso_ = verso; // Définit le contenu du côté verso de la carte avec la valeur fournie en param
}
