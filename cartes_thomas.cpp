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
    getline(iss, verso, ',');
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
//meme pb ici que en dessous je pense juste avant de charger les éléments du csv il faut vider le deck puis sinon si on charge deux fois à la suite après avoir rajouté quelque cartes dans le csv ça va faire un doublon de deck

void Deck::sauvegarderCartes() const
{
    ofstream fichier(fichierCSV_);
    if (!fichier) {
        cerr << "Erreur : Impossible d'ouvrir le fichier" << endl;
        return;
    }
    for (int i = 0; i < deck_.size(); i++)
    {
        const CarteDeRevision* carte = deck_[i];
        string newligne = serialiserCarte(*carte);
        fichier << newligne << endl;
    }
}// attnetion pb ça rajouter des ligne au fichier à la fin donc peut créer des doublons si le deck à déjà été suavegarder. Mon idée c'est dès que tu veux sauvegarder tu dois d'abord effacer tous ce qui est dans le fichier.

void Deck::ajouterCarte(const CarteDeRevision& carte)
{
    deck_.push_back(new CarteDeRevision(carte));
}

void Deck::supprimerCarte(int index)
{
    if (index < deck_.size() && index >= 0) // && permet d'avoir une condition en "et"
    {
        delete deck_[index]; // libère l'espace de l'élément dans la mémoire mais ne supprime pas effectivement l'élément
        deck_.erase(deck_.begin() + index);// supprime l'élément et déplace les éléments suivant pour ajuster la taille du vecteur
    }
    else
    {
        cerr << "Index fourni invalide" << endl;
    }
}

void Deck::afficherDeck() const
{
    cout << "-------------------- Cartes dans le Deck --------------------" << endl;
    cout << endl;
    for (const CarteDeRevision* carte : deck_) //autre méthode de parcours
    {
        cout << "Recto : " << carte->getRecto() << " , Verso : " << carte->getVerso() << endl;//Utilisation de -> car getRecto est dans la classe CarteDeRevision
    }
}