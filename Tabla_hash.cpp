#include <iostream>
#include <unordered_map>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

using namespace std;

struct Paciente {
    int id;
    string nombre;
    int edad;
    string diagnostico;
};

unordered_map<int, Paciente> tablaHashPorID;
unordered_map<string, Paciente> tablaHashPorNombre;

void cargarPacientesDesdeBD() {
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> conn(driver->connect("tcp://127.0.0.1:3306", "root", "tu_contraseña"));
        conn->setSchema("hospital");

        unique_ptr<sql::Statement> stmt(conn->createStatement());
        unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM pacientes"));

        while (res->next()) {
            Paciente p;
            p.id = res->getInt("id");
            p.nombre = res->getString("nombre");
            p.edad = res->getInt("edad");
            p.diagnostico = res->getString("diagnostico");

            tablaHashPorID[p.id] = p;
            tablaHashPorNombre[p.nombre] = p;
        }

        cout << "Pacientes cargados correctamente.\n";

    } catch (sql::SQLException &e) {
        cerr << "Error al conectar a MySQL: " << e.what() << endl;
    }
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
    cargarPacientesDesdeBD();

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
