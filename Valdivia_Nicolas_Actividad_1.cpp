#include <iostream>

using namespace std;

//Primero se determina el tamaño a utilizar con respecto a la tabla 
const int TAMANO = 20;

// Nodo para las listas a usar en un futuro
struct Nodo {
    int dato;
    Nodo* siguiente;
};

// La funcion de hash simple divide y toma residuo
int hashSimple(int key) {
    return key % TAMANO;
}

// Función hash secundaria para doble hash
int hashSec(int key) {
    return 5 - (key % 5);  // Un número fijo menos el módulo
}

//Primero prueba lineal
void insertarLineal(int tabla[], int key) {
    int pos = hashSimple(key);
    int pos_original = pos;
    int intentos = 0;
    bool colision = false;
    
    cout << "Insertando " << key << " -> Posicion inicial: " << pos << endl;
    
    // Buscar posición vacía
    while (tabla[pos] != -1) {
        if (!colision) {
            cout << "COLISIONN en posicion " << pos << endl;
            colision = true;
        }
        
        intentos++;
        pos = (pos_original + intentos) % TAMANO;  // Avanza de 1 en 1
        
        // Si dio vuelta completa
        if (pos == pos_original) {
            cout << "Tabla llena No se pudo insertar " << key << endl;
            return;
        }
    }
    
    // Insertar el valor
    tabla[pos] = key;
    
    if (colision) {
        cout << "Resuelto en posicion " << pos << " (intentos: " << intentos << ")" << endl;
    } else {
        cout << "Insertado sin colisiones" << endl;
    }
}

// Segundo Prueba Cuadrática
void insertarCuadratico(int tabla[], int key) {
    int pos = hashSimple(key);
    int pos_original = pos;
    int intentos = 0;
    bool colision = false;
    
    cout << "Insertando " << key << " -> Posicion inicial: " << pos << endl;
    
    // Buscar posición vacía
    while (tabla[pos] != -1) {
        if (!colision) {
            cout << "COLISIONN en posicion " << pos << endl;
            colision = true;
        }
        
        intentos++;
        // Avanza cuadráticamente: 1, 4, 9, 16...
        pos = (pos_original + intentos * intentos) % TAMANO;
        
        if (intentos > TAMANO) {
            cout << "Demasiados intentos para " << key << endl;
            return;
        }
    }
    
    // Insertar el valor
    tabla[pos] = key;
    
    if (colision) {
        cout << "Insertado en posicion " << pos << " (saltos: " << intentos * intentos << ")" << endl;
    } else {
        cout << "Insertado sin colisiones" << endl;
    }
}

// Doble Hash
void insertarDobleHash(int tabla[], int key) {
    int pos = hashSimple(key);
    int pos_original = pos;
    int intentos = 0;
    bool colision = false;
    
    cout << "Insertando " << key << " -> Posicion inicial: " << pos << endl;
    
    // Buscar posición vacía
    while (tabla[pos] != -1) {
        if (!colision) {
            cout << "COLISION en posicion " << pos << endl;
            colision = true;
        }
        
        intentos++;
        // Usa segunda función hash
        int paso = hashSec(key);
        pos = (pos_original + intentos * paso) % TAMANO;
        
        if (intentos > TAMANO) {
            cout << "Demasiados intentos para " << key << endl;
            return;
        }
    }
    
    // Insertar el valor
    tabla[pos] = key;
    
    if (colision) {
        cout << "Insertado en posicion " << pos << " (paso: " << hashSec(key) << ")" << endl;
    } else {
        cout << "Insertado sin colisiones" << endl;
    }
}

// Luego seguimos con encadenamiento
void insertarEncadenamiento(Nodo* lista[], int key) {
    int pos = hashSimple(key);
    
    cout << "Insertando " << key << " -> Posicion: " << pos << endl;
    
    // Se crea un nuevo nodo
    Nodo* nuevo = new Nodo;
    nuevo->dato = key;
    nuevo->siguiente = nullptr;
    
    if (lista[pos] == nullptr) {
        // Primer elemento en la posicion
        lista[pos] = nuevo;
        cout << "Primer elemento en esta posicion" << endl;
    } else {
        // Ya hay elementos, agregar al final
        cout << "COLISION - agregando a la lista existente" << endl;
        
        Nodo* actual = lista[pos];
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// Mostrar tabla para los metodos aplicados
void mostrarTabla(int tabla[]) {
    cout << "TABLA ACTUAL: [";
    for (int i = 0; i < TAMANO; i++) {
        if (tabla[i] == -1) {
            cout << " -";
        } else {
            cout << " " << tabla[i];
        }
    }
    cout << " ]" << endl << endl;
}

// Se muestran las listas para en enlazamiento
void mostrarListas(Nodo* lista[]) {
    cout << "LISTAS ACTUALES:" << endl;
    for (int i = 0; i < TAMANO; i++) {
        cout << "Posicion " << i << ": ";
        
        Nodo* actual = lista[i];
        if (actual == nullptr) {
            cout << "VACIO";
        } else {
            while (actual != nullptr) {
                cout << actual->dato;
                if (actual->siguiente != nullptr) {
                    cout << " -> ";
                }
                actual = actual->siguiente;
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Búsqueda para los distintos metodos
void buscarEnTabla(int tabla[], int key, char metodo) {
    cout << "Buscando " << key << "..." << endl;
    
    int pos = hashSimple(key);
    int pos_original = pos;
    int intentos = 0;
    
    while (tabla[pos] != -1) {
        if (tabla[pos] == key) {
            cout << "ENCONTRADO en posicion " << pos;
            
            if (intentos > 0) {
                cout << " (colision original en " << pos_original;
                cout << ", intentos: " << intentos << ")";
            }
            cout << endl;
            return;
        }
        
        intentos++;
        
        // Avanzar según el método
        if (metodo == 'L') {
            pos = (pos_original + intentos) % TAMANO;
        } else if (metodo == 'C') {
            pos = (pos_original + intentos * intentos) % TAMANO;
        } else if (metodo == 'D') {
            int paso = hashSec(key);
            pos = (pos_original + intentos * paso) % TAMANO;
        }
        
        if (intentos > TAMANO) break;
    }
    
    cout << "NO ENCONTRADO" << endl;
}

// Búsqueda para metodo de enlazamiento
void buscarEnListas(Nodo* lista[], int key) {
    cout << "Buscando " << key << "..." << endl;
    
    int pos = hashSimple(key);
    int pos_en_lista = 0;
    
    Nodo* actual = lista[pos];
    
    while (actual != nullptr) {
        if (actual->dato == key) {
            cout << "ENCONTRADO en lista " << pos;
            cout << " (posicion " << pos_en_lista << " en la lista)" << endl;
            return;
        }
        actual = actual->siguiente;
        pos_en_lista++;
    }
    
    cout << "NO ENCONTRADO" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: ./hash L|C|D|E" << endl;
        cout << "L = Lineal, C = Cuadratico, D = Doble Hash, E = Encadenamiento" << endl;
        return 1;
    }
    
    char metodo = argv[1][0];
    
    if (metodo != 'L' && metodo != 'C' && metodo != 'D' && metodo != 'E') {
        cout << "Metodo debe ser L, C, D o E" << endl;
        return 1;
    }
    
    cout << "=== TABLA HASH - METODO ";
    switch(metodo) {
        case 'L': cout << "LINEAL"; break;
        case 'C': cout << "CUADRATICO"; break;
        case 'D': cout << "DOBLE HASH"; break;
        case 'E': cout << "ENCADENAMIENTO"; break;
    }
    cout << " ===" << endl;
    
    // Datos a insertar
    int datos[] = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};
    int num_datos = 15;
    

    int tabla[TAMANO];        // Para L, C, D
    Nodo* listas[TAMANO];     // Para E
    
    if (metodo == 'E') {
        for (int i = 0; i < TAMANO; i++) {
            listas[i] = nullptr;
        }
    } else {
        for (int i = 0; i < TAMANO; i++) {
            tabla[i] = -1;  // -1 = vacío
        }
    }
    

    cout << "\n--- INSERTANDO DATOS ---" << endl;
    for (int i = 0; i < num_datos; i++) {
        int key = datos[i];
        
        if (metodo == 'L') {
            insertarLineal(tabla, key);
            mostrarTabla(tabla);
        } else if (metodo == 'C') {
            insertarCuadratico(tabla, key);
            mostrarTabla(tabla);
        } else if (metodo == 'D') {
            insertarDobleHash(tabla, key);
            mostrarTabla(tabla);
        } else if (metodo == 'E') {
            insertarEncadenamiento(listas, key);
            mostrarListas(listas);
        }
    }
    

    cout << "\n--- BUSCANDO DATOS ---" << endl;
    
    //Se tratan de buscar valores que existen menos el 100
    int buscar[] = {42, 59, 28, 100};  
    
    for (int i = 0; i < 4; i++) {
        int key = buscar[i];
        
        if (metodo == 'E') {
            buscarEnListas(listas, key);
        } else {
            buscarEnTabla(tabla, key, metodo);
        }
    }
    
    cout << "\n=== FIN DEL PROGRAMA ===" << endl;
    
    return 0;
}