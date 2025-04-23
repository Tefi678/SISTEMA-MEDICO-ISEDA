#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

struct Paciente {
    int id;
    string nombre;
    int edad;
    string diagnostico;
};

unordered_map<int, Paciente> tablaHashPorID;
unordered_map<string, Paciente> tablaHashPorNombre;

void cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string item;
        Paciente p;

        getline(ss, item, ',');
        p.id = stoi(item);
        getline(ss, p.nombre, ',');
        getline(ss, item, ',');
        p.edad = stoi(item);
        getline(ss, p.diagnostico, ',');

        tablaHashPorID[p.id] = p;
        tablaHashPorNombre[p.nombre] = p;
    }

    archivo.close();
    cout << "Datos cargados desde archivo correctamente.\n";
}

void buscarPorID(int id) {
    if (tablaHashPorID.find(id) != tablaHashPorID.end()) {
        Paciente p = tablaHashPorID[id];
        cout << "Paciente encontrado: " << p.nombre << ", Edad: " << p.edad << ", Diagnóstico: " << p.diagnostico << endl;
    } else {
        cout << "Paciente con ID " << id << " no encontrado.\n";
    }
}

void buscarPorNombre(const string& nombre) {
    if (tablaHashPorNombre.find(nombre) != tablaHashPorNombre.end()) {
        Paciente p = tablaHashPorNombre[nombre];
        cout << "Paciente encontrado: ID " << p.id << ", Edad: " << p.edad << ", Diagnóstico: " << p.diagnostico << endl;
    } else {
        cout << "Paciente con nombre '" << nombre << "' no encontrado.\n";
    }
}

int main() {
    cargarDesdeArchivo("pacientes.csv");

    int opcion;
    while (true) {
        cout << "\n1. Buscar por ID\n2. Buscar por Nombre\n3. Salir\nOpción: ";
        cin >> opcion;

        if (opcion == 1) {
            int id;
            cout << "Ingrese el ID del paciente: ";
            cin >> id;
            buscarPorID(id);
        } else if (opcion == 2) {
            string nombre;
            cout << "Ingrese el nombre del paciente: ";
            cin.ignore();
            getline(cin, nombre);
            buscarPorNombre(nombre);
        } else if (opcion == 3) {
            break;
        } else {
            cout << "Opción inválida.\n";
        }
    }

    return 0;
}
