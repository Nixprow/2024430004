#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
//Estructura del nodo, ya que en este trabajo se tratará como una cola 
struct Nodo{
    string resn;  //Nombre del aminoacido
    string resid; //El numero del residuo
    Nodo* siguiente; //Puntero al siguiente
};

struct Lista{
    Nodo* cabeza;
    Nodo* cola;
};

//Se inicia la lista (Toda esta se comienza en nulo)
void iniciarLista(Lista*& lista){
    lista = new Lista();
    lista->cabeza= nullptr;
    lista->cola = nullptr;

}
//Se verifica si es que la lista se encuentra vacia
bool listaVacia(Lista* lista){
    return lista->cabeza == nullptr;

}

//Se agrega residuo al final de la cola
void agregarResiduo(Lista* lista, string nombre,string numero){
    Nodo* nuevo = new Nodo(); //Aqui se crea un nuevo nodo
    nuevo->resn = nombre;
    nuevo->resid = numero;
    nuevo -> siguiente = nullptr;
    //Esto verifica dentro de la funcion de agregar residuo si es que la lista está vacia
    if (listaVacia(lista)){
        lista ->cabeza = nuevo;
        lista->cola = nuevo;
    } else {
        lista->cola->siguiente = nuevo;
        lista->cola = nuevo;
    }
    cout<<"Agregado: "<< nombre <<numero<<endl; //Este cout corrobora que se añadio el aa deseado :p"


}
//Muestra los residuos en la lista
void mostrarResiduos(Lista* lista){

    //Esto nuevamente verifica si la lista está vacia xd
    if (listaVacia(lista)){
        cout <<"Lista vacia"<<endl; //Mensaje para decir que la lista ta vacia
        return;
    }
    //Aqui se crea la lista de residuos xd
    cout<<"\n--- Lista de Residuos---"<<endl;
    Nodo* actual = lista ->cabeza;
    int cont= 1;

    while (actual != nullptr){

        cout<< cont <<". "<<actual->resn<<" "<< actual->resid<<endl;
        actual = actual->siguiente; //Esta linea avanza al siguiente nodo
        cont++;
    }
    
}
void cambiarResiduo(Lista* lista,int pos,string nuevo_nombre){
    if (listaVacia(lista) || pos < 1){
        cout <<"Posicion invalida"<<endl;
        return;
    }

    Nodo* actual = lista ->cabeza;
    int cont = 1;

    while (actual != nullptr && cont < pos) {
        actual = actual ->siguiente;    
        cont++; 
    }

    if (actual == nullptr){
        cout<<"Posicion invalida"<<endl;
        return;
    }

    cout<<"Cambiado: " <<actual ->resn <<" por " <<nuevo_nombre <<endl;
    actual ->resn = nuevo_nombre;   
}


void eliminarResiduo(Lista* lista, int pos){

    if (listaVacia(lista) || pos < 1){
        cout<<"Posicion invalida"<<endl;
        return;
    }

    Nodo* actual = lista->cabeza;
    Nodo* anterior = nullptr;
    int cont =1;

    if (pos == 1){
        lista ->cabeza = actual ->siguiente;

        if(lista->cabeza==nullptr){
            lista->cola = nullptr;
        }
        cout<<"Eliminado: "<<actual->resn<< actual->resid<<endl;
        delete actual;
        return;
    }
    while (actual != nullptr && cont<pos){
        anterior = actual;
        actual = actual->siguiente;
        cont++;
    }
    if(actual==nullptr){
        cout<<"Posicion Invalida"<<endl;
        return;
    }

    anterior->siguiente = actual->siguiente;

    if(actual==lista ->cola){
        lista->cola = anterior;
    }

    cout<<"Eliminado: "<<actual->resn << actual->resid<< endl;
    delete actual;
    
}

void leerArchivo(Lista* lista, string nombreArchivo){
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()){
        cout<<"No se pudo abrir: "<<nombreArchivo<<endl;
        return;
    }

    string linea;
    int total=0;

    while(getline(archivo, linea)){
        // Formato: LEU;A;   2
        // Buscar el primer punto y coma
        size_t pos1 = linea.find(';');
        if (pos1 == string::npos) continue;
        
        // Buscar el segundo punto y coma
        size_t pos2 = linea.find(';', pos1 + 1);
        if (pos2 == string::npos) continue;
        
        // Extraer nombre (antes del primer ;)
        string nombre = linea.substr(0, pos1);
        
        // Extraer número (después del segundo ;)
        string numero = linea.substr(pos2 + 1);
        
        // Limpiar espacios en el número
        size_t inicio_num = numero.find_first_not_of(" \t");
        size_t fin_num = numero.find_last_not_of(" \t");
        
        if (inicio_num != string::npos && fin_num != string::npos) {
            numero = numero.substr(inicio_num, fin_num - inicio_num + 1);
            
            if(!nombre.empty() && !numero.empty()){
                agregarResiduo(lista, nombre, numero);
                total++;
            }
        }
    }

    archivo.close(); 
    cout <<"Leidos "<<total <<" residuos"<<endl;

}
//Se implementa la funcion de liberar memoria de el laboratorio 1 pero esta vez adaptado a lo requerido
void liberarMemoria(Lista* lista) {
    Nodo* actual = lista->cabeza;  // Empieza desde el primer nodo
    
    
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;  
        delete actual;                        // Libera memoria del nodo actual
        actual = siguiente;                  
    }
    
    delete lista;  // Libera la estructura Lista principal
    cout << "Memoria liberada correctamente\n";
}
//Funcion para crear el graphviz
void crearGraphviz(Lista* lista, string nombreArchivo) {
    if (listaVacia(lista)) {
        cout << "Lista vacia, nada que exportar\n";
        return;
    }
    
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo crear: " << nombreArchivo << endl;
        return;
    }
    
    //Orientacion dada por el profesor
    archivo << "digraph G {\n";
    archivo << "rankdir = LR;\n"; 
    archivo << "node [style=filled fillcolor=yellow];\n\n";  
    
    //Aqui se escriben las conexiones
    Nodo* actual = lista->cabeza;
    while (actual != nullptr && actual->siguiente != nullptr) {
        archivo << actual->resn << actual->resid;
        archivo << " -> ";
        archivo << actual->siguiente->resn << actual->siguiente->resid;
        archivo << ";\n";
        actual = actual->siguiente;
    }
    
    archivo << "}\n";
    archivo.close();
    cout << "Archivo Graphviz creado: " << nombreArchivo << endl;
}
//En esta funcion se genera el PNG como bien dice su nombre xd
//A grandes rasgos se implementa la funcion planteada como pista por el docente para la transformacion a PNG
void generarPNG(string archivoDot, string archivoPng) {
    string comando = "dot -Tpng " + archivoDot + " -o " + archivoPng;
    cout << "Generando imagen.\n";
    
    int resultado = system(comando.c_str());
    
    if (resultado == 0) {
        cout << "Imagen creada: " << archivoPng << endl;
    } else {
        cout << "Error: Verifique que Graphviz este instalado\n";
    }
}


int main(){
    Lista* lista;
    iniciarLista(lista);
    
    int opcion;
    string nombre, numero, archivo;
    int posicion;
    
    do {
        cout << "\n*** MENU RESIDUOS ***\n";
        cout << "1. Cargar archivo\n";
        cout << "2. Agregar residuo\n";
        cout << "3. Cambiar residuo\n";
        cout << "4. Eliminar residuo\n";
        cout << "5. Mostrar residuos\n";
        cout << "6. Exportar Graphviz\n";
        cout << "7. Generar PNG\n";
        cout << "8. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                cout << "Nombre archivo: ";
                cin >> archivo;
                leerArchivo(lista, archivo);
                break;

            case 2:
                cout << "Nombre aminoacido: ";
                cin >> nombre;
                cout << "Numero residuo: ";
                cin >> numero;
                agregarResiduo(lista, nombre, numero);
                break;
                
            case 3:
                cout << "Posicion a cambiar: ";
                cin >> posicion;
                cout << "Nuevo nombre: ";
                cin >> nombre;
                cambiarResiduo(lista, posicion, nombre);
                break;
                
            case 4:
                cout << "Posicion a eliminar: ";
                cin >> posicion;
                eliminarResiduo(lista, posicion);
                break;
                
            case 5:
                mostrarResiduos(lista);
                break;
                
            case 6:
                crearGraphviz(lista, "primary_structure.dot");
                break;
            case 7:
                generarPNG("primary_structure.dot", "primary_structure.png");
                break;
                
            case 8:
                cout << "Saliendo del programa...\n";
                break;
                
            default:
                cout << "Opcion invalida\n";
        }
        
    } while (opcion != 8);

    // Se da uso a la funcion de liberar memora (casi se me olvida perdon)
    liberarMemoria(lista);
    
    return 0;
    
}