#include "cartes_thomas.h"
#include <iostream>
using namespace std;

// Méthode classe CarteDeRevision

void CarteDeRevision::setNom(const string& nom)
{
    this->nom_ = nom;
}

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

    if (date_ != "AAAA-MM-JJ") { //à relire et comprendre
        // Convertir la date actuelle en année, mois et jour
        int year, month, day;
        if (sscanf_s(date_.c_str(), "%d-%d-%d", &year, &month, &day) == 3);

        // Ajouter l'intervalle de révision aux jours
        day += intervalle_revision_;

        // Vérifier si le mois a changé
        while (day > 30) {
            month++;
            day -= 30;
        }

        // Vérifier si l'année a changé
        while (month > 12) {
            year++;
            month -= 12;
        }

        // Formater la nouvelle date
        stringstream ss;
        ss << setw(4) << setfill('0') << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << day;
        date_ = ss.str();
    }


    //supprimer la carte déja presente dans le deck et ajouter cette nouvelle carte mise à jour
    //supprimerCarte(this->getNom());
    //deck.ajouterCarte(*this); //Utilisation de l'opérateur *, j'accède à lobjet carte sur lequel pointe this

}

string CarteDeRevision::getDateActuelle() { //à relire et comprendre
    // Obtenir le temps actuel
    time_t t = time(nullptr);
    struct tm tm;

    // Convertir le temps en structure tm contenant l'année, le mois et le jour actuels
    localtime_s(&tm, &t);

    // Formater la date actuelle
    char date[11]; // "AAAA-MM-JJ" + caractère nul
    sprintf_s(date, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    return string(date);
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

void Deck::ajouterCarte(CarteDeRevision* carte)
{
    deck_.push_back(carte);// attention c'est un constructeur de copie de la carte, pb que je rencontre : je fais une modification sur la carte après l'avoir mise dans le deck, et la carte présente dans le carte n'est pas modifié car c'est une copie.
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

void Deck::supprimerCarte(const string& nom)
{
    vector<CarteDeRevision*>::iterator it;//marche mais voir si pas mieux de déclarer it dans la boucle for avce un type auto
    for (it = deck_.begin(); it != deck_.end(); it++)
    {
        if ((*it)->getNom() == nom)
        {
            delete* it;
            deck_.erase(it);
            return;
        }
    }
    cout << "Carte portant le nom " << nom << "n'a pas été trouvée shehh" << endl;

}

void Deck::afficherDeck() const
{
    cout << "-------------------- Cartes dans le Deck --------------------" << endl;
    cout << endl;
    for (int i = 0; i < deck_.size(); i++) //autre méthode de parcours
    {
        const CarteDeRevision* carte = deck_[i];
        cout << "Index de la carte : " << i << ", Nom de la carte : " << carte->getNom() << ", Recto : " << carte->getRecto() << ", Verso : " << carte->getVerso() << ", Facteur de difficulté : " << carte->getFacteurDifficulte() << ", Série : " << carte->getSerie() << ", Date de la prochaine révision : " << carte->getDate() << endl;//Utilisation de -> car getRecto est dans la classe CarteDeRevision
    }
}

const CarteDeRevision& Deck::getCarte(int index) const
{
    if (index >= 0 && index < deck_.size()) {
        return *deck_[index];
    }
    else {
        throw out_of_range("Index hors limites");
    }
}

const vector<CarteDeRevision*> Deck::getDeck() const
{
    return deck_;
}



//Méthode de la classe Session de Révision

bool SessionRevision::comparerDates(const string& date1, const string& date2)
{
    tm tm1 = {};
    tm tm2 = {};

    sscanf_s(date1.c_str(), "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf_s(date2.c_str(), "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);

    // Ajuster les mois (tm_mon est de 0 à 11)
    tm1.tm_mon -= 1;
    tm2.tm_mon -= 1;

    tm1.tm_year -= 1900;
    tm2.tm_year -= 1900;

    // Convertir les structures tm en time_t (en secondes depuis l'époque)
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    // Comparer les valeurs de temps
    return time1 <= time2;
}

void SessionRevision::CarteDuJour(const Deck fouretout)
{
    string dateActuelle = CarteDeRevision::getDateActuelle();
    session_.clear();
    vector<CarteDeRevision*> deck = fouretout.getDeck();

    for (size_t i = 0; i < deck.size(); i++)
    {
        string datecarte = deck[i]->getDate();
        cout << datecarte << endl;
        if (comparerDates(datecarte, dateActuelle))
        {
            session_.push_back(deck[i]);
        }
    }
}

void SessionRevision::afficherSession() const
{
    cout << "-------------------- Cartes dans la Session --------------------" << endl;
    cout << endl;
    for (int i = 0; i < session_.size(); i++) //autre méthode de parcours
    {
        const CarteDeRevision* carte = session_[i];
        cout << "Index de la carte : " << i << ", Nom de la carte : " << carte->getNom() << ", Recto : " << carte->getRecto() << ", Verso : " << carte->getVerso() << ", Facteur de difficulté : " << carte->getFacteurDifficulte() << ", Série : " << carte->getSerie() << ", Date de la prochaine révision : " << carte->getDate() << endl;//Utilisation de -> car getRecto est dans la classe CarteDeRevision
    }
}