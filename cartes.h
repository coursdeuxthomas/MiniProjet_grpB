#ifndef CARTES_H
#define CARTES_H
#include <iostream>
#include <string>
using namespace std;

class CarteDeRevision {
private:
    string recto_;
    string verso_;

public:
    // Constructeur
    CarteDeRevision(const string recto, const string verso) {recto_, verso_ = recto, verso;}

    const string getRecto() const { return recto_; }
    void setRecto(const string& recto);
    const string getVerso() const { return verso_; }
    void setVerso(const string& verso);
}; //THOMAS.B



#endif // CARTES_H

