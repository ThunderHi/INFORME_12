#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Contacto {
    string nombre;
    string telefono;
    string email;
};

// Función auxiliar para convertir un string a minúsculas (para la búsqueda insensible a mayúsculas)
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main() {
    map<string, Contacto> agenda; //Mapa para almacenar los contactos (ordenado por el nombre)

    char opcion;
    do {
        cout << "\nOpciones:\n";
        cout << "a) Agregar nuevo contacto\n";
        cout << "b) Buscar contacto por nombre\n";
        cout << "c) Actualizar contacto existente\n";
        cout << "d) Mostrar lista de contactos ordenada alfabéticamente\n";
        cout << "e) Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); //Limpiar el buffer de entrada

        switch (opcion) {
            case 'a': {
                //Agregar nuevo contacto
                Contacto nuevo_contacto;
                cout << "Nombre: ";
                getline(cin, nuevo_contacto.nombre);
                cout << "Teléfono: ";
                getline(cin, nuevo_contacto.telefono);
                cout << "Correo electrónico: ";
                getline(cin, nuevo_contacto.email);

                //Insertar en el mapa
                agenda[toLower(nuevo_contacto.nombre)] = nuevo_contacto;
                cout << "Contacto agregado correctamente.\n";
                break;
            }
            case 'b': {
                //Buscar contacto por nombre
                string nombre_buscar;
                cout << "Ingrese el nombre del contacto a buscar: ";
                getline(cin, nombre_buscar);

                //Convertir a minúsculas para búsqueda insensible a mayúsculas
                string nombre_lower = toLower(nombre_buscar);

                //Buscar en el mapa
                auto it = agenda.find(nombre_lower);
                if (it != agenda.end()) {
                    cout << "Contacto encontrado:\n";
                    cout << "Nombre: " << it->second.nombre << endl;
                    cout << "Teléfono: " << it->second.telefono << endl;
                    cout << "Correo electrónico: " << it->second.email << endl;
                } else {
                    cout << "Contacto no encontrado.\n";
                }
                break;
            }
            case 'c': {
                //Actualizar contacto existente
                string nombre_actualizar;
                cout << "Ingrese el nombre del contacto a actualizar: ";
                getline(cin, nombre_actualizar);

                //Convertir a minúsculas para búsqueda insensible a mayúsculas
                string nombre_lower = toLower(nombre_actualizar);

                //Verificar si el contacto existe
                auto it = agenda.find(nombre_lower);
                if (it != agenda.end()) {
                    cout << "Ingrese el nuevo teléfono: ";
                    getline(cin, it->second.telefono);
                    cout << "Ingrese el nuevo correo electrónico: ";
                    getline(cin, it->second.email);
                    cout << "Contacto actualizado correctamente.\n";
                } else {
                    cout << "Contacto no encontrado.\n";
                }
                break;
            }
            case 'd': {
                //Mostrar lista de contactos ordenada alfabéticamente
                if (agenda.empty()) {
                    cout << "La agenda está vacía.\n";
                } else {
                    cout << "Lista de contactos ordenada alfabéticamente:\n";
                    for (const auto& pair : agenda) {
                        cout << "Nombre: " << pair.second.nombre << endl;
                        cout << "Teléfono: " << pair.second.telefono << endl;
                        cout << "Correo electrónico: " << pair.second.email << endl;
                        cout << "-----------------\n";
                    }
                }
                break;
            }
            case 'e':
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 'e');

    return 0;
}
