#include <iostream>
#include <cstdlib> // para atoi
using namespace std;

//En este codigo hice uso de punteros, ya que se habla de los args y tal y al aparecer punteros los utilicé en este codigo
const int MAX_N = 100; // máximo contenedores por pila, determinado como constante, ya que no tendrá ningun cambio
const int MAX_M = 20;  // máximo de pilas

struct Pila {
    int elementos[MAX_N];
    int tope;
    int capacidad;
};

// Esta funcion es similar a la del codigo pasado solo que en este hago uso de punteros con el fin de trabajar con listas dinamicas
void inicializar(Pila* p, int capacidad) {
    p->tope = 0;
    p->capacidad = capacidad;
}

bool pilaVacia(Pila* p) {
    if (p->tope == 0) {
        return true;
    } else {
        return false;
    }
}


bool pilaLlena(Pila* p) {
    if (p->tope == p->capacidad) {
        return true;
    } else {
        return false;
    }
}


//Hace lo mismo que en el codigo pasado solo que aqui se trabaja con punteros
void push(Pila* p, int dato) {
    if (pilaLlena(p)) {
        cout << "Pila llena, no se puede agregar " << dato << endl;
    } else {
        p->elementos[p->tope] = dato;
        p->tope++;
    }
}
//Lo mismo que el codigo pasado
int pop(Pila* p) {
    if (pilaVacia(p)) {
        cout << "Pila vacía, no se puede remover" << endl;
        return -1;
    } else {
        p->tope--;
        return p->elementos[p->tope];
    }
}
//Hace lo mismo que el codigo pasado
void mostrar(Pila* p) {
    if (pilaVacia(p)) {
        cout << "[VACIA]" << endl;
    } else {
        for (int i = p->tope - 1; i >= 0; i--) {
            cout << "|" << p->elementos[i] << "|" << endl;
        }
    }
}

// Esta es la funcion clave del codigo
void retirarContenedor(Pila* pilas, int m, int id) {
    bool encontrado = false;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < pilas[i].tope; j++) {
            if (pilas[i].elementos[j] == id) {
                cout << "Contenedor " << id << " encontrado en pila " << i+1 << endl;

                // mover los que están arriba
                while (pilas[i].elementos[pilas[i].tope - 1] != id) {
                    int temporal = pop(&pilas[i]);

                    // Esta funcion busca otra pila
                    bool movido = false;
                    for (int k = 0; k < m; k++) {
                        if (k != i && !pilaLlena(&pilas[k])) {
                            push(&pilas[k], temporal);
                            cout << "Se movió contenedor " << temporal
                                 << " desde pila " << i+1 << " a pila " << k+1 << endl;
                            movido = true;
                            break;
                        }
                    }
                    if (!movido) {
                        cout << "No hay espacio para mover el contenedor " << temporal << endl;
                        return;
                    }
                }

                // Ahora se encarga de eliminar
                int eliminado = pop(&pilas[i]);
                cout << "Contenedor " << eliminado << " retirado con éxito." << endl;

                encontrado = true;
                break;
            }
        }
        if (encontrado) break;
    }

    if (!encontrado) {
        cout << "Contenedor " << id << " no encontrado." << endl;
    }
}

int main(int argc, char* argv[]) {
    // Validación de argumentos
    if (argc < 3) {
        cout << "Uso: ./programa <n> <m>" << endl;
        return 1;
    }

    int n = atoi(argv[1]); // altura máxima de cada pila
    int m = atoi(argv[2]); // número de pilas

    if (n > MAX_N || m > MAX_M) {
        cout << "Valores demasiado grandes." << endl;
        return 1;
    }

    // Crear pilas
    Pila pilas[MAX_M];
    for (int i = 0; i < m; i++) {
        inicializar(&pilas[i], n);
    }

    int opcion, valor;

    while (true) {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Ingresar contenedor" << endl;
        cout << "2. Retirar contenedor" << endl;
        cout << "3. Ver pilas" << endl;
        cout << "0. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Ingrese ID del contenedor: ";
            cin >> valor;
            bool agregado = false;
            for (int i = 0; i < m; i++) {
                if (!pilaLlena(&pilas[i])) {
                    push(&pilas[i], valor);
                    cout << "Contenedor " << valor << " agregado a pila " << i+1 << endl;
                    agregado = true;
                    break;
                }
            }
            if (!agregado) {
                cout << "Todas las pilas están llenas." << endl;
            }
        }
        else if (opcion == 2) {
            cout << "Ingrese ID a retirar: ";
            cin >> valor;
            retirarContenedor(pilas, m, valor);
        }
        else if (opcion == 3) {
            for (int i = 0; i < m; i++) {
                cout << "\nPila " << i+1 << ":" << endl;
                mostrar(&pilas[i]);
            }
        }
        else if (opcion == 0) {
            cout << "Salir" << endl;
            break; // terminar el bucle
        }
        else {
            cout << "Opción no válida" << endl;
        }
    }

    return 0;
}
