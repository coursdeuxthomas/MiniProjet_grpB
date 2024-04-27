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

void CarteDeRevision::setIntervalle(const int& I)
{
    this->intervalle_revision_ = I;
}

void CarteDeRevision::MajIntervalleRevision(const int& scoreUx)
{
    if (scoreUx >= 3) { // correct response
        if (serie_ == 0) {
            intervalle_revision_ = 1;
        }
        else if (serie_ == 1) {
            intervalle_revision_ = 6;
        }
        else {
            intervalle_revision_ = round(intervalle_revision_ * facteur_difficulte_);
        }
        serie_++;
    }
    else { // incorrect response
        serie_ = 0;
        intervalle_revision_ = 1;
    }

    // Update the easiness factor
    facteur_difficulte_ += (0.1 - (5 - scoreUx) * (0.08 + (5 - scoreUx) * 0.02));
    if (facteur_difficulte_ < 1.3) {
        facteur_difficulte_ = 1.3;
    }
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
//pb semble résolu si on ne mélange pas l'utilsation des deux méthode cahrger et sauvegarder dans le main. On a choisit de garder l'utilisation de sauvegarder pour que l'ux crée les carte direct depuis l'interface SFML donc le main, les carte seront ensuite save dans le csv grace à la méthode sauvegarder.

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

