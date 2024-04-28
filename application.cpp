#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "cartes_thomas.h"
#include "cartes_paul.h"

using namespace std;


class Application
{
    /*sf::CircleShape circle_;*/ // mettre un champ session
    std::thread windowThread_;
    enum windowState { terminate, hidden, visible } windowState_;
public:
    Application();
    int printMenu();
    bool processMenuChoice(int choice);
    void processWindow(sf::RenderWindow& window);
    void runWindowThread();
    void execute();
};

Application::Application()

// create and process the window in a separate thread
    : windowState_(hidden), windowThread_(&Application::runWindowThread, this)
{
    /*circle_.setRadius(100);
    circle_.setOrigin(100, 100);
    circle_.setFillColor(sf::Color::Green);*/
    // afficher la premi�re carte � r�viser
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

// cr�er un deck au d�but du main

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
        
        date = DateActuelle();
        CarteDeRevision * nouvelleCarte = new CarteDeRevision(nom, recto, verso, date);
        MyDeck.ajouterCarte(nouvelleCarte);
        MyDeck.serialiserCarte(nouvelleCarte);
        MyDeck.sauvegarderCartes();

        // mettre m�thodes pour ajouter au deck,serialiser et sauvegarder et initialiser la date aussi
        break;
    }
    case 2: {
        cout << "Veuillez entrer le numero de la carte � supprimer : " << endl;
        int n; // on peut mettre auto pour enlever case 3
        cin >> n;
        MyDeck.supprimerCarte(n);
        break;
    }
    case 3: {
        cout << "Veuillez entrer le nom de la carte � supprimer : " << endl;
        cin >> entree;
        MyDeck.supprimerCarte(entree);
        break;
    }
    case 4: {
        MySessionRevision.CartesDuJour(// le deck cr�e);
            windowState_ = windowState::visible ;
        //windowState_ = windowState::hidden; // le mettre plutot � la fin de l'affichage des cartes
        //cout << "Session termin�e" << endl;
        break;
    }
    case 5: {
        Deck.AfficherCartes();
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
        }

        //// Clear the window
        //window.clear();
        //// Set the circle in the center of the window
        //sf::Vector2u size = window.getSize();
        //circle_.setPosition(size.x / 2.f, size.y / 2.f);
        //// Draw the circle
        //window.draw(circle_);
        //// Display the window
        //window.display();
        //// Make the thread sleep few time
        //sf::sleep(sf::milliseconds(10));
        // Deck.reviser
        // Afficher Carte avec boucle et size du vector et demander note � chaque fois
        // Afficher CarteRecto
        // event mousebuttonpressed
        // Afficher CarteVerso
        // event mousebutton pressed et i<taille du vector alors on change de carte et on recommence la boucle


    }
}


void Application::runWindowThread()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Session de Revision"); // penser � augmenter la taille de la fen�tre
    processWindow(window);
    cout << "Session commenc�e" << endl;
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
    Application app;
    app.execute();
    return 0;
}



