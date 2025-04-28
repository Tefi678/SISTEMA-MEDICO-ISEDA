#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdlib> // Para getenv
#include <sstream>

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

// Función para obtener el valor del campo de entrada HTTP POST
string obtenerCampoPost(const string& campo) {
    char* val = getenv(campo.c_str());
    return (val == nullptr) ? "" : string(val);
}

void registrarPaciente(const Paciente& p) {
    tablaHashPorID[p.id] = p;
    tablaHashPorNombre[p.nombre] = p;
    cout << "Paciente " << p.nombre << " " << p.apellido << " registrado correctamente.\n";
}

void responderFormulario() {
    // Contenido de la cabecera HTTP
    cout << "Content-type: text/html\n\n";
    cout << "<html><body>";

    // Obtener los datos del formulario a través de las variables de entorno
    string id_str = obtenerCampoPost("id");
    string nombre = obtenerCampoPost("nombre");
    string apellido = obtenerCampoPost("apellido");
    string fechaNacimiento = obtenerCampoPost("fecha_nacimiento");
    string edad_str = obtenerCampoPost("edad");
    string diagnostico = obtenerCampoPost("diagnostico");
    string genero = obtenerCampoPost("genero");
    string direccion = obtenerCampoPost("direccion");
    string telefono = obtenerCampoPost("telefono");

    if (id_str.empty() || nombre.empty() || apellido.empty() || edad_str.empty() || telefono.empty()) {
        cout << "<h1>Error: Faltan campos obligatorios.</h1>";
    } else {
        // Crear un nuevo paciente a partir de los datos recibidos
        int id = stoi(id_str);
        int edad = stoi(edad_str);
        
        Paciente nuevoPaciente = { id, nombre, apellido, fechaNacimiento, edad, diagnostico, genero, direccion, telefono };
        registrarPaciente(nuevoPaciente);

        // Responder con un mensaje de éxito
        cout << "<h1>Paciente registrado correctamente.</h1>";
    }

    cout << "</body></html>";
}

int main() {
    // Responder al formulario CGI
    responderFormulario();
    return 0;
}
