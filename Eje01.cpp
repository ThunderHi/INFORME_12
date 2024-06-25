#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Producto {
    string descripcion;
    int cantidad;
};

class Inventario {
private:
    map<string, Producto> productos;

public:
    void agregarProducto(const string& codigo, const string& descripcion, int cantidad) {
        productos[codigo] = {descripcion, cantidad};
    }

    void actualizarCantidad(const string& codigo, int cantidad) {
        if (productos.find(codigo) != productos.end()) {
            productos[codigo].cantidad = cantidad;
        } else {
            cout << "Producto no encontrado.\n";
        }
    }

    void buscarProducto(const string& codigo) const {
        auto it = productos.find(codigo);
        if (it != productos.end()) {
            cout<<"Codigo: "<<it->first 
                <<", Descripcion: "<<it->second.descripcion 
                <<", Cantidad: "<<it->second.cantidad<<'\n';
        } else {
            cout<<"Producto no encontrado.\n";
        }
    }

    void mostrarProductosOrdenados() const {
        vector<pair<string, Producto>> productosVec(productos.begin(), productos.end());
        sort(productosVec.begin(), productosVec.end(), 
                  [](const auto& a, const auto& b) {
                      return a.second.descripcion < b.second.descripcion;
                  });
        
        for (const auto& p : productosVec) {
            cout<<"Codigo: "<<p.first 
                <<", Descripcion: "<<p.second.descripcion 
                <<", Cantidad: "<<p.second.cantidad<<'\n';
        }
    }
};

void mostrarMenu() {
    cout<<"1. Agregar producto\n"
        <<"2. Actualizar cantidad\n"
        <<"3. Buscar producto\n"
        <<"4. Mostrar productos ordenados\n"
        <<"5. Salir\n";
}

int main() {
    Inventario inventario;
    int opcion;
    string codigo, descripcion;
    int cantidad;

    do {
        mostrarMenu();
        cout<<"Seleccione una opcion: ";
        cin>>opcion;

        switch (opcion) {
            case 1:
                cout<<"Ingrese el código del producto: ";
                cin>>codigo;
                cout<<"Ingrese la descripción del producto: ";
                cin.ignore(); // Ignorar el newline que quedó en el buffer
                getline(std::cin, descripcion);
                cout<<"Ingrese la cantidad: ";
                cin>>cantidad;
                inventario.agregarProducto(codigo, descripcion, cantidad);
                break;
            case 2:
                cout<<"Ingrese el código del producto: ";
                cin>>codigo;
                cout<<"Ingrese la nueva cantidad: ";
                cin>>cantidad;
                inventario.actualizarCantidad(codigo, cantidad);
                break;
            case 3:
                cout<<"Ingrese el código del producto: ";
                cin>>codigo;
                inventario.buscarProducto(codigo);
                break;
            case 4:
                inventario.mostrarProductosOrdenados();
                break;
            case 5:
                cout<<"Saliendo...\n";
                break;
            default:
                cout<<"Opción no válida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}
