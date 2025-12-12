#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int tamAlfabeto = 4;
const string alfabeto = "ACGT"; 
//Se crea una matriz para analizar U
int** matrizU = nullptr;
int GAP = -2;            
const int LIMITE_VISUALIZACION = 80;

//No quise usar cmath para el max o el min, así que hice funciones basadas en if para poder simularlas de alguna manera

int max3(int a, int b, int c) {
    int max_val = a;
    if (b > max_val) max_val = b;
    if (c > max_val) max_val = c;
    return max_val;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}
//Esta funcion reemplazaria lo que haria atoi de la funcion cstdlib, por temas de comodidad para mi, esto transforma "-2" del gap por ejemplo en el valor entero de -2
int stringToInt(const char* str) {
    int res = 0;
    int sign = 1;
    int i = 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    for (; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            res = res * 10 + (str[i] - '0');
        } else {
            return 0; 
        }
    }
    return sign * res;
}


//Liberar memoria asignada en punteros para la matriz U
void liberarMatrizU() {
    if (matrizU != nullptr) {
        for (int i = 0; i < tamAlfabeto; i++) {
            delete[] matrizU[i];
        }
        delete[] matrizU;
        matrizU = nullptr;
    }
}
//Esto sirve para verificar si la letra ingresada pertenece al alfabeto (en este caso ACGT) y si no pertenece pues se devuelve -1 (error)
int indiceEnAlfabeto(char c) {
    for (int i = 0; i < tamAlfabeto; i++) {
        if (alfabeto[i] == c) return i;
    }
    return -1;
}
//Esto verifica la posicion dentro de la matriz U
int obtenerPuntaje(char a, char b) {
    int idxA = indiceEnAlfabeto(a);
    int idxB = indiceEnAlfabeto(b);
    if (idxA == -1 || idxB == -1) return 0;
    return matrizU[idxA][idxB];
}
//Esto lee la secuencia
string leerSecuencia(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string secuencia = "";
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de secuencia " << nombreArchivo << endl;
        return "";
    }
    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea[0] == '>') {
            continue;
        }
        for (char c : linea) {
            if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
                secuencia += c;
            }
        }
    }
    archivo.close();
    return secuencia;
}

//Esto lee la matriz U (añadir al ppt)
bool leerMatrizU(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de matriz U " << nombreArchivo << endl;
        return false;
    }
    //Aqui se asigna memoria para las filas que presente la matriz U
    matrizU = new int*[tamAlfabeto];
    //Aqui se asignan los espacios para las columnas de la matriz
    for (int i = 0; i < tamAlfabeto; i++) {
        matrizU[i] = new int[tamAlfabeto];
    }
    //Aqui se omiten la primera linea de la matriz
    string temp;
    getline(archivo, temp);
    //Se recorren las filas y las columnas de la matriz
    for (int i = 0; i < tamAlfabeto; i++) {
        char letra_fila;
        if (!(archivo >> letra_fila)) {
            cerr << "Error: Formato de matriz incorrecto (faltan letras de fila)." << endl;
            liberarMatrizU();
            return false;
        }
        //El siguiente ciclo for se encarga de leer la matriz y asignar sus valores guardandolos en la variable matriz
        for (int j = 0; j < tamAlfabeto; j++) {
            if (!(archivo >> matrizU[i][j])) {
                cerr << "Error: Formato de matriz incompleto (faltan valores)." << endl;
                liberarMatrizU();
                return false;
            }
        }
    }
    archivo.close();
    return true;
}


//Funcion que hace todo el calculo de needleman wunsch(añadir ppt)
void needlemanWunsch(const string& sec1, const string& sec2,string& alineado1, string& alineado2, int& puntaje) {
    //Se lee el largo de las secuencias
    int n = sec1.length(); 
    int m = sec2.length(); 
    //Se crea la nueva matriz dinamica (que es con la que vamos a trabajar)
    int** F = new int*[n + 1];
    for (int i = 0; i <= n; i++) {
        F[i] = new int[m + 1];
    }
    //Al alinear 2 secuencias vacias da 0
    F[0][0] = 0;
    //Rellena las primeras filas y columnas con la penalizacion el gap 
    for (int i = 1; i <= n; i++) F[i][0] = F[i-1][0] + GAP;
    for (int j = 1; j <= m; j++) F[0][j] = F[0][j-1] + GAP;
    //Viaja considerando listas sobre listas rellenando con los valores y 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int match_mismatch = F[i-1][j-1] + obtenerPuntaje(sec1[i-1], sec2[j-1]);
            int arriba = F[i-1][j] + GAP;
            int izq = F[i][j-1] + GAP;
            F[i][j] = max3(match_mismatch, arriba, izq);
        }
    }
    //El max se almacena en la siguiente variable
    puntaje = F[n][m]; 
    //Estas 4 lineas siguientes inicializan en la esquina inferior derecha de la matriz y las variables de la alineacion vacias
    int i = n; 
    int j = m;
    alineado1 = "";
    alineado2 = "";
    
    while (i > 0 || j > 0) {
        //Si el puntaje viene del diagonal se alinea con el correspondiente viendo si hay match o mismatch
        if (i > 0 && j > 0 && F[i][j] == F[i-1][j-1] + obtenerPuntaje(sec1[i-1], sec2[j-1])) {
            alineado1 = sec1[i-1] + alineado1;
            alineado2 = sec2[j-1] + alineado2;
            i--; 
            j--;
        }
        //Si no viene del diagonal, viene del de arriba y se le asigna un "-" la secuencia 2
        else if (i > 0 && F[i][j] == F[i-1][j] + GAP) {
            alineado1 = sec1[i-1] + alineado1;
            alineado2 = "-" + alineado2;
            i--;
        }
        //Si no viene de arriba viene de la izq y por lo tanto se le asigna un "-" a la secuencia 1
        else if (j > 0 && F[i][j] == F[i][j-1] + GAP) {
            alineado1 = "-" + alineado1;
            alineado2 = sec2[j-1] + alineado2;
            j--;
        }
        //Lo siguientes son algo preventivos, ya que no son tan necesarios pero si cumplen regular el movimiento si es que llegan a un borde antes de llegar al origen
        //Por lo cual si se acaba una secuencia se alinea todo el resto con gaps
        else if (i > 0) {
             alineado1 = sec1[i-1] + alineado1;
             alineado2 = "-" + alineado2;
             i--;
        }
        else if (j > 0) { 
             alineado1 = "-" + alineado1;
             alineado2 = sec2[j-1] + alineado2;
             j--;
        }
    }
    //Se libera memoria
    for (int i = 0; i <= n; i++) {
        delete[] F[i];
    }
    delete[] F;
}



//Aqui se crean las marcas para el alineado en la terminal
string generarMarcas(const string& alineado1, const string& alineado2) {
    string marcas = "";
    for (size_t k = 0; k < alineado1.length(); ++k) {
        if (alineado1[k] != '-' && alineado2[k] != '-' && alineado1[k] == alineado2[k]) {
            marcas += "|"; 
        } else {
            marcas += " "; 
        }
    }
    return marcas;
}


//Lo que hace la siguiente funcion es mostrar el alineamiento por bloques, si supera las 80 pb crea otro bloque abajo para seguir visualizando
void mostrarAlineamientoPorBloques(const string& alineado1, const string& alineado2,const string& marcas) {
    
    int longitud = alineado1.length();
    int bloques = (longitud + LIMITE_VISUALIZACION - 1) / LIMITE_VISUALIZACION;
    
    cout << "\nALINEAMIENTO (Bloques de " << LIMITE_VISUALIZACION << " caracteres):"<<endl;
    
    for (int bloque = 0; bloque < bloques; bloque++) {
        int inicio = bloque * LIMITE_VISUALIZACION;
        int fin = min(inicio + LIMITE_VISUALIZACION, longitud);
        
        cout << "\nBloque " << (bloque + 1) << "/" << bloques 
             << " (posiciones " << inicio + 1 << "-" << fin << "):\n";
        
      
        cout << alineado1.substr(inicio, fin - inicio) << endl; 
        
       
        cout << marcas.substr(inicio, fin - inicio) << endl; 
        
      
        cout << alineado2.substr(inicio, fin - inicio) << endl; 
    }
}

//Calcula estadisticas segundo los matches, mismatches o gaps
void calcularEstadisticas(const string& alineado1, const string& alineado2,int& matches, int& mismatches, int& gaps, double& similitud_porcentaje) {
    //las 3 variables se inicializan en 0
    matches = mismatches = gaps = 0;
    //Se lee la longitud guiando en el alineado 1
    int longitud = alineado1.length();

    //luego tenemos 3 casos
    for (int i = 0; i < longitud; i++) {
        //EL primero es que haya "-" en cualquiera de las 2 alineaciones lo cual seria un gap
        //El segundo es q si son iguales hay match y  si no pues mismatch
        if (alineado1[i] == '-' || alineado2[i] == '-') {
            gaps++;
        } else if (alineado1[i] == alineado2[i]) {
            matches++;
        } else {
            mismatches++;
        }
    }
    
    similitud_porcentaje = (longitud > 0) ? (100.0 * matches / longitud) : 0.0;
}


void generarGraphviz(const string& alineado1, const string& alineado2, int puntaje, const string& archivo1, const string& archivo2, double similitud) {
    //Se crea el alineamiento.dot
    ofstream archivo("alineamiento.dot");
    if (!archivo.is_open()) {
        cerr << "Error al crear alineamiento.dot" << endl;
        return;
    }
    //Esto secciona el graphviz, ya que si la secuencia es extremadamente larga no la genera
    int mostrar = min(150, alineado1.length());
    string alineado1_short = alineado1.substr(0, mostrar);
    string alineado2_short = alineado2.substr(0, mostrar);
    string marcas_short = generarMarcas(alineado1_short, alineado2_short);
    //Si el valor del largo de la secuencia es mayor al valor determinado por mostrar, mostrará ... en el alineamiento
    if (alineado1.length() > mostrar) {
        alineado1_short += " (...)";
        alineado2_short += " (...)";
        marcas_short += " (...)";
    }
    
    //Hay una etiqueta basica que dice estadisticas sobre el alineamiento en cuestion
    string etiqueta_info = 
        "Puntaje Máximo: " + to_string(puntaje) + "\n" +
        "Similitud: " + to_string(similitud).substr(0, to_string(similitud).find('.') + 3) + "%\n" + 
        "Longitud Total: " + to_string(alineado1.length()) + " bases\n" +
        "Gap Penalty (V): " + to_string(GAP) + "\n" +
        "-------------------------------------\n"; 
        
    string etiqueta_alineamiento = 
        "S: " + alineado1_short + "\n" + 
        "   " + marcas_short + "\n" + 
        "T: " + alineado2_short;

    
    archivo << "digraph AlineamientoNeedlemanWunsch {" << endl;
    archivo << "  rankdir=TB;" << endl;
    
    archivo << "  node [shape=box, fontname=\"Courier\", fontsize=12, style=\"filled\", fillcolor=\"#F0F0F0\"];" << endl;
    
    
    archivo << "  resultado [label=\"" 
            << etiqueta_info 
            << etiqueta_alineamiento 
            << "\", fillcolor=\"#ADD8E6\"];" << endl;
    
    archivo << "}" << endl;
    archivo.close();
    
    cout << "\n Archivo Graphviz generado" << endl;
    cout << " Para generar el diagrama PNG:" << endl;
    cout << "$ dot -Tpng alineamiento.dot -o alineamiento.png" << endl;
}

//Esta funcion posee relacion como guia para el uso adecuado de la ejecucion del codigo
void mostrarAyuda() {
    cout << "\nUSO: ./programa -C1 archivo_sec_S -C2 archivo_sec_T -U archivo_matriz -V valor_gap" << endl;
    cout << "\nEjemplo: ./programa -C1 sec1.txt -C2 sec2.txt -U U.txt -V -2" << endl;
}


int main(int argc, char* argv[]) {
    
    cout << "===================" << endl;
    cout << " NEEDLEMAN-WUNSCH" << endl;
    cout << "===================" << endl;
    
    if (argc < 9) {
        mostrarAyuda();
        return 1;
    }
    
    string archivo1, archivo2, archivoMatriz;
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        
        if (arg == "-C1" && i + 1 < argc) {
            archivo1 = argv[++i];
        }
        else if (arg == "-C2" && i + 1 < argc) {
            archivo2 = argv[++i];
        }
        else if (arg == "-U" && i + 1 < argc) {
            archivoMatriz = argv[++i];
            if (!leerMatrizU(archivoMatriz)) {
                return 1;
            }
        }
        else if (arg == "-V" && i + 1 < argc) {
            GAP = stringToInt(argv[++i]); 
        }
    }
    
    if (archivo1.empty() || archivo2.empty() || matrizU == nullptr) {
        cerr << "Error: Faltan archivos de entrada o la matriz U no se cargó." << endl;
        liberarMatrizU();
        return 1;
    }
    
    string sec1 = leerSecuencia(archivo1);
    string sec2 = leerSecuencia(archivo2);

    if (sec1.empty() || sec2.empty()) {
        cerr << "Error: Una o ambas secuencias están vacías o son inválidas." << endl;
        liberarMatrizU();
        return 1;
    }
    
    cout << "\n-INFORMACIÓN DE ENTRADA-" << endl;
    cout << "Secuencia S (" << archivo1 << "): " << sec1.length() << " bases" << endl;
    cout << "Secuencia T (" << archivo2 << "): " << sec2.length() << " bases" << endl;
    cout << "Gap penalty (V): " << GAP << endl;
    
    cout << "\n-EJECUTANDO ALGORITMO-" << endl;
    
    string alineado1, alineado2;
    int puntaje;
    
    needlemanWunsch(sec1, sec2, alineado1, alineado2, puntaje);
    
    string marcas = generarMarcas(alineado1, alineado2);
    
    int matches, mismatches, gaps;
    double similitud;
    calcularEstadisticas(alineado1, alineado2, matches, mismatches, gaps, similitud);
    
    cout << "Alineamiento completado" << endl;
    cout << " Longitud del alineamiento: " << alineado1.length() << " caracteres" << endl;
    cout << " Puntaje óptimo: " << puntaje << endl;
    
    cout << "\n- ESTADÍSTICAS -" << endl;
    cout << "Matches: " << matches << endl;
    cout << "Mismatches: " << mismatches << endl;
    cout << "Gaps: " << gaps << endl;
    cout << "Similitud global: " << similitud << "%" << endl;
    

    if (alineado1.length() > LIMITE_VISUALIZACION) {
        mostrarAlineamientoPorBloques(alineado1, alineado2, marcas);
    } else {
        cout << "\n--ALINEAMIENTO COMPLETO--" << endl;
    
        cout << alineado1 << endl;
        cout << marcas << endl;
        cout << alineado2 << endl;
    }
    

    generarGraphviz(alineado1, alineado2, puntaje, archivo1, archivo2, similitud);
    
    liberarMatrizU();
    
    cout << "\n===================" << endl;
    cout << " Proceso completado" << endl;
    cout << "===================" << endl;
    
    return 0;
}