//#include "cartes_thomas.h"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>
//#include <sstream>
//#include <Windows.h>
//#include <SFML/Graphics.hpp>
//
//
//
//
//using namespace std;
//using namespace sf;
//
//int main()
//{
//	SetConsoleOutputCP(65001);
//	/*CarteDeRevision pythagore("Théorême de Pythagore","La somme des carré des cotés égale au carré de l'hypo");
//	cout << "Voici la carte pythagore :" << endl;
//	cout << "recto : " << pythagore.getRecto()<<endl;
//	cout << "verso : " << pythagore.getVerso()<<endl;
//	return 0;*/
//
//	/*CarteDeRevision carte("recto", "verso");
//	string carteseria = Deck::serialiserCarte(carte);
//	cout << "Texte de la carte serialiser : " << carteseria << endl;
//	CarteDeRevision carteDeseria = Deck::deserialiserCarte("Quelle est la capitale de la France,Paris,1.00,1,2024-04-23");
//	cout << "Recto de la carte deseria : " << carteDeseria.getRecto() << endl;
//	cout << "Verso de la carte deseria : " << carteDeseria.getVerso() << endl;*/  
//
//
//	/*myDeck.afficherDeck();
//	CarteDeRevision carte0("capitale france", "paris");
//	CarteDeRevision carte1("capitale espagne ", "madrid");
//	CarteDeRevision carte2("capitale finlande", "oslo");
//	CarteDeRevision carte3("capitale portugal", "lisbonne");
//	CarteDeRevision carte4("capitale suisse", "bremes");
//	myDeck.ajouterCarte(carte0);
//	myDeck.ajouterCarte(carte1);
//	myDeck.ajouterCarte(carte2);
//	myDeck.ajouterCarte(carte3);
//	myDeck.ajouterCarte(carte4);
//	myDeck.afficherDeck();
//	myDeck.supprimerCarte(4);
//	myDeck.sauvegarderCartes();
//	myDeck.afficherDeck();*/
//
//
//
//
//

// CODE BASE SFML

	/*RenderWindow window;
	ContextSettings option;
	option.antialiasingLevel = 8;

	window.create(VideoMode(800, 600), "Ta grand mère", Style::Close, option);

	Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
	}*/

	/*circleshape shape(100.f);
	shape.setfillcolor(sf::color::green);
	while (window.isopen())
	{
		sf::event event;
		while (window.pollevent(event))
		{
			if (event.type == sf::event::closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}*/

	//CODE AFFICHER IMAGE MAIS CACA

	//	RenderWindow window;
	//	ContextSettings option;
	//	option.antialiasingLevel = 8;
	//
	//	window.create(VideoMode(800, 600), "Ta grand mère", Style::Close, option);
	//	Deck myDeck("fichierCSV.csv");
	//	CarteDeRevision carte0("capitaleFrance.png", "paris.png");
	//	Texture textureRecto;
	//	Texture textureVerso;
	//	if (!textureRecto.loadFromFile(carte0.getRecto()) || !textureVerso.loadFromFile(carte0.getVerso())) {
	//		// Gérer les erreurs de chargement d'image
	//		return EXIT_FAILURE;
	//	}
	//	Sprite spriteRecto(textureRecto);
	//	Sprite spriteVerso(textureVerso);
	//	window.draw(spriteRecto);
	//	window.draw(spriteVerso);
	//
	//	// Boucle principale de rendu SFML
	//	while (window.isOpen()) {
	//		Event event;
	//		while (window.pollEvent(event)) {
	//			if (event.type == Event::Closed)
	//				window.close();
	//		}
	//
	//		window.display();
	//	}
	//
	//	return EXIT_SUCCESS;
	//}




#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime> 
#include <iomanip> 
#include <string>   
#include "cartes_thomas.h"
#include <Windows.h>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS 
using namespace std;
using namespace sf;
int main()
{
	SetConsoleOutputCP(65001);
	Deck Mydeck("fichierCSV.csv");
	SessionRevision Session1("sessionCSV.csv");
	string dateActuelle = CarteDeRevision::getDateActuelle();
	cout << dateActuelle << endl;
	CarteDeRevision* carte0 = new CarteDeRevision("carte0", "capitale", "paris", "2022-01-01");
	CarteDeRevision* carte1 = new CarteDeRevision("carte1", "maman", "sylvie", "2025-01-01");
	//CarteDeRevision carte0("carte0", "capitale", "paris", dateActuelle);
	//CarteDeRevision carte1("carte1", "maman", "sylvie", dateActuelle);
	Mydeck.ajouterCarte(carte0);
	Mydeck.afficherDeck();
	carte0->MajIntervalleRevision(4);
	Mydeck.afficherDeck();

	Session1.CarteDuJour(Mydeck);
	Session1.afficherSession();

	//// Comparaison de différentes dates
	//bool result1 = SessionRevision::comparerDates("2022-04-30", "2022-05-01");
	//bool result2 = SessionRevision::comparerDates("2022-05-01", "2022-04-30");
	//bool result3 = SessionRevision::comparerDates("2022-05-01", "2022-05-01");
	//bool result4 = SessionRevision::comparerDates("2023-01-01", "2022-12-31");

	//// Affichage des résultats
	//std::cout << std::boolalpha; // Pour afficher true/false au lieu de 1/0
	//std::cout << "Resultat 1 : " << result1 << std::endl;
	//std::cout << "Resultat 2 : " << result2 << std::endl;
	//std::cout << "Resultat 3 : " << result3 << std::endl;
	//std::cout << "Resultat 4 : " << result4 << std::endl;













}



