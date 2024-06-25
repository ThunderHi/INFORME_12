#include <iostream>
#include <deque>
#include <algorithm> //Para replace
#include <iterator>  //Para ostream_iterator

using namespace std;

int main() {
    deque<char> caracteres;
    char caracter;

    cout << "Ingrese una cadena de caracteres (ingrese cualquier caracter para terminar):" << endl;
    while (cin >> caracter) {
        caracteres.push_back(caracter);
    }
    //Limpiar el error de entrada para continuar usando cin
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Caracteres ingresados uno por uno:" << endl;
    for (auto it = caracteres.begin(); it != caracteres.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (auto it = caracteres.begin(); it != caracteres.end(); ++it) {
        char& c = *it;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            c = '*';
        }
    }
  
    cout << "Caracteres modificados en orden inverso:" << endl;
    for (auto rit = caracteres.rbegin(); rit != caracteres.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;

    // Mostrar la cadena resultante después de las modificaciones
    cout << "Cadena resultante después de reemplazar vocales por '*':" << endl;
    copy(caracteres.begin(), caracteres.end(), ostream_iterator<char>(cout, ""));
    cout << endl;

    return 0;
}
