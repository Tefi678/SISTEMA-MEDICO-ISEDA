#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>

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

void registrarPaciente(const Paciente& p) {
    tablaHashPorID[p.id] = p;
    tablaHashPorNombre[p.nombre] = p;
    cout << "Paciente " << p.nombre << " registrado correctamente.\n";
}

void exportarJSON(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    archivo << "[\n";
    bool primero = true;

    for (const auto& par : tablaHashPorID) {
        const Paciente& p = par.second;
        if (!primero) archivo << ",\n";
        archivo << "  {\n";
        archivo << "    \"nombre\": \"" << p.nombre << "\",\n";
        archivo << "    \"dni\": " << p.id << ",\n";
        archivo << "    \"telefono\": \"Desconocido\",\n";
        archivo << "    \"direccion\": \"Desconocida\"\n";
        archivo << "  }";
        primero = false;
    }

    archivo << "\n]";
    archivo.close();
    cout << "Exportado a JSON correctamente.\n";
}

int main() {
    cargarDesdeArchivo("pacientes.csv");

    // Ejemplo de cómo registrar un nuevo paciente
    Paciente nuevoPaciente = {12345, "Juan Pérez", 45, "Hipertensión"};
    registrarPaciente(nuevoPaciente);

    exportarJSON("pacientes.json");

    return 0;
}
