#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "cartes_thomas.h"


using namespace std;


class Application
{
    Deck MyDeck;
    SessionRevision MySessionRevision;
    std::thread windowThread_;
    enum windowState { terminate, hidden, visible } windowState_;
public:
    Application(Deck MyDeck,SessionRevision MySessionRevision);
    int printMenu();
    bool processMenuChoice(int choice);
    void processWindow(sf::RenderWindow& window);
    void runWindowThread();
    void execute();
};

Application::Application(Deck MyDeck, SessionRevision MySessionRevision)

// create and process the window in a separate thread
    : windowState_(hidden), windowThread_(&Application::runWindowThread, this)
{
    
    MyDeck.chargerCartes();
    MySessionRevision = MySessionRevision;
  
}


int Application::printMenu()
{
    int choice;

    system("cls");
    cout << "ANKI " << endl;
    cout << endl;

    cout << "1: Ajouter une Carte" << endl;
    cout << "2: Supprimer une Carte par numero " << endl;
    cout << "3: Supprimer une Carte par nom " << endl;
    cout << "4: Demarrer une session de revision" << endl;
    cout << "5: Afficher les cartes (noms et chemins d'images)" << endl;
    cout << "6: Quitter" << endl;
    cout << endl;
    cout << "Votre choix :";
    cin >> choice;

    return choice;
}

// créer un deck au début du main

bool Application::processMenuChoice(int choice)
{
    bool finished = false;
    string nom, recto, verso, date, entree;
    cin >> choice;
    switch (choice) {
    case 1: {
        cout << "Veuillez entrer le nom de la carte : " << endl;
        cin >> nom;
        cout << "Veuillez entrer le chemin du recto : " << endl;
        cin >> recto;
        cout << "Veuillez entrer le chemin du verso : " << endl;
        cin >> verso;
        date =CarteDeRevision:: getDateActuelle();
        CarteDeRevision * nouvelleCarte = new CarteDeRevision(nom, recto, verso, date);
        MyDeck.ajouterCarte(nouvelleCarte);
        MyDeck.sauvegarderCartes();

        // mettre méthodes pour ajouter au deck,serialiser et sauvegarder et initialiser la date aussi
        break;
    }
    case 2: {
        cout << "Veuillez entrer le numero de la carte a supprimer : " << endl;
        int n; // on peut mettre auto pour enlever case 3
        cin >> n;
        MyDeck.supprimerCarte(n);
        break;
    }
    case 3: {
        cout << "Veuillez entrer le nom de la carte a supprimer : " << endl;
        cin >> entree;
        MyDeck.supprimerCarte(entree);
        break;
    }
    case 4: {
        MySessionRevision.CarteDuJour(MyDeck);// le deck crée);
        windowState_ = windowState::visible ;
        //windowState_ = windowState::hidden; // le mettre plutot à la fin de l'affichage des cartes
        //cout << "Session terminée" << endl;
        break;
    }
    case 5: {
        MyDeck.afficherDeck();
        break;
    }
    case 6:
        finished = true;
        break;
    default:
        cout << "mauvais choix de numero, apprend a lire et recommence" << endl;
        system("pause");
    }
    return finished;
}



void Application::processWindow(sf::RenderWindow& window)
{
    vector<CarteDeRevision*> session = MySessionRevision.getDeck();
    while (window.isOpen() && windowState_ != windowState::terminate) {

        // set the window visible or not visible
        window.setVisible(windowState_ == windowState::visible);

        // event loop
        sf::Event event;
        while (window.pollEvent(event)) {

            // catch the resize events
            if (event.type == sf::Event::Resized) {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
                window.setView(sf::View(visibleArea));
            }

            // Request for closing the window : just hide it
            if (event.type == sf::Event::Closed) {
                windowState_ = windowState::hidden;
            }

            // The escape key was pressed : hide the window
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                windowState_ = windowState::hidden;
            }
            
            for (int i = 0; i < session.size(); i++) {
                session[i]->afficherCarte(window,event);
                cout << "Entrez une note entre 0 et 5" << endl;
                int d;
                cin >> d;
                while (d < 0 && d>5) {
                    cout << "t'es un gros nul, apprend à lire" << endl;
                    cin >> d;
                }
            }

            


        }

    }
}


void Application::runWindowThread()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Session de Revision"); // penser à augmenter la taille de la fenêtre
    processWindow(window);
    /*cout << "Session commencée";*/
    ;
}


void Application::execute()
{
    int choice;
    bool finished;

    do {
        choice = printMenu();
        finished = processMenuChoice(choice);
    } while (!finished);

    // request the thread to end
    windowState_ = windowState::terminate;
    // wait for termination
    windowThread_.join();
}


int main()
{
    Deck MyDeck("fichierCSV.csv");
    SessionRevision MySessionRevision("fichierCSV.csv");
    Application app(MyDeck,MySessionRevision);
    app.execute();
    return 0;
}




