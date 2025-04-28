#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Paciente {
    int id;
    string nombre;
    string apellido;
    string fechaNacimiento;
    int edad;
    string diagnostico;
    string genero;
    string direccion;
    string telefono;
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

        // Suponiendo que el CSV tiene los campos en el mismo orden que tu tabla:
        getline(ss, item, ',');
        p.id = stoi(item);
        getline(ss, p.nombre, ',');
        getline(ss, p.apellido, ',');
        getline(ss, p.fechaNacimiento, ',');
        getline(ss, item, ',');
        p.edad = stoi(item);
        getline(ss, p.diagnostico, ',');
        getline(ss, p.genero, ',');
        getline(ss, p.direccion, ',');
        getline(ss, p.telefono, ',');

        tablaHashPorID[p.id] = p;
        tablaHashPorNombre[p.nombre] = p;
    }

    archivo.close();
    cout << "Datos cargados desde archivo correctamente.\n";
}

void registrarPaciente(const Paciente& p) {
    tablaHashPorID[p.id] = p;
    tablaHashPorNombre[p.nombre] = p;
    cout << "Paciente " << p.nombre << " " << p.apellido << " registrado correctamente.\n";
}

void exportarJSON(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    archivo << "[\n";
    bool primero = true;

    for (const auto& par : tablaHashPorID) {
        const Paciente& p = par.second;
        if (!primero) archivo << ",\n";
        archivo << "  {\n";
        archivo << "    \"id\": " << p.id << ",\n";
        archivo << "    \"nombre\": \"" << p.nombre << "\",\n";
        archivo << "    \"apellido\": \"" << p.apellido << "\",\n";
        archivo << "    \"fechaNacimiento\": \"" << p.fechaNacimiento << "\",\n";
        archivo << "    \"edad\": " << p.edad << ",\n";
        archivo << "    \"diagnostico\": \"" << p.diagnostico << "\",\n";
        archivo << "    \"genero\": \"" << p.genero << "\",\n";
        archivo << "    \"direccion\": \"" << p.direccion << "\",\n";
        archivo << "    \"telefono\": \"" << p.telefono << "\"\n";
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
    Paciente nuevoPaciente = {
        12345, "Juan", "Pérez", "1979-05-20", 45,
        "Hipertensión", "Masculino", "Calle Falsa 123", "123456789"
    };
    registrarPaciente(nuevoPaciente);

    exportarJSON("pacientes.json");

    return 0;
}
