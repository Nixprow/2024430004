#include <iostream>
using namespace std;

const int MAX = 100; //Se plantea esta variable de forma constante, ya que no cambia su valor y además es un maximo simbolico

struct Pila {
    int elementos[MAX];
    int tope;
    int capacidad;
};

//Cree una funcion que se encargue de inicializar la pila con el proposito de crear un objeto del tipo pila
Pila inicializar(int capacidad) {
    Pila p;
    p.tope = 0;
    p.capacidad = capacidad;
    return p;
}

// Verificar si está vacía en una primera instancia
bool pilaVacia(Pila p) {
    if (p.tope == 0){
        return true;
    } else {
        return false;
    }
}

// Verificar si está llena
bool pilaLlena(Pila p) {
    if (p.tope == p.capacidad) {
        return true;
    } else {
        return false;
    }
}

// Esta funcion hace el push como tal ;3
Pila push(Pila p, int dato) {
    if (pilaLlena(p)) {
        cout << "Pila llena" << endl;
    } else {
        p.elementos[p.tope] = dato;
        p.tope++;
    }
    return p;
}

// Esta funcion hace basicamente el pop o eliminar
Pila pop(Pila p) {
    if (pilaVacia(p)) {
        cout << "Pila vacía" << endl;
    } else {
        p.tope--;
        cout << "Elemento eliminado: " << p.elementos[p.tope] << endl;
    }
    return p;
}

// Cree otra funcion que se encargue de mostrar la pila 
void mostrar(Pila p) {
    if (pilaVacia(p)) {
        cout << "Pila vacía" << endl;
    } else {
        cout << "Contenido de la pila:" << endl;
        for (int i = p.tope - 1; i >= 0; i--) {
            cout << "|" << p.elementos[i] << "|" << endl;
        }
    }
}

int main() {
    int tam;
    cout << "Ingrese tamaño máximo de la pila: ";
    cin >> tam;

    if (tam > MAX) { //Aqui se encarga de verificar que el maximo no se supere
        cout << "El tamaño no puede superar " << MAX << endl;
        return 1;
    }

    Pila miPila = inicializar(tam);
    //Aqui se hace un menú de toda la vida
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Agregar / Push" << endl;
        cout << "2. Remover / Pop" << endl;
        cout << "3. Ver pila" << endl;
        cout << "0. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

        if (opcion == 1) {
            int valor;
            cout << "Ingrese valor: ";
            cin >> valor;
            miPila = push(miPila, valor);
        }
        else if (opcion == 2) {
            miPila = pop(miPila);
        }
        else if (opcion == 3) {
            mostrar(miPila);
        }
        else if (opcion == 0) {
            cout << "Salir" << endl;
        }
        else {
            cout << "Opción no válida" << endl;
        }
    }

    return 0;
}
