#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- Clase Paciente ---
class Paciente {
private:
    int id;
    string nombre;
    string apellido;

public:
    Paciente(int id, const string& nombre, const string& apellido)
        : id(id), nombre(nombre), apellido(apellido) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }

    void mostrarDatos() const {
        cout << "ID: " << id << endl;
        cout << "Nombre: " << nombre << " " << apellido << endl;
    }
};

// --- Estructura para entradas del historial ---
struct EntradaHistorial {
    string fecha;
    string descripcion;
};

// --- Clase Historial ---
class Historial {
private:
    vector<EntradaHistorial> entradas;

public:
    void agregarEntrada(const string& fecha, const string& descripcion) {
        entradas.push_back({fecha, descripcion});
    }

    void mostrarHistorial() const {
        cout << "\nHistorial Médico:\n";
        for (const auto& entrada : entradas) {
            cout << "- [" << entrada.fecha << "] " << entrada.descripcion << endl;
        }
    }
};

// --- Programa principal ---
int main() {
    Paciente paciente1(1, "Juan", "Pérez");
    Historial historial1;

    paciente1.mostrarDatos();

    historial1.agregarEntrada("2025-04-28", "Consulta general. Todo en orden.");
    historial1.agregarEntrada("2025-05-15", "Diagnóstico de hipertensión. Medicación recetada.");

    historial1.mostrarHistorial();

    return 0;
}
