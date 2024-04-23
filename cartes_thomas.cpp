#include "cartes_thomas.h"
#include <iostream>
using namespace std;

// Méthode classe CarteDeRevision
void CarteDeRevision::setRecto(const string& recto) 
{
    this->recto_ = recto; // Définit le contenu du côté recto de la carte avec la valeur fournie en param 
}

void CarteDeRevision::setVerso(const std::string& verso) 
{
    this->verso_ = verso; // Définit le contenu du côté verso de la carte avec la valeur fournie en param
}

//Méthode classe Deck

string Deck::serialiserCarte(const CarteDeRevision& carte)
{
    return carte.getRecto() + "," + carte.getVerso();
}

CarteDeRevision Deck::deserialiserCarte(const string& ligneCSV)
{
    istringstream iss(ligneCSV);
    string recto, verso;
    getline(iss, recto, ',');
    getline(iss, verso);
    return CarteDeRevision(recto, verso);
}

void Deck::chargerCartes()
{
    ifstream fichier(fichierCSV_); // ouvrir fichier en mode lecteur
    if (!fichier) {
        cerr << "Erreur : Impossible d'ouvrir le fichier" << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) 
    //la boucle lis chaque ligne du fichier et la stocke dans la variable ligne
    {
        CarteDeRevision carte = deserialiserCarte(ligne);
        deck_.push_back(new CarteDeRevision(carte)); //utilisation du constructeur de copie de CarteDeRevision
    }

}
