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
    //Maj je pense que ça pu de taffer avec des date, il vaut mieux travailler avec des intervalles int I, ne plus l'algo SM2 est basé sur ça, je pense ça sera easy pour les calcule et on pourra séléctionner les cartes dans la classe SessionRevion avec des entiers c plus simples selon moi.
    double facteur_difficulte_;
    //int score_difficulte_; pas dans la classe carte 
    int serie_; // nombre n que j'ai appelé serie dont tu m'avais parlé mais à voire
    int intervalle_revision_;
public:
    // Constructeur
    CarteDeRevision(const string& recto = "a", const string& verso = "a") : recto_(recto), verso_(verso), facteur_difficulte_(2.5), serie_(0), intervalle_revision_(0) {}
    const string& getRecto() const { return recto_; }
    void setRecto(const string& recto);
    const string& getVerso() const { return verso_; }
    void setVerso(const string& verso);
    const int& getIntervalle() const { return intervalle_revision_; }
    void setIntervalle(const int& I);
    const double& getFacteurDifficulte() const { return facteur_difficulte_; }
    const int& getSerie() const { return serie_; }

    void MajIntervalleRevision(const int& scoreUx);



}; //THOMAS.B

class Deck {
private:
    vector<CarteDeRevision*> deck_; // Vecteur pour stocker les cartes
    string fichierCSV_; // Chemin vers le fichier CSV

public:
    //Constructeur
    Deck(const string& fichierCSV) : fichierCSV_(fichierCSV) {}

    //Le constructeur Deck est initialisé avec le chemin vers le fichierCSV et il prend la valeur de vector<CarteDeRevision *> deck_ par défaut qui est le vecteur vide.

     // Méthode privée pour sérialiser une carte au format CSV
    static string serialiserCarte(const CarteDeRevision& carte); //convertit format carte en format csv

    // "static" permet d'appeler la méthode serialiserCarte sans avoir besoin de créer un objet ou une instance Deck, en fait la méthode peut-être appelée sans avoir besoin d'être lié ou relatif à un objet (c'est le contraire de carte.getRecto() par exemple), voire nouvelle syntaxe dans le main test. Attention on ne précise le fait que la ùéthode est static seulement dans le fichier .h et pas dans le fichier .cpp.

    // Méthode privée pour désérialiser une ligne CSV en une carte
    static CarteDeRevision deserialiserCarte(const string& ligneCSV); //convertir les lignes csv en format cartederevision

    // Méthode pour charger les cartes depuis le fichier CSV
    void chargerCartes();

    //Méthode pour sauvegarder les cartes dans le fichier CSV
    void sauvegarderCartes() const;

    // Méthode pour ajouter une carte au deck
    void ajouterCarte(const CarteDeRevision& carte);

    // Méthode pour supprimer une carte du deck
    void supprimerCarte(int index);

    //Méthode afficher
    void afficherDeck() const;
};




#endif // CARTES_H

