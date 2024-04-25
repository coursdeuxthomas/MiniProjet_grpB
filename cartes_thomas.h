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
    int score_difficulte_;
    string date_revision_;
public:
    // Constructeur
    CarteDeRevision(const string& recto = "a", const string& verso = "a") : recto_(recto), verso_(verso), facteur_difficulte_(1.0), score_difficulte_(1), date_revision_("2000-01-01") {}
    const string& getRecto() const { return recto_; }
    void setRecto(const string& recto);
    const string& getVerso() const { return verso_; }
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

    //Constructeur
    Deck(const string& fichierCSV) : fichierCSV_(fichierCSV) {}
    
    //Le constructeur Deck est initialisé avec le chemin vers le fichierCSV et il prend la valeur de vector<CarteDeRevision *> deck_ par défaut qui est le vecteur vide.

    // Méthode pour charger les cartes depuis le fichier CSV
    void chargerCartes();

    /* Méthode pour sauvegarder les cartes dans le fichier CSV
    void sauvegarderCartes() const;*/

    //// Méthode pour ajouter une carte au deck
    //void ajouterCarte(const CarteDeRevision& carte);

    //// Méthode pour supprimer une carte du deck
    //void supprimerCarte(int index);

    //// Accesseur pour récupérer les cartes
    //const vector<CarteDeRevision>& getCartes() const;

    ////Méthode pour changer la prochaine date de  révision
    // void setDateRevision (const string & nouvelle_date)

    //// Méthode pour avoir la prochaine date de révision:
    // void getDateRevision() const {return date_revision_;}
};




#endif // CARTES_H

