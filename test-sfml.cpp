#include <SFML/Graphics.hpp>
#include <iostream>
#include "cartes_thomas.h"
#include <Windows.h>
using namespace sf;
int main()
{
	SetConsoleOutputCP(65001);

	//CODE AFFICHER IMAGE MAIS CACA

	RenderWindow window;
	ContextSettings option;
	option.antialiasingLevel = 8;

	window.create(VideoMode(800, 600), "Ta grand mère", Style::Close, option);
	Deck myDeck("fichierCSV.csv");
	CarteDeRevision carte0("capitaleFrance.png", "paris.png");
	Texture textureRecto;
	Texture textureVerso;
	if (!textureRecto.loadFromFile(carte0.getRecto()) || !textureVerso.loadFromFile(carte0.getVerso())) {
		// Gérer les erreurs de chargement d'image
		return EXIT_FAILURE;
	}
	Sprite spriteRecto(textureRecto);
	Sprite spriteVerso(textureVerso);
	window.draw(spriteRecto);
	window.draw(spriteVerso);

	// Boucle principale de rendu SFML
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.display();
	}

	return EXIT_SUCCESS;
}


}