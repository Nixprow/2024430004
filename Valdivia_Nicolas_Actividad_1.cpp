#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

//La metodologia a utilizar será listas sobre listas
void inicializar_matriz_enteros(int **matriz, int n){
    for (int fila=0;fila<n;fila++){ //En este caso la variable fila, tomaria el valor que tiende a tomar i
        for (int col=0;col<n;col++){
            matriz[fila][col] = -1; //En caso de que sea -1 será que no hay conexion o el infinito que se utiliza en dijkstra para determinar que no hay conexion entre los vertices
        }
    }
}

//Esta funcion se encargaria de mostrar la matriz anteriormente creada
void imprimir_matriz(int **matriz, int n){
    cout<<"\n";
    for (int fila = 0; fila<n;fila++){
        for(int col=0;col<n;col++){
            cout<<matriz[fila][col]<< " "; //Esta linea se encarga de imprimir cada elemento de la matriz
        }
        cout<<"\n";
    }
}

void imprimir_vector_entero(int *vector, int n){
    cout <<"D[] = [";
    for (int i=0;i<n;i++){
        if(vector[i]==9999){//En este caso el numero 9999, simularia el infinito en las operaciones correspondientes a dijkstra
            cout<<"INFINITO"; // Por lo cual se escribe que es infinito
        } else {
            cout << vector[i]; //Imprime la distancia

        }
        if (i<n -1){
            cout<<",";
        }
    }
    cout<<"]"<<endl;
}

int buscar_indice_caracter(string *V, char caracter,int n){
    for(int i=0;i<n;i++){
        if (V[i][0] == caracter){
            return i; //En caso de que se encuentre el caracter que buscamos, se retorna la posicion buscada
        }
        
    }
    return -1; //Este -1 representa el que no existe la posicion a buscar
}

void aplicar_dijkstra(string *V,int **M,int n, int vertice_o){
    int *D = new int[n]; //Este arreglo se encarga de almacenar las distancias minimas
    bool *S = new bool[n]; //Y este marca los vertices ya visitados

    for (int i =0;i<n;i++){ 
        D[i]= M[vertice_o][i]; //Esta linea se encarga de copiar las distancias desde el origen
        if(D[i]== -1 && i!=vertice_o){ //En caso de que no haya conexion y si no es el origen, se le asignará el valor de infinito que lo represento con un 9999

            D[i]= 9999;
        }
        S[i]= false; //Esto marca a todos como no visitados
    }
    D[vertice_o] = 0; //Esto marca que la distancia hacia el mismo vertice (osea desde A hasta A) es 0
    S[vertice_o] = true; //Marca el origen como un punto ya visitado

    cout<<"Aplicando algoritmo de Dijkstra..."<<endl;
    cout<<"Vertice origen: "<<V[vertice_o]<<endl;
    cout<<"Estado inicial del arreglo D[]:";
    imprimir_vector_entero(D,n); //Muestra el estado inicial

    for(int count=0;count<n-1;count++){//Itera n-1 veces (ya que no se toma en consideracion el origen)
        int u =-1; //Variable asignada para el vertice a visitar
        int min_distancia= 9999; //Variable para la distancia minima (Esta luego cambiará)

        for(int i=0;i<n;i++){ //Este for recorre todos los vertices
            if(!S[i] && D[i]<min_distancia){
                min_distancia= D[i]; //Cambia el valor de la distancia minima
                u=i; //Esta variable se encarga de guardar el indice del vertice
                
            }

        }

        if(u==-1) break; //Si no hay vertices alcanzables, termina

        S[u]= true;
        cout<<"Visitando vertice: "<<V[u]<<" (distancia: "<< D[u]<<")"<<endl;

        for(int v=0;v<n;v++){ //Esto recorre todos los vertices
            if(!S[v] && M[u][v]!= -1){ //Si no está visitado y hay conexion, calcula la nueva distancia

                int nueva_distancia= D[u]+ M[u][v]; //Esta variable representa el calculo para buscar el minimo, visto en clases
                if(nueva_distancia< D[v] ){
                    cout<<" Actualizando "<<V[v]<<": "<<D[v]<<" ->" <<nueva_distancia<<endl;
                    D[v]= nueva_distancia; //Actualiza la distancia minima
                }
            }
        }

        cout<<" Estado actual de D[]:";
        imprimir_vector_entero(D,n);


    } 

    cout<<"Resultados"<<endl;
    cout<<"Distancias minimas desde"<<V[vertice_o]<< ":"<<endl;
        for(int i=0; i<n; i++){
            if(D[i]== 9999){
                cout<<"  "<<V[vertice_o]<<" ->"<<V[i]<<": No alcanzable"<<endl;

            } else {
                cout<<"  "<<V[vertice_o]<<" ->"<<V[i]<<D[i]<< endl;

            }

        }

    cout << "\nContenido final del arreglo D[]:";
    imprimir_vector_entero(D, n);
    
    // Libera la memoria reservada para los arreglos
    delete[] D;
    delete[] S;
}

// Función para liberar la memoria de la matriz y el vector de nodos
void liberar_memoria(int **matriz, string *V, int n) {
    if (matriz == nullptr) {
        return;
    }
    
    // libera primero cada fila de la matriz
    for(int i = 0; i < n; i++) {
        delete[] matriz[i];    // Se libera la memoria de cada fila
    }
    
    delete[] matriz;
    
    delete[] V;
}

void generar_grafo_graphviz(int **matriz, string *V, int n) {
    string outputDot = "grafo.dot"; 
    string outputPng = "grafo.png"; 
    
    //Sintaxis para crear el archivo.dot
    ofstream outfile;
    outfile.open(outputDot);
    if (!outfile.is_open()) {                      // Si no pudo abrir el archivo
        cout << "Error: No se pudo crear el archivo " << outputDot << endl;
        return;                                    // Sale de la función
    }

    
    outfile << "digraph G {\n";                  
    outfile << "graph [rankdir=LR]\n";            
    outfile << "node [style=filled fillcolor=\"#00ff005f\"]\n";  
    
    
    for (int i = 0; i < n; i++) {                 // Recorre cada nodo origen
        for (int j = 0; j < n; j++) {             // Recorre cada nodo destino
            if (i != j && matriz[i][j] != -1) {   // Si hay conexión válida (no diagonal)
                outfile << V[i] << " -> " << V[j] << " [label=" << matriz[i][j] << "];\n";
            }                                     // Escribe: origen->destino [label=peso];
        }
    }

    outfile << "}\n";                             // Cierra la definición del grafo
    outfile.close();                              // Cierra el archivo

    cout << "+ Archivo Graphviz generado: " << outputDot << endl;

    
    string comando = "dot -Tpng " + outputDot + " -o " + outputPng;
    int resultado = system(comando.c_str());      // Ejecuta el comando en el sistema

    // Verifica si Graphviz funcionó correctamente
    if (resultado == 0) {
        cout << "+ Imagen del grafo generada: " << outputPng << endl;
    } else {
        cout << "+ Error: Graphviz no pudo generar la imagen" << endl;
        cout << "+ Instale Graphviz con: sudo apt-get install graphviz" << endl;
    }
}


int main(int argc, char **argv) {
    
    if (argc < 2) {                               // Si no hay suficientes argumentos
        cout << "Uso: ./Actividad1 (n)" << endl;
        cout << "Donde n es un entero mayor a 2" << endl;
        return -1;                                 // Termina el programa con error
    }
    

    int n = atoi(argv[1]);                        // Convierte string a entero
    if (n <= 2) {                                 // Si el número es muy pequeño
        cout << "Error: n debe ser mayor a 2" << endl;
        return -1;                                 // Termina el programa con error
    }
    
    
    string *V = new string[n];                    // Reserva memoria para n nodos
    for (int i = 0; i < n; i++) {                 // Para cada nodo
        V[i] = 'a' + i;                           // Asigna letras: 'a'+0='a', 'a'+1='b', etc.
    }
    
    cout << "Nodos del grafo: ";
    for (int i = 0; i < n; i++) {                 // Imprime todos los nodos
        cout << V[i] << " ";
    }
    cout << endl;
    

    int **matriz;
    matriz = new int*[n];                         // Crea array de punteros a filas
    for(int i = 0; i < n; i++) {                  // Para cada fila
        matriz[i] = new int[n];                   // Crea la fila con n columnas
    }
    
    inicializar_matriz_enteros(matriz, n);        // Inicializa matriz con -1
    

    cout << "\nIngrese la matriz de adyacencia " << n << "x" << n << ":" << endl;
    cout << "Use -1 para indicar que no hay conexion entre nodos" << endl;
    
    for (int fila = 0; fila < n; fila++) {        // Recorre cada fila
        for (int col = 0; col < n; col++) {       // Recorre cada columna
            if (fila == col) {                    // Si es la diagonal principal
                matriz[fila][col] = 0;            // Distancia a sí mismo es 0
            } else {                              // Si no es la diagonal
                cout << "Distancia " << V[fila] << " -> " << V[col] << ": ";
                cin >> matriz[fila][col];         // Lee la distancia del usuario
            }
        }
    }

    cout << "\nMatriz de adyacencia ingresada:" << endl;
    imprimir_matriz(matriz, n);
    
    
    char vertice_origen_char;
    cout << "\nIngrese el vertice origen: ";
    cin >> vertice_origen_char;                   // Lee un caracter (a, b, c, ...)
    
    
    int vertice_origen = buscar_indice_caracter(V, vertice_origen_char, n);
    if (vertice_origen == -1) {                   // Si retorna -1, no existe
        cout << "Error: vertice origen no encontrado" << endl;
        liberar_memoria(matriz, V, n);            // Libera memoria antes de terminar
        return -1;                                 // Termina el programa con error
    }
    

    aplicar_dijkstra(V, matriz, n, vertice_origen);
    generar_grafo_graphviz(matriz, V, n);
    liberar_memoria(matriz, V, n);
    
    return 0;                                    
}