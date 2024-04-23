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

public:
    // Méthode privée pour sérialiser une carte au format CSV
    static string serialiserCarte(const CarteDeRevision& carte);
    
    // "static" permet d'appeler la méthode serialiserCarte sans avoir besoin de créer un objet ou une instance Deck, en fait la méthode peut-être appelée sans avoir besoin d'être lié ou relatif à un objet (c'est le contraire de carte.getRecto() par exemple), voire nouvelle syntaxe dans le main test. Attention on ne précise le fait que la ùéthode est static seulement dans le fichier .h et pas dans le fichier .cpp.
    
    // Méthode privée pour désérialiser une ligne CSV en une carte
    static CarteDeRevision deserialiserCarte(const string& ligneCSV);

    ////Constructeur
    //Deck(const std::string& fichierCSV);

    //// Méthode pour charger les cartes depuis le fichier CSV
    //void chargerCartes();

    //// Méthode pour sauvegarder les cartes dans le fichier CSV
    //void sauvegarderCartes() const;

    //// Méthode pour ajouter une carte au deck
    //void ajouterCarte(const CarteDeRevision& carte);

    //// Méthode pour supprimer une carte du deck
    //void supprimerCarte(int index);

    //// Accesseur pour récupérer les cartes
    //const std::vector<CarteDeRevision>& getCartes() const;
};




#endif // CARTES_H

