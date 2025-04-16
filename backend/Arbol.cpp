#include <iostream>
#include <string>
using namespace std;
struct Nodo {
    string nombre;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo(string n) {
        nombre = n;
        izquierda = nullptr;
        derecha = nullptr;
    }
};

class ArbolBinario {
private:
    Nodo* raiz;
    void insertar(Nodo*& nodo, string nombre) {
        if (nodo == nullptr) {
            nodo = new Nodo(nombre);
        } else if (nombre < nodo->nombre) {
            insertar(nodo->izquierda, nombre);
        } else {
            insertar(nodo->derecha, nombre);
        }
    }
    void inorden(Nodo* nodo) {
        if (nodo != nullptr) {
            inorden(nodo->izquierda);
            cout << nodo->nombre << endl;
            inorden(nodo->derecha);
        }
    }
public:
    ArbolBinario() {
        raiz = nullptr;
    }
    void insertar(string nombre) {
        insertar(raiz, nombre);
    }
    void mostrarInorden() {
        cout << "Pacientes (ordenados):" << endl;
        inorden(raiz);
    }
};

int main() {
    ArbolBinario arbol;
    arbol.insertar("Juan Pérez");
    arbol.insertar("Ana Martínez");
    arbol.insertar("Carlos Ramírez");
    arbol.insertar("Beatriz Gómez");
    arbol.insertar("Zulema Torres");
    arbol.mostrarInorden();

    return 0;
}
