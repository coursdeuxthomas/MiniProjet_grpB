﻿#include "cartes_thomas.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <Windows.h>




using namespace std;

int main() 
{
	SetConsoleOutputCP(65001);
	/*CarteDeRevision pythagore("Théorême de Pythagore","La somme des carré des cotés égale au carré de l'hypo");
	cout << "Voici la carte pythagore :" << endl;
	cout << "recto : " << pythagore.getRecto()<<endl;
	cout << "verso : " << pythagore.getVerso()<<endl;
	return 0;*/

	CarteDeRevision carte("recto", "verso");
	string carteseria = Deck::serialiserCarte(carte);
	cout << "Texte de la carte serialiser : " << carteseria << endl;
	CarteDeRevision carteDeseria = Deck::deserialiserCarte("Quelle est la capitale de la France,Paris,1.00,1,2024-04-23");
	cout << "Recto de la carte deseria : " << carteDeseria.getRecto() << endl;
	cout << "Verso de la carte deseria : " << carteDeseria.getVerso() << endl;  
	





}

