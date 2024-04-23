#ifndef CARTES_H
#define CARTES_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class CarteDeRevision {
private:
    string recto_;
    string verso_;
    // il faut rajouter les facteurs pour l'algorithme sm2 : le facteur de difficulté (type double), le score de difficulté (différent du facteur, de type entier entre 1 et 5) et la date de PROCHAINE révision (au format : "AAAA-MM-JJ")
    double facteur_difficulte_;
    int score_difficulté_;
    string date_revision_;
public:
    // Constructeur
    CarteDeRevision(const string& recto = "a", const string& verso = "a") : recto_(recto), verso_(verso) {}
    const string getRecto() const { return recto_; }
    void setRecto(const string& recto);
    const string getVerso() const { return verso_; }
    void setVerso(const string& verso);
}; //THOMAS.B

class Deck {
private:
    vector<CarteDeRevision *> deck_; // Vecteur pour stocker les cartes
    string fichierCSV_; // Chemin vers le fichier CSV

    // Méthode privée pour sérialiser une carte au format CSV
    string serialiserCarte(const CarteDeRevision& carte) const 
    {
        return carte.getRecto() + "," + carte.getVerso();
    }

    // Méthode privée pour désérialiser une ligne CSV en une carte
    CarteDeRevision deserialiserCarte(const std::string& ligneCSV) const {
        istringstream iss(ligneCSV);
        string recto, verso;
        getline(iss, recto, ',');
        getline(iss, verso);
        return CarteDeRevision(recto, verso);
    }

   


public:
    /*Constructeur
    Deck(const std::string& fichierCSV);

    // Méthode pour charger les cartes depuis le fichier CSV
    void chargerCartes();

    // Méthode pour sauvegarder les cartes dans le fichier CSV
    void sauvegarderCartes() const;

    // Méthode pour ajouter une carte au deck
    void ajouterCarte(const CarteDeRevision& carte);

    // Méthode pour supprimer une carte du deck
    void supprimerCarte(int index);

    // Accesseur pour récupérer les cartes
    const std::vector<CarteDeRevision>& getCartes() const;*/
};




#endif // CARTES_H

