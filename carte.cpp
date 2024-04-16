#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h> // utiliser pour gérer l'encodage
using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    cout << "Héllo World" << endl;
    cout << "fin" << endl;
    cout << "COUCOUS" << endl;
    return 0;
}