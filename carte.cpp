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
    cout << "JE SUIS THOMAS" << endl;
    cout << "FIN" << endl;
    return 0;
}