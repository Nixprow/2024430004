#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono; //Este nuevo using namespace se encarga de simplificar la sintaxis de chrono con el std
//Como aclaracion, al no querer usar la libreria de vectores, hice uso de vectores de la forma *(vec + i) lo cual representa normalmente el elemento al que apunta el puntero

void generar_vector_aleatorio(int *vec, int n){
    for (int i=0; i<n; i++){ //Recorre cada posicion del vector
        *(vec + i)= rand() % 10000; //Asigna un numero aleatorio entre 0 y 9999 y si quiere la explicacion del sentido del vec + 1 , es al elemento al que apunta

    }
    
}
//Esta funcion se encarga de copiar
void copiar(int *destino,int *origen, int n){
    for(int i=0;i<n; i++){
        *(destino + i)=*(origen + i); //ESto lee el vector de acuerdo al destino y al origen respectivamente y tambien copia elemento por elemento 
    }

}

//Esta funcion desea mostrar en pantalla los elementos en cuestion
void mostrar(int *vec,int n,string nombre){
    //Primero se muestra el nombre del vector
    cout<<nombre<<endl;

    for(int i=0;i<n;i++){
        //En la siguiente linea se muestra el indice y el valor del elemento actual
        cout<<"a["<<i<<"]="<<*(vec+i)<<" ";
    }

    cout<<endl<<"--------------------------------------"<<endl;


}

//primero se crea el algoritmo burbuja correspondiente al cuadratico
void burbuja(int *vec, int n){
    //Las siguientes lineas tienen relacion con un avance de lista sobre listas
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            //Si estan en orden incorrecto, los intercambia
            if(*(vec + j) > *(vec + j + 1)){

                int temp = *(vec + j); //Guarda el valor actual, como un temporal
                *(vec + j) = *(vec + j + 1); //Luego le asigna el valor siguiente al actual
                *(vec + j + 1)= temp; //Y por ultimo se asigna el valor temporal al siguiente
            }
        }

    }
}
//Como segundo el algoritmo de insercion
void insercion (int *vec, int n){
    for(int i=1;i<n; i++){
        //Primero se guarda el valor actual a insertar
        int key = *(vec + i);
        //j es el indice del elemento anterior al actual
        int j = i - 1;


        while(j>=0 && *(vec + j) > key){ 
            // La siguiente linea se encarga de desplazar el elemento mayor hacia la der
            *(vec + j + 1) = *(vec + j);
            // Retrocede para comparar con el siguiente elemento
            j--;
        }

        *(vec + j + 1) = key;
    }

}
//Tercero tenemos el algoritmo de seleccion
void seleccion(int *vec, int n){

    for(int i = 0;i<n-1; i++){
        //Se supone que el menor está en la posicion actual
        int min_id= i;
        //Busca el elemento menor en el resto del vector
        for(int j = i + 1; j < n; j++){
            if(*(vec+ j) < *(vec+ min_id)){
                min_id = j;
            }
        }

        int temp = *(vec + min_id); //PRimero se guarda el valor menor
        *(vec + min_id)= *(vec + i); //Se le asigna el valor actual al del menor
        *(vec + i) = temp; //Pone el menor en la posicion actual
    }

}
//Aqui se comienza con la busqueda interna de los logaritmicos
void shellsort (int *vec, int n){
    //COmienza con un gap reduciendo a la mitad en cada iteracion
    for(int gap = n/2;gap > 0;gap /=2){
        // Aplica la insercion en el gap actual
        for(int i= gap; i < n; i++){
            //Se guarda el elemento en una variable temporal o aux
            int temp = *(vec + i);
            int j = i; //Indice para el desplazamiento
            
            //Desplaza elementos mayores que temp segun el gap
            while (j >= gap && *(vec + j - gap) > temp){
                //Mueve el elemento mayor hacia adelante

                *(vec + j) = *(vec + j -gap);
                //Retrocede un salto
                j -= gap;
            }
            *(vec + j) = temp;

        }   

    }

}
//Primero se hace la funcion de particion para el quicksort
int particion(int *vec, int inicio, int fin){
    //Elige el ultimo elemento como pivote
    int pivote = *(vec + fin);
    //Indice el cual marca la posicion del ultimo elemento menor que el pivote
    int i = inicio - 1;

    for(int j = inicio; j< fin; j++){

        if(*(vec + j) <= pivote){
            i++;
            //Aqui se intercambia el elemento actual con la posicion i en la que vaya
            int temp= *(vec + i);
            *(vec + i) = *(vec + j);
            *(vec + j) = temp;

        }
    }

    //Se encarga de colocar el pivote en la ultima posicion luego de todos los valores menoresw
    int temp= *(vec + i + 1);
    *(vec + i + 1) = *(vec + fin);
    *(vec + fin) = temp;

    return i + 1;

}
//Algoritmo quicksort como tal (se hará uso de la particion creada exclusivamente para quicksort)
void quicksort(int *vec, int inicio, int fin){
    //Como caso principal tenemos que el segmento tiene más de un elemento
    if (inicio<fin){
        //Primero se obtiene la posicion del piv despues de la particion
        int pos_pivote = particion(vec,inicio, fin);
        quicksort(vec, inicio, pos_pivote - 1);
        quicksort(vec, pos_pivote + 1, fin);
    }
}

void quicksort_wrapper(int *vec, int n){
    
    quicksort(vec,0, n-1);
}

int main(int argc, char* argv[]){

    if (argc != 3){

        cout<<"Uso: "<<argv[0] <<" N VER"<<endl;
        cout<<"N:(escribir numero de elementos positivos)"<<endl;
        cout<<"VER: 's' mostrar,'n' no mostrar"<<endl;
        return 1; 
    }
    //Convierte el primer argumento de string a entero
    int n = atoi(argv[1]);

    string ver = argv[2];


    //Primero se verifica que N sea un numero positivo
    if(n<=0){
        cout<<"Error: N debe ser positivo"<<endl;
        return 1;
    }
    //Inicializa el generador de numeros aleatorios con la hora actual como semilla
    srand(time(0));

    //Reserva  memoria dinamica para 6 vectores de n elementos cada uno
    int* original = new int[n];
    int* copia_burbuja = new int[n];
    int* copia_insercion = new int[n];
    int* copia_seleccion = new int[n];
    int* copia_shellsort = new int[n];
    int* copia_quicksort = new int[n];

    //Se llena el vector original con numeros aleatorios
    generar_vector_aleatorio(original, n);

    if(ver == "s"){
        mostrar(original, n,"Original:");

    }

    copiar(copia_burbuja,original,n);
    copiar(copia_insercion,original,n);
    copiar(copia_seleccion,original, n);
    copiar(copia_shellsort,original, n);
    copiar(copia_quicksort, original,n);

    //Las siguientes funciones o lineas se encargaran de medir el tiempo de ejecucion de los algoritmos

    //Primero el burbuja
    auto inicio_burbuja =high_resolution_clock::now(); //Esta linea registra el tiempo inicial
    burbuja(copia_burbuja,n);
    auto fin_burbuja = high_resolution_clock::now();//Registra el tiempo final
    long long tiempo_burbuja= duration_cast<milliseconds>(fin_burbuja - inicio_burbuja).count();

    //Luego el de insercion
    auto inicio_insercion =high_resolution_clock::now(); //Esta linea registra el tiempo inicial
    insercion(copia_insercion,n);
    auto fin_insercion = high_resolution_clock::now();//Registra el tiempo final
    long long tiempo_insercion= duration_cast<milliseconds>(fin_insercion - inicio_insercion).count();

    //Luego el de Seleccion
    auto inicio_seleccion =high_resolution_clock::now(); //Esta linea registra el tiempo inicial
    seleccion(copia_seleccion,n);
    auto fin_seleccion = high_resolution_clock::now();//Registra el tiempo final
    long long tiempo_seleccion= duration_cast<milliseconds>(fin_seleccion - inicio_seleccion).count();

    //Despues Shellsort
    auto inicio_shellsort =high_resolution_clock::now(); //Esta linea registra el tiempo inicial
    shellsort(copia_shellsort,n);
    auto fin_shellsort = high_resolution_clock::now();//Registra el tiempo final
    long long tiempo_shellsort= duration_cast<milliseconds>(fin_shellsort - inicio_shellsort).count();

    //Y por ultimo Quicksort
    auto inicio_quicksort =high_resolution_clock::now(); //Esta linea registra el tiempo inicial
    quicksort_wrapper(copia_quicksort,n);
    auto fin_quicksort = high_resolution_clock::now();//Registra el tiempo final
    long long tiempo_quicksort= duration_cast<milliseconds>(fin_quicksort - inicio_quicksort).count();

    //Las siguientes tablas comparativas de tiempos de ejecucion

    cout<<"-----------------------------------------------"<<endl;
    cout<<"Metodo\t\t|Tiempo"<<endl;
    cout<<"Burbuja\t\t|"<<tiempo_burbuja<<" ms"<<endl;
    cout<<"Insercion\t|"<<tiempo_insercion<<" ms"<<endl;
    cout<<"Seleccion\t|"<<tiempo_seleccion<<" ms"<<endl;
    cout<<"Shellsort\t|"<<tiempo_shellsort<<" ms"<<endl;
    cout<<"Quicksort\t|"<<tiempo_quicksort<<" ms"<<endl;
    cout<<"-------------------------------------------------"<<endl;

    if(ver == "s"){
        mostrar(copia_burbuja,n,"Burbuja:");
        mostrar(copia_insercion,n,"Insercion:");
        mostrar(copia_seleccion,n,"Seleccion:");
        mostrar(copia_shellsort,n,"Shellsort:");
        mostrar(copia_quicksort,n,"Quicksort:");
    }
    //Las siguientes lineas liberan la memoria utilizada por el new[] (no hice la funcion para eliminar esa memoria en este caso)
    delete[] original;
    delete[] copia_burbuja;
    delete[] copia_insercion;
    delete[] copia_seleccion;
    delete[] copia_shellsort;
    delete[] copia_quicksort;

    
    return 0;
}