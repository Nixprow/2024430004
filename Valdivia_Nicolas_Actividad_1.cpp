#include <iostream>
#include <string>
using namespace std;

//Gran parte del codigo, se guia en la ayuda del docente, el archivo pila_con_nodo.cpp
struct Nodo{
    string nombre; //Atributos propios de la clase estudiante solo que se agrupan dentro de una estructura llamada Nodo
    string carrera;
    float promedio;
    Nodo* siguiente;

};

struct Cola{
    Nodo* frente; //Esta variable marca un puntero al inicio de la lista dinamica
    Nodo* final;//Y esta marca el ultimo

};

void inicializarCola(Cola*& cola){

    cola= new Cola(); //Esta linea crea una nueva estructura Cola en memoria dinamica
    cola->frente = nullptr; // Esta linea se encarga de comenzar el frente como nulo
    cola->final=nullptr;//Y el final tambien

}

bool colaVacia(Cola* cola){

    return(cola->frente==nullptr); //Esta linea o más bien la funcion se encarga de verificar si la cola está vacia, y si frente es igual a nullptr, significa que si se cumple
}
//Lo que hará esta funcion será insertar un estudiante al final de la cola 
void insertarCola(Cola* cola,string nombre,string carrera,float promedio){
    
    //Se crea un nuevo nodo en memoria dinamica
    Nodo* nuevo = new Nodo();
    //Se crean los atributos de la clase 
    nuevo->nombre = nombre;
    nuevo->carrera= carrera;
    nuevo->promedio = promedio;
    nuevo-> siguiente = nullptr; //Esté representa el ultimo por lo cual se le asigna el nulo

    //Se usa el if para ver si la cola está vacia
    if (colaVacia(cola)){
        //Y si esta cola se encuentra vacia lo que hará es que el nodo nuevo, se encuentre tanto al inicio como al final
        cola->frente = nuevo;
        cola->final= nuevo;
    } else {
        //Pero en caso de que no esté vacio se enlaza el ultimo nodo al nuevo
        cola->final->siguiente= nuevo;
        cola-> final=nuevo;//Actualiza el final para q el final sea el nuevo nodo

    }

    cout<<"Estudiante: "<<nombre<<" agregado a la cola. "<<endl;



}

bool eliminarCola(Cola* cola, string& nombre,string& carrera,float& promedio){

    //Primero se verifica si la cola está vacia o no
    if (colaVacia(cola)){
        return false; //No se puede eliminar cola si está se encuentra vacia

    }
    //Guardar referencia al nodo que se va a eliminar, el cual se le pone de nombre auxiliar
    Nodo* aux = cola->frente;

    //Esto extrae los datos del nodo antes de eliminarlo
    nombre=aux->nombre;
    carrera= aux->carrera;
    promedio = aux->promedio;
    
    //Verifica si solo hay un elemento en la cola
    if (cola->frente == cola ->final){
        //Y si solo hay uno la cola queda vacia 
        cola->frente = nullptr;
        cola->final = nullptr;

    } else {

        cola->frente= cola->frente->siguiente;
    }

    delete aux;
    return true;


}

void mostrarCola(Cola* cola){
    if (colaVacia(cola)){
        cout<<"la cola está vacia."<<endl;
        return;
    }

    cout<<"\n---CANTIDAD ACTUAL DE LA COLA---\n";
    int pos = 1;
    Nodo* actual = cola ->frente;
    while (actual != nullptr){
        cout<< pos << "- "<<actual->nombre<<" | "
            <<actual->carrera <<" | Promedio: "
            <<actual -> promedio<<endl;
        actual = actual->siguiente;
        pos++;
    }
    cout<<"----------------------------------\n";
    
}
//Esta borra una posicion en una posicion especifica, lo cual es distinto del eliminar cola, que este sera el dequeue
bool borrarPosicion(Cola* cola, int posicion){

    if ((colaVacia(cola)) || posicion < 1){
        return false;
    }
    //Este if es para un caso especial y se encarga de borrar el primer elemento o el frente de la cola
    if (posicion == 1){
        string nombre;
        string carrera;
        float promedio;
        return eliminarCola(cola,nombre,carrera,promedio);//En este caso se reutiliza la funcion existente de eliminar cola
    }

    Nodo* actual=cola->frente; // Empieza desde el frente
    Nodo* anterior = nullptr;// Guardar referencia al nodo anterior
    int contador= 1;

    //Avanzar hasta llegar a la posicion deseada
    while (actual != nullptr && contador < posicion){
        anterior = actual;  //Guarda el nodo anterior
        actual = actual -> siguiente; // Avanza al siguiente nodo
        contador++;  // esto hace que el contado avance
    }
    if (actual == nullptr){
        return false;
    }

    anterior ->siguiente = actual->siguiente; //Lo que hace la siguiente linea es saltar al nodo que busca eliminar

    //Si se eliminó el ultimo elemento, reorganiza el final
    if (actual == cola->final){
        cola->final = anterior; //El anterior ahora es el ultimo

    }

    //Libera la memoria del nodo eliminado
    delete actual;
    return true;
    
}


int main(){
    Cola* cola;
    inicializarCola(cola); //Se inicializa la cola vacia llamando a la funcion de inicializarCola
    //He de aclarar que es primera vez que trabajo con switch, por lo cual m cuesta algo aun
    int opcion;
    string nombre,carrera;
    float promedio;  
    int pos;    
    
    //Se hace uso del do y de switch, para trabajar con el menu

    do { 
        cout<<"\n---MENU ESTUDIANTES COLA---\n";
        cout<<"1-Insertar estudiante"<<endl;
        cout<<"2-Eliminar estudiante"<<endl;
        cout<<"3-Mostrar cola completa"<<endl;
        cout<<"4-Borrar una posicion especifica"<<endl;
        cout<<"5-Verificar si la cola está vacia"<<endl;
        cout<<"6-Salir"<<endl;
        cout<<"Seleccione una opcion: "<<endl;
        cin>>opcion;
        cin.ignore();

        switch (opcion){
            case 1:
                cout<<"Nombre: ";
                getline(cin,nombre);
                cout<<"Carrera: ";
                getline(cin,carrera);
                cout<<"Promedio: ";
                cin>> promedio;
                cin.ignore();
                insertarCola(cola,nombre,carrera,promedio);
                break;
            case 2:
                if(eliminarCola(cola,nombre,carrera,promedio)){
                    cout<<"Se ha eliminado la cola: "<< nombre << " | "<<carrera<<" | Promedio: "<< promedio <<endl;
                } else {
                    cout<<"La cola está vacia.\n";
                }
                break;
            case 3: 
                mostrarCola(cola);
                break;
            case 4:
                cout<<"Ingrese la posicion a borrar: ";
                cin>> pos;
                if (borrarPosicion(cola,pos)){
                    cout<<"Se borró el estudiante que se encontraba en la posicion: "<<pos<<endl;

                } else {
                    cout<<"Posicion invalida :c"<<endl;

                }
                break;
            case 5:
                if (colaVacia(cola)){
                    cout<<"La cola ta vacia. "<<endl;

                } else {
                    cout<<"La cola no ta vacia"<<endl;
                }
                break;
            case 6:
                cout<<"Saliendo"<<endl;
                break;
            default: //Hace 5 minutos descubrí cual era la utilidad del default
                cout<<"Opcion invalida";
        }
    } while (opcion!=6);
    //Esto libera memoria
    while(!colaVacia(cola)){
        string nombre, carrera;
        float promedio;
        eliminarCola(cola,nombre,carrera, promedio); //Al finalizar el menú se eliminan todos los nodos
    }
    delete cola;
    
    

    return 0;
}