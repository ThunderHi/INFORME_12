#include <iostream> //para usar entrada/salida estandar
#include <fstream> //"filestream" para manejar archivos en c++
#include <string> //manejo de cadenas de texto
#include <vector> //para usar contenedores dinamicos
#include <algorithm> //para usar algoritmos de la STL
using namespace std;

// Interfaz para mostrar información de empleados
class Interfaz {
public:
    virtual void mostrarInformacion() const = 0; // Método virtual puro
    virtual double calcularSalario() const = 0;  // Método virtual puro
    virtual void guardar(ofstream& out) const = 0;  // Método virtual puro para guardar
    virtual ~Interfaz() {} // Destructor virtual
};

// Clase Base para empleados
class Empleado : public Interfaz {
protected:
    string nombre;
    double salarioBase;     // salario base acorde a su rol
    string fechaContratacion;
    static double tarifaHora; // Atributo estático
public:
    // Constructor de clase base
    Empleado(string nom, double salario, string fecha) :
        nombre(nom), salarioBase(salario), fechaContratacion(fecha) {}
    // Método estático para establecer la tarifa por hora
    static void setTarifaHora(double tarifa) {
        tarifaHora = tarifa;
    }
    // Método para mostrar información básica del empleado
    void mostrarInformacion() const override {
        cout << "Nombre: " << nombre << endl;
        cout << "Salario Base: " << salarioBase << endl;
        cout << "Fecha de Contratacion: " << fechaContratacion << endl;
    }
    // Método para guardar información básica del empleado
    void guardar(ofstream& out) const override {
        out << nombre << "," << salarioBase << "," << fechaContratacion << ",";
    }
    virtual ~Empleado() {} // Destructor virtual
};

// Inicialización del atributo estático
double Empleado::tarifaHora = 0.0;

// Clase derivada Gerente
class Gerente : public Empleado {
private:
    double bono; // Adicional a su sueldo
public:
    // Constructor de clase Gerente
    Gerente(string nom, double salario, string fecha, double b) :
        Empleado(nom, salario, fecha), bono(b) {}
    // Sobreescritura de método
    double calcularSalario() const override {
        return salarioBase + bono;
    }
    // Sobreescritura y refinamiento de método
    void mostrarInformacion() const override {
        Empleado::mostrarInformacion();
        cout << "Bono: " << bono << endl;
    }
    // Método para guardar información
    void guardar(ofstream& out) const override {
        out << "Gerente,";
        Empleado::guardar(out);
        out << bono << endl;
    }
    // Método getNombre() para la búsqueda
    string getNombre() const {
        return nombre;
    }
};

// Clase derivada Desarrollador
class Desarrollador : public Empleado {
private:
    int horasExtras; // Hora fuera de horario normal
public:
    // Constructor de clase Desarrollador
    Desarrollador(string nom, double salario, string fecha, int horas) :
        Empleado(nom, salario, fecha), horasExtras(horas) {}
    // Sobreescritura de método
    double calcularSalario() const override {
        return salarioBase + (horasExtras * tarifaHora);
    }
    // Sobreescritura y refinamiento de método
    void mostrarInformacion() const override {
        Empleado::mostrarInformacion();
        cout << "Horas Extras: " << horasExtras << endl;
        cout << "Tarifa por Hora Extra: " << tarifaHora << endl;
    }
    // Método para guardar información
    void guardar(ofstream& out) const override {
        out << "Desarrollador,";
        Empleado::guardar(out);
        out << horasExtras << endl;
    }
    // Método getNombre() para la búsqueda
    string getNombre() const {
        return nombre;
    }
};

// Clase derivada Diseñador
class Disenador : public Empleado {
private:
    double porcentajeComision; // Ganancia por ventas
    double ventasTotales; // Ventas realizadas en soles

public:
    // Constructor de Diseñador
    Disenador(string nom, double salario, string fecha, double comision, double ventas) :
        Empleado(nom, salario, fecha), porcentajeComision(comision), ventasTotales(ventas) {}
    // Sobreescritura de método
    double calcularSalario() const override {
        return salarioBase + (ventasTotales * porcentajeComision);
    }
    // Sobreescritura y refinamiento de método
    void mostrarInformacion() const override {
        Empleado::mostrarInformacion();
        cout << "Porcentaje de Comision: " << porcentajeComision << endl;
        cout << "Ventas Totales: " << ventasTotales << endl;
    }
    // Método para guardar información
    void guardar(ofstream& out) const override {
        out << "Disenador,";
        Empleado::guardar(out);
        out << porcentajeComision << "," << ventasTotales << endl;
    }
    // Método getNombre() para la búsqueda
    string getNombre() const {
        return nombre;
    }
};

// Plantilla de clase Departamento
template <typename T>
class Departamento {
private:
    vector<T*> empleados; // Usamos vector en lugar de puntero a arreglo
// El vector encargado de almacenar punteros a objetos de tipo T 
// (donde T puede ser cualquier tipo que herede de Empleado, como Gerente, Desarrollador, o Disenador)
public:
    // Constructor por defecto
    Departamento() {}

    // Método para agregar un empleado
    void agregarEmpleado(T* empleado) {
        empleados.push_back(empleado);
    }

    // Método para eliminar un empleado por índice
    void eliminarEmpleado(int indice) {
        if (indice >= 0 && indice < empleados.size()) {
            delete empleados[indice];
            empleados.erase(empleados.begin() + indice);
        } else {
            cout << "Índice fuera de rango." << endl;
        }
    }

    // La lambda dentro de buscarEmpleado define cómo find_if busca un empleado por nombre
    // Lambda sirve para definir funciones anónimas localmente, útiles en algoritmos y operaciones funcionales
    // Las lambdas se usan donde se necesitan funciones, como en algoritmos de la STL como find_if
    // Método para buscar un empleado por nombre
    T* buscarEmpleado(const string& nombre) const {
        //uso de algoritmo de busqueda find_if
        auto it = find_if(empleados.begin(), empleados.end(), [&nombre](T* emp) {
        // auto deduce automáticamente el tipo de variable según la inicialización proporcionada
        // Ya sea int, double, char 
        // find_if busca empleado por nombre en vector usando lambda
            return emp->getNombre() == nombre;
        });
        if (it != empleados.end()) {
            return *it;
        }
        // return *it; devuelve el puntero al empleado encontrado por nombre
        // Ya sea gerente, diseñador o desarrollador

        return nullptr;
        // Nullptr indica que un puntero no apunta a ninguna dirección de memoria válida
        // Si no encuentra, devuelve nullptr
    }

    // Método para listar todos los empleados
    void listarEmpleados() const {
        for (size_t i = 0; i < empleados.size(); ++i) {
            cout << "Indice: " << i + 1 << endl;
            empleados[i]->mostrarInformacion();
            cout << "Salario Calculado: " << empleados[i]->calcularSalario() << endl << endl;
        }
    }

    // Método para guardar todos los empleados a un archivo
    void guardar(ofstream& out) const {
        out << empleados.size() << endl;  // Guardar el número de empleados
        for (const auto& emp : empleados) {
        // auto deduce tipo de elemento en empleados, iterando y llamando guardar(out) a cada uno
            emp->guardar(out);
        }
    }

    // Destructor
    ~Departamento() {
        for (auto emp : empleados) {
            delete emp;
        }
    }
};

// Prototipo del menú
void menu() {
    cout << "+========Recursos Humanos========+\n";
    cout << "1. Agregar Empleado\n";
    cout << "2. Eliminar Empleado\n";
    cout << "3. Buscar Empleado\n";
    cout << "4. Listar Empleados\n";
    cout << "5. Guardar Empleados a Archivo\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    double Thora;
    try {
        // Lectura de la tarifa por hora
        cout << "Ingrese tarifa en soles de hora: ";
        cin >> Thora;
        if (cin.fail()) {
        // cin.fail() Detecta errores de tipo al leer datos con cin
            throw runtime_error("Error: entrada no válida para tarifa por hora.");
        }
        cin.ignore();  // Limpiar el buffer de entrada

        Empleado::setTarifaHora(Thora);

        // Creación de departamentos
        Departamento<Gerente> deptoGerentes;
        Departamento<Desarrollador> deptoDesarrolladores;
        Departamento<Disenador> deptoDisenadores;

        int opcion;
        do {
            menu();
            cin >> opcion;
            cin.ignore(); // Limpiar el buffer de entrada
            // cin.ignore() Descarta caracteres adicionales en el buffer de entrada de cin
            switch (opcion) {
                case 1: {
                    cout << "Tipo de Empleado (1. Gerente, 2. Desarrollador, 3. Disenador): ";
                    int tipo;
                    cin >> tipo;
                    cin.ignore();
                    // cin.ignore() Descarta caracteres adicionales en el buffer de entrada de cin

                    string nombre, fecha;
                    double salario;

                    cout << "Nombre: ";
                    getline(cin, nombre);
                    // getline() Lee una línea completa de texto desde cin, incluyendo espacios en blanco
                    cout << "Salario Base: ";
                    cin >> salario;
                    cin.ignore();
                    // cin.ignore() Descarta caracteres adicionales en el buffer de entrada de cin
                    cout << "Fecha de Contratacion (YYYY-MM-DD): ";
                    getline(cin, fecha);
                    // getline() Lee una línea completa de texto desde cin, incluyendo espacios en blanco

                    if (tipo == 1) {
                        double bono;
                        cout << "Bono: ";
                        cin >> bono;
                        deptoGerentes.agregarEmpleado(new Gerente(nombre, salario, fecha, bono));
                    } else if (tipo == 2) {
                        int horasExtras;
                        cout << "Horas Extras: ";
                        cin >> horasExtras;
                        deptoDesarrolladores.agregarEmpleado(new Desarrollador(nombre, salario, fecha, horasExtras));
                    } else if (tipo == 3) {
                        double comision, ventas;
                        cout << "Porcentaje de Comision: ";
                        cin >> comision;
                        cout << "Ventas Totales: ";
                        cin >> ventas;
                        deptoDisenadores.agregarEmpleado(new Disenador(nombre, salario, fecha, comision, ventas));
                    } else {
                        cout << "Tipo de empleado no válido." << endl;
                    }
                    break;
                }
                case 2: {
                    cout << "Departamento (1. Gerentes, 2. Desarrolladores, 3. Disenadores): ";
                    int depto;
                    cin >> depto;
                    int indice;
                    cout << "Indice del empleado a eliminar: ";
                    cin >> indice;

                    if (depto == 1) {
                        deptoGerentes.eliminarEmpleado(indice - 1);
                    } else if (depto == 2) {
                        deptoDesarrolladores.eliminarEmpleado(indice - 1);
                    } else if (depto == 3) {
                        deptoDisenadores.eliminarEmpleado(indice - 1);
                    } else {
                        cout << "Departamento no válido." << endl;
                    }
                    break;
                }
                case 3: {
                    cout << "Departamento (1. Gerentes, 2. Desarrolladores, 3. Disenadores): ";
                    int depto;
                    cin >> depto;
                    cin.ignore();
                    // cin.ignore() Descarta caracteres adicionales en el buffer de entrada de cin
                    string nombre;
                    cout << "Nombre del empleado a buscar: ";
                    getline(cin, nombre);
                    // getline() Lee una línea completa de texto desde cin, incluyendo espacios en blanco

                    if (depto == 1) {
                        Gerente* g = deptoGerentes.buscarEmpleado(nombre);
                        if (g) {
                            g->mostrarInformacion();
                            cout << "Salario Calculado: " << g->calcularSalario() << endl;
                        } else {
                            cout << "Gerente no encontrado." << endl;
                        }
                    } else if (depto == 2) {
                        Desarrollador* d = deptoDesarrolladores.buscarEmpleado(nombre);
                        if (d) {
                            d->mostrarInformacion();
                            cout << "Salario Calculado: " << d->calcularSalario() << endl;
                        } else {
                            cout << "Desarrollador no encontrado." << endl;
                        }
                    } else if (depto == 3) {
                        Disenador* d = deptoDisenadores.buscarEmpleado(nombre);
                        if (d) {
                            d->mostrarInformacion();
                            cout << "Salario Calculado: " << d->calcularSalario() << endl;
                        } else {
                            cout << "Diseñador no encontrado." << endl;
                        }
                    } else {
                        cout << "Departamento no válido." << endl;
                    }
                    break;
                }
                case 4: {
                    cout << "Departamento (1. Gerentes, 2. Desarrolladores, 3. Disenadores): ";
                    int depto;
                    cin >> depto;

                    if (depto == 1) {
                        deptoGerentes.listarEmpleados();
                    } else if (depto == 2) {
                        deptoDesarrolladores.listarEmpleados();
                    } else if (depto == 3) {
                        deptoDisenadores.listarEmpleados();
                    } else {
                        cout << "Departamento no válido." << endl;
                    }
                    break;
                }
                case 5: {
                    cout << "Guardando información de empleados a archivo..." << endl;
                    ofstream outFile("C:\\Users\\Thunder\\Documents\\Thunder\\Practicando\\empleados.txt");
                    if (!outFile) {
                        throw runtime_error("Error al abrir el archivo de salida.");
                    }
                    deptoGerentes.guardar(outFile);
                    deptoDesarrolladores.guardar(outFile);
                    deptoDisenadores.guardar(outFile);
                    outFile.close();
                    cout << "Información guardada correctamente." << endl;
                    break;
                }
                case 6:
                    cout << "Saliendo..." << endl;
                    break;
                default:
                    cout << "Opción no válida." << endl;
            }
        } while (opcion != 6);
    } catch (const exception& e) {
        cerr << "Excepción capturada: " << e.what() << endl;
    }

    return 0;
}
