#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Nodo{
    int info;
    Nodo* izq; //Este puntero apunta hacia la rama izquierda
    Nodo* der; //Este puntero apunta hacia la rama derecha

};

//La siguiente funcion tiene por proposito crear un nuevo nodo
Nodo* crearNodo (int data){
    Nodo* nuevo = new Nodo; //Esta linea reserva memoria para el nuevo nodo a crear
    nuevo ->info= data; //Se le asigna el valor al nodo
    //Luego se inicializan los 2 hijos, como nulos, ya que no hay nada en esa ubicacion en el momento
    nuevo->izq = nullptr;
    nuevo ->der = nullptr;
    return nuevo; // Y luego se retorna el nuevo nodo creado
}

bool buscarValor(Nodo* nodo, int valor){
    if (nodo == nullptr){ //Si llegamos a nulo, retorna falso
        return false;
    }
    if (nodo-> info== valor){ //Si encontramos el valor que buscamos retorna a true
        return true;
    }

    if (valor < nodo->info){
        return buscarValor(nodo ->izq, valor); //Si es menor se busca en izquierda y si no lo hará en derecha como la linea de más abajo
    }
    return buscarValor(nodo ->der,valor);

}

Nodo* insertarNum (Nodo* nodo, int valor){
    if (nodo==nullptr){ //Si la posicion está vacia se crea un nuevo nodo
        return crearNodo(valor); 
    }

    if(valor<nodo->info){   //Este if plantea que si el valor es menor al nodo actual, se inserta en el subarbol izq
        nodo->izq = insertarNum(nodo->izq,valor);

    } else if (valor > nodo->info){ //Este es en caso de que sea mayor que el nodo actual, y por lo tanto se inserta en el subarbol derecho
        nodo->der = insertarNum(nodo ->der,valor); 

    } else {
        cout<<"El numero "<<valor<< " ya existe en el árbol. No se permiten dupllicados"<<endl;

    }

    return nodo; 

}
//Este busca al nodo minimo que seria a la izquiera ya que va de menor a mayor
Nodo* encontrarMinimo(Nodo* nodo){
    while (nodo->izq != nullptr){
        nodo = nodo->izq;
    }
    return nodo;

}

Nodo* removerNum(Nodo* nodo, int valor){
    if(nodo == nullptr){ //Si el arbol está vacio da el mensaje de que no está como para eliminarlo
        cout<<"El numero "<<valor<< " no se encuentra en el arbol"<<endl;
        return nodo;

    }

    if (valor < nodo->info){
        nodo->izq = removerNum(nodo->izq,valor); //Busca por la izquierda
    } else if (valor > nodo->info){
        nodo ->der= removerNum(nodo->der,valor); //Busca en la derecha

    } else {
        //Si es que se encuentra el nodo, tenemos 3 posibles casos


        //Primer caso: Nodo hoja
        if (nodo ->izq == nullptr){ //ESte if verifica si solo tiene un hijo derecho o si es hoja
            Nodo* temp = nodo->der;
            delete nodo;
            cout<<"Numero "<<valor<<" eliminado correctamente"<<endl;
            return temp;
        } else if (nodo-> der == nullptr){ //Este if es en caso de que solo tenga al hijo izq
            Nodo* temp= nodo->izq; //Se guarda la referencia del hijo
            delete nodo;
            cout<<"Numero "<<valor<< " eliminado correctamente"<<endl;
            return temp; //Conecta el hijo al padre

        }

        //Segundo caso: Nodo con 2 hijos
        Nodo* temp= encontrarMinimo(nodo->der); //Esta linea encuentra el minimo del subarbol derecho

        nodo->info = temp->info;
        nodo->der = removerNum(nodo->der,temp->info); //Elimina el minimo original

    }

    return nodo;
}

//Esta funcion es para modificar un elemento, valorA es valor antigo y valor N es valor nuevo porsiacaso
Nodo* modificar(Nodo* raiz, int valorA, int valorN){
    if (buscarValor(raiz,valorN)){ //Verificar si el valor nuevo ya existe
        cout<<"El nuevo valor "<< valorN<<" ya existe en el arbol"<<endl;

        return raiz;
    }

    raiz= removerNum(raiz,valorA); //Se elimina el valor antiguo y se inserta el nuevo xd
    raiz= insertarNum(raiz,valorN);

    cout<<"Valor modificado de "<< valorA <<" a "<<valorN<<" correctamente."<<endl;
    return raiz;
}   
//Esta funcion debe partir por la raiz para luego ir a la izquierda y luego derecha
void preOrden(Nodo* nodo){
    if (nodo==nullptr){ //Esto es en caso de nodo nulo o la base por decirlo asi
        return;
    }
    cout<<nodo->info<< " "; //Asi se visita la raiz y se imprime
    //Recorre lado izquierdo y luego el derecho
    
    preOrden(nodo->izq);
    preOrden(nodo->der);
}
//Esta funcion parte por la izquierda, llega a la raiz y luego a la rama derecha
void inOrden(Nodo* nodo){
    if(nodo== nullptr){
        return;
    }
    inOrden(nodo->izq);
    cout<< nodo->info<< " "; //Visita raiz
    inOrden(nodo->der);
}
//Esta funcion parte por la izquierda-derecha y al final la raiz
void posOrden(Nodo* nodo){
    if (nodo==nullptr){
        return;
    }
    posOrden(nodo->izq);
    posOrden(nodo->der);
    cout<<nodo->info<<" ";
}
//Esta funcion crea con Graphviz
void generarGraphviz(Nodo* nodo, ofstream& fp){
    if (nodo != nullptr){
        //Primero se procesa el hijo izq
        if (nodo->izq!=nullptr){
            //En caso de que este exista se crea una conexion
            fp<<"    "<<nodo->info<<"->"<<nodo->izq->info<<";"<<endl;
        } else {
            //Si no existe se crea el nodo fantasma (ese punto q marca q en realidad no hay na)
            string nodoNulo = "null" + to_string(nodo->info)+ "l";
            fp <<"    "<<nodoNulo<<" [shape=point];"<<endl;
            fp <<"    "<<nodo->info<<"->"<<nodoNulo<<";"<<endl;
        }

        if (nodo->der!=nullptr){
            //En caso de que este exista se crea una conexion
            fp<<"    "<<nodo->info<<"->"<<nodo->der->info<<";"<<endl;
        } else {
            //Si no existe se crea el nodo fantasma (ese punto q marca q en realidad no hay na)
            string nodoNulo = "null" + to_string(nodo->info)+ "r";
            fp <<"    "<<nodoNulo<<" [shape=point];"<<endl;
            fp <<"    "<<nodo->info<<"->"<<nodoNulo<<";"<<endl;
        }

        generarGraphviz(nodo->izq, fp);
        generarGraphviz(nodo->der, fp);
    }
}
//Funcion para crear el grafo
void generarGrafo(Nodo* raiz) {
    ofstream fp("grafo.txt");  // Abre archivo para escritura
    
    if (!fp.is_open()) {
        cerr << "Error al crear el archivo grafo.txt" << endl;
        return;
    }
    
    // Escribi encabezado del archivo DOT
    fp << "digraph G {" << endl;
    fp << "    node [style=filled fillcolor=yellow];" << endl;
    
    // Genera contenido del árbol
    generarGraphviz(raiz, fp);
    
    fp << "}" << endl;  // Cerra el grafo
    fp.close();         // Cerra archivo
    
    // Ejecuta Graphviz para generar imagen PNG
    system("dot -Tpng -ografo.png grafo.txt");
    cout << "Archivo grafo.png generado correctamente.\n";
}
//Con el comando eog grafo.png se puede visualizar el grafo
//y claro el "grafo" de grafo.png se reemplazaria por el nombre del png a visualizar
//Esta funcion es la de liberar memoria pero aplicada al arbol y esta se encarga de eliminar primero el subarbol izquierdo y luego el derecho
void liberarMemoria(Nodo* nodo){
    if (nodo==nullptr){
        return;
    }

    liberarMemoria(nodo->izq);
    liberarMemoria(nodo->der);
    delete nodo;
}
int main(){

    Nodo* raiz =nullptr; //La raiz del arbol o el primer nodo se incializa como vacio
    int opcion, valor,valorA;


    cout << "LABORATORIO 4 - ÁRBOLES BINARIOS" << endl;
    cout << "============================================" << endl;
    //A continuacion se hace un do con el switch y case para hacer el menu

    do{

        cout<<"\n --- Menú Arbol Binario de Busqueda ---"<<endl;
        cout<<"1. Insertar Numero"<<endl;
        cout<<"2. Modificar Numero"<<endl;
        cout<<"3. Eliminar numero"<<endl;
        cout<<"4. Mostrar recorridos"<<endl;
        cout<<"5. Generar grafo"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Seleccione una opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1: 
                cout<<"Ingrese el numero a insertar: ";
                cin>>valor;
                raiz=insertarNum(raiz,valor);
                break;
            case 2:
                cout<<"Ingrese el numero a modificar: ";
                cin>>valorA;
                cout<<"Ingrese el nuevo valor: ";
                cin>>valor;
                raiz=modificar(raiz,valorA,valor);
                break;
            case 3:
                cout<<"Ingrese numero a eliminar: ";
                cin>>valor;
                raiz=removerNum(raiz,valor);
                break;
            case 4:
                if(raiz==nullptr){
                    cout<<"El arbol está vacio."<<endl;

                } else {
                    cout<<"Preorden: ";
                    preOrden(raiz);
                    cout<< "\n";

                    cout<<"Inorden: ";
                    inOrden(raiz);
                    cout<<"\n";

                    cout<<"Posorden: ";
                    posOrden(raiz);
                    cout<<"\n";
                }
                break;
            case 5:
                if (raiz==nullptr){
                    cout<<"El arbol está vacio. Inserte numeros antes de volver a intentarlo"<<endl;

                } else {
                    generarGrafo(raiz);
                }
                break;
            case 0:
                cout<<"Saliendo del programa"<<endl;
                liberarMemoria(raiz); //Se libera memoria al momento de salir del programa
                raiz= nullptr; //Esto según lo que investigué sirve para evitar algo llamado dangling pointer
                break;
            default:
            cout<<"Opcion no valida. Intente nuevamente"<<endl;



        }

    } while(opcion != 0);


    return 0;
}