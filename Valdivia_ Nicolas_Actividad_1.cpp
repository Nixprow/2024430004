#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

// inicializa un vector de strings con espacios
void inicializar_vector_caracter(string *vector, int n) {
    int col;
  
    // recorre el vector.
    for (col=0; col<n; col++) {
        vector[col] = " ";
    }
}

// imprime un vector. recibe el vector como un puntero.
void imprimir_vector_caracter(string *vector, int n) {
    cout << endl;
    for (int i=0; i<n; i++) {
        cout << "vector[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

// inicializa matriz NxN y recibe un puntero a la matriz.
void inicializar_matriz_enteros(int **matriz, int n) {
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            matriz[fila][col] = -1; // -1 representa que no hay conexión
        }
    }
}
//Funcion que muestra la matriz en cuestion
void imprimir_matriz(int **matriz, int n) {
    cout << endl;
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            cout << matriz[fila][col] << " ";
        }
        cout << endl;
    }
}

// Función para asignar nombres automáticos a los nodos (a, b, c, ...)
void asignar_nombres_nodos(string *V, int n) {
    for (int i = 0; i < n; i++) {
        V[i] = 'a' + i; // 'a' + 0 = 'a', 'a' + 1 = 'b', etc.
    }
}

// Función para buscar el índice de un nodo por su nombre
int buscar_indice_caracter(string *V, char caracter, int n) {
    for (int i = 0; i < n; i++) {
        if (V[i][0] == caracter) {
            return i; // Retorna la posición si encuentra el caracter
        }
    }
    return -1; // Retorna -1 si no encuentra el caracter
}

// Función para liberar la memoria de la matriz
void liberar_memoria(int **matriz, int n) {
    if (matriz == nullptr) {
        return;
    }
    
    // Liberar primero cada fila de la matriz
    for(int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    

    delete[] matriz;
}

// Función para generar el grafo con Graphvizz
void generar_grafo_original(int **matriz, string *V, int n) {
    string outputDot = "grafo_original.dot";
    
    ofstream outfile;
    outfile.open(outputDot);
    if (!outfile.is_open()) {
        cout << "Error: No se pudo crear el archivo " << outputDot << endl;
        return;
    }

    outfile << "graph G {\n";
    outfile << "graph [rankdir=LR]\n";
    outfile << "node [style=filled fillcolor=\"#00ff005f\"]\n";
    
    // Escribir conexiones (solo una vez por arista para grafos no dirigidos)
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) { // Comenzar desde i para evitar duplicados
            if (i != j && matriz[i][j] != -1) {
                outfile << "  " << V[i] << " -- " << V[j] << " [label=" << matriz[i][j] << "];\n";
            }
        }
    }

    outfile << "}\n";
    outfile.close();

    cout << "- Archivo Graphviz del grafo original generado: " << outputDot << endl;

    
    string comando = "dot -Tpng " + outputDot + " -o grafo_original.png";
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "- Imagen del grafo original generada: grafo_original.png" << endl;
    } else {
        cout << "- Error al generar imagen del grafo original" << endl;
    }
}

// Función para generar el grafo de con el costo minimo
void generar_grafo_minimo(int **matriz, string *V, int n) {
    string outputDot = "grafo_minimo.dot";
    
    ofstream outfile;
    outfile.open(outputDot);
    if (!outfile.is_open()) {
        cout << "Error: No se pudo crear el archivo " << outputDot << endl;
        return;
    }


    outfile << "graph G {\n";
    outfile << "graph [rankdir=LR]\n";
    outfile << "node [style=filled fillcolor=\"#00ff005f\"]\n";
    
    // El for describe las conexiones del árbol mínimo
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) { // Comenzar desde i para evitar duplicados
            if (i != j && matriz[i][j] != -1) {
                outfile << "  " << V[i] << " -- " << V[j] << " [label=" << matriz[i][j] << "];\n";
            }
        }
    }

    outfile << "}\n";
    outfile.close();

    cout << "- Archivo Graphviz del grafo mínimo generado: " << outputDot << endl;


    string comando = "dot -Tpng " + outputDot + " -o grafo_minimo.png";
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "-Imagen del grafo mínimo generada: grafo_minimo.png" << endl;
    } else {
        cout << "-Error al generar imagen del grafo mínimo" << endl;
    }
}

// Algoritmo de Prim para encontrar el árbol abarcador de costo mínimo
void aplicar_prim(string *V, int **M, int n) {
    // Conjunto L para almacenar las aristas del árbol mínimo
    int **L = new int*[n];
    for(int i = 0; i < n; i++) {
        L[i] = new int[n];
        for(int j = 0; j < n; j++) {
            L[i][j] = -1; // Inicializar L con -1 (sin conexión)
        }
    }
    
    // Arreglo para marcar vértices incluidos en el árbol
    bool *incluido = new bool[n];
    for(int i = 0; i < n; i++) {
        incluido[i] = false;
    }
    
    // Incluir el primer vértice en el árbol
    incluido[0] = true;
    int aristas_incluidas = 0;
    int costo_total = 0;
    
    cout << "\n -- APLICANDO ALGORITMO DE PRIM --" << endl;
    cout << "Conjunto L (aristas del árbol mínimo):" << endl;
    
    // Mientras no se incluyan todos los vértices
    while (aristas_incluidas < n - 1) {
        int min_peso = 9999; // Valor grande para encontrar el mínimo (luego cambiará)
        int u = -1, v = -1; // Variables para almacenar los vértices de la arista mínima
        
        // Buscar la arista de menor peso que conecte un vértice incluido con uno no incluido
        for (int i = 0; i < n; i++) {
            if (incluido[i]) {
                for (int j = 0; j < n; j++) {
                    if (!incluido[j] && M[i][j] != -1) {
                        if (M[i][j] < min_peso) {
                            min_peso = M[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }
        }
        
        if (u != -1 && v != -1) {
            // Se busca incluir la arista en el valor minimo
            L[u][v] = min_peso;
            L[v][u] = min_peso; // Grafo no dirigido
            incluido[v] = true;
            costo_total += min_peso;
            aristas_incluidas++;
            
            cout << "Arista incluida: " << V[u] << " -- " << V[v] << " [peso: " << min_peso << "]" << endl;
        }
    }
    
    cout << "\nCosto total del árbol abarcador mínimo: " << costo_total << endl;
    

    cout << "\nMatriz L (árbol de costo mínimo):" << endl;
    imprimir_matriz(L, n);

    generar_grafo_original(M, V, n);
    generar_grafo_minimo(L, V, n);
    
    // Liberar memoria
    for(int i = 0; i < n; i++) {
        delete[] L[i];
    }
    delete[] L;
    delete[] incluido;
}

int main(int argc, char **argv) {
    // número de elementos.
    int n;


    if (argc<2) {
        cout << "Uso: \n./Actividad1 n (donde n es el numero de nodos)" << endl;
        return -1;
    }


    n = atoi(argv[1]);
    if (n <= 2) {
        cout << "Error: n debe ser mayor a 2" << endl;
        return -1;
    }

    
    string V[n];
    inicializar_vector_caracter(V, n);
    asignar_nombres_nodos(V, n);
    
    cout << "Nodos del grafo:";
    imprimir_vector_caracter(V, n);

    // crea matriz nxn de enteros.
    int **matriz;
    matriz = new int*[n];
    for(int i=0; i<n; i++)
        matriz[i] = new int[n];

    inicializar_matriz_enteros(matriz, n);
    

    cout << "\nIngrese la matriz de adyacencia " << n << "x" << n << ":" << endl;
    cout << "Recuerda que es un grafo no dirigido (matriz simétrica)" << endl;
    cout << "Use -1 para indicar que no hay conexión entre nodos" << endl;
    
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            if (fila == col) {
                matriz[fila][col] = 0; // Diagonal principal es 0
            } else {
                cout << "Peso " << V[fila] << " -- " << V[col] << ": ";
                cin >> matriz[fila][col];
                // Para grafos no dirigidos, hacer la matriz simétrica
                if (matriz[fila][col] != -1) {
                    matriz[col][fila] = matriz[fila][col];
                }
            }
        }
    }

    cout << "\nMatriz de adyacencia ingresada:" << endl;
    
    imprimir_matriz(matriz, n);
    aplicar_prim(V, matriz, n);
    liberar_memoria(matriz, n);

    return 0;
}