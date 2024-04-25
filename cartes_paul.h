#ifndef CARTES_H
#define CARTES_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class SessionDeRevision {
	Deck deck_;
	CarteRevision* carte_actuelle_;
public:
	SessionRevision(const Deck& deck) : deck(deck), carte_actuelle(nullptr) {}
	void ReviserCarte();
	
};
