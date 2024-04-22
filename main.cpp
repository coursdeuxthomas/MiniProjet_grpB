#include "cartes_thomas.h"
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
	CarteDeRevision pythagore("Théorême de Pythagore","La somme des carré des cotés égale au carré de l'hypo");
	cout << "Voici la carte pythagore :" << endl;
	cout << "recto : " << pythagore.getRecto()<<endl;
	cout << "verso : " << pythagore.getVerso()<<endl;
	return 0;
}

