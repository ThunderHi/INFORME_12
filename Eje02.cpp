#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Evento {
    string fecha;
    set<string> asistentes; // Usamos un set para mantener los asistentes en orden alfabético
};

class GestorEventos {
private:
    map<string, Evento> eventos; // Mapa de nombre del evento a estructura de evento
    multimap<string, string> eventosPorFecha; // Mapa de fecha a nombre del evento

public:
    void agregarEvento(const string& nombre, const string& fecha) {
        eventos[nombre] = {fecha, {}};
        eventosPorFecha.insert({fecha, nombre});
    }

    void agregarAsistente(const string& nombre, const string& asistente) {
        if (eventos.find(nombre) != eventos.end()) {
            eventos[nombre].asistentes.insert(asistente);
        } else {
            cout<<"Evento no encontrado\n";
        }
    }

    void mostrarAsistentes(const string& nombre) const {
        auto it = eventos.find(nombre);
        if (it != eventos.end()) {
            cout<<"Asistentes al evento "<<nombre<<":\n";
            for (const auto& asistente : it->second.asistentes) {
                cout<<asistente<<'\n';
            }
        } else {
            cout<<"Evento no encontrado\n";
        }
    }

    void buscarEventosPorFecha(const string& fecha) const {
        auto rango = eventosPorFecha.equal_range(fecha);
        if (rango.first != rango.second) {
            cout<<"Eventos en la fecha "<<fecha<<":\n";
            for (auto it = rango.first; it != rango.second; ++it) {
                cout<<it->second<<'\n';
            }
        } else {
            cout<<"No se encontraron eventos en esa fecha\n";
        }
    }
};

void mostrarMenu() {
    cout<<"1. Agregar evento\n"
        <<"2. Agregar asistente a evento\n"
        <<"3. Mostrar asistentes de evento\n"
        <<"4. Buscar eventos por fecha\n"
        <<"5. Salir\n";
}

int main() {
    GestorEventos gestor;
    int opcion;
    string nombre, fecha, asistente;

    do {
        mostrarMenu();
        cout<<"Seleccione una opcion: ";
        cin>>opcion;

        switch (opcion) {
            case 1:
                cout<<"Ingrese el nombre del evento: ";
                cin.ignore(); // Ignorar el newline que quedó en el buffer
                getline(cin, nombre);
                cout<<"Ingrese la fecha del evento (YYYY-MM-DD): ";
                getline(cin, fecha);
                gestor.agregarEvento(nombre, fecha);
                break;
            case 2:
                cout<<"Ingrese el nombre del evento: ";
                cin.ignore();
                getline(cin, nombre);
                cout<<"Ingrese el nombre del asistente: ";
                getline(cin, asistente);
                gestor.agregarAsistente(nombre, asistente);
                break;
            case 3:
                cout<<"Ingrese el nombre del evento: ";
                cin.ignore();
                getline(cin, nombre);
                gestor.mostrarAsistentes(nombre);
                break;
            case 4:
                cout<<"Ingrese la fecha (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, fecha);
                gestor.buscarEventosPorFecha(fecha);
                break;
            case 5:
                cout<<"Saliendo...\n";
                break;
            default:
                cout<<"Opcion no valida Intente de nuevo\n";
                break;
        }
    } while (opcion != 5);
    return 0;
}
