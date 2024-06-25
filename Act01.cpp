#include <iostream>
#include <algorithm>
#include <numeric> //Para accumulate
#include <limits>

using namespace std;

const int MAX_SIZE = 100; //Tamaño máximo del arreglo

int main() {
    int numeros[MAX_SIZE];
    int n = 0;
    int numero;

    cout << "Ingrese números enteros (ingrese cualquier letra para terminar):" << endl;
    while (cin >> numero && n < MAX_SIZE) {
        numeros[n++] = numero;
    }
    //Limpiar el error de entrada para continuar usando cin
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
    int suma = accumulate(numeros, numeros + n, 0);
    int minimo = *min_element(numeros, numeros + n);
    int maximo = *max_element(numeros, numeros + n);

    sort(numeros, numeros + n);

    int new_n = 0;
    for (int i = 0; i < n; ++i) {
        if (numeros[i] % 2 != 0) {
            numeros[new_n++] = numeros[i];
        }
    }

    //Mostrar los resultados
    cout << "Suma de todos los números: " << suma << endl;
    cout << "Número mínimo: " << minimo << endl;
    cout << "Número máximo: " << maximo << endl;

    cout << "Números ordenados de forma ascendente (sin pares):" << endl;
    for (int i = 0; i < new_n; ++i) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    return 0;
}
