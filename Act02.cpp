#include <iostream>
#include <algorithm>
#include <numeric> // Para std::accumulate
#include <limits>

using namespace std;

int main() {
    const int MAX_SIZE = 100;
    int numeros[MAX_SIZE];
    int n = 0;
    int numero;

    cout << "Ingrese números enteros (ingrese cualquier letra para terminar):" << endl;
    while (cin >> numero && n < MAX_SIZE) {
        numeros[n++] = numero;
    }
    // Limpiar el error de entrada para continuar usando cin
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // a) Calcular la suma de todos los números
    int suma = accumulate(numeros, numeros + n, 0);

    // b) Encontrar el número máximo y mínimo en la lista
    int minimo = *min_element(numeros, numeros + n);
    int maximo = *max_element(numeros, numeros + n);

    // c) Ordenar los números de forma ascendente
    sort(numeros, numeros + n);

    // d) Eliminar los números pares del contenedor
    int new_n = 0;
    for (int i = 0; i < n; ++i) {
        if (numeros[i] % 2 != 0) {
            numeros[new_n++] = numeros[i];
        }
    }

    // Mostrar los resultados
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
