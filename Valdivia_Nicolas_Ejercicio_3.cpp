#include <iostream>
#include <cstring>
using namespace std;



struct Paciente{
    char nombre[20];
    int edad;
    float peso;
    float altura;
    Paciente* next; // Este en resumen ve el siguiente nodo (gran parte es casi lo mismo que el ejercicio anterior)
    //Dato, aqui aproveche el vacio legal y no añadí habitacion ya que no es informacion relevante con respecto a lo que pide el ejercicio numero 4
};

Paciente* crear_paciente(const char* nombre_,int edad_,float peso_,float altura_){

    Paciente* nuevo= new Paciente;
    strcpy(nuevo->nombre,nombre_); //Esta linea copia y pega el nombre asignado en la estructura hacia la variable nueva creada por la funcion de crear paciente
    nuevo->edad= edad_;
    nuevo->peso= peso_;
    nuevo->altura= altura_;
    nuevo->next= nullptr; // Esta linea es crucial, ya que esta indica que al pasar a la siguiente posicion está se vuelve nula por la cual se llega al final de la lista dinamica
    return nuevo;
}
void agregar_paciente(Paciente** head, Paciente* nuevo) {
    if (*head == nullptr) { //Esta funcion evalua que la cabeza de la lista esté vacia y en caso de que sea vacia está añadira un paciente en la siguiente linea
        *head = nuevo;
    } else {
        Paciente* actual = *head;
        while (actual->next != nullptr) {
            actual = actual->next;
        }
        actual->next = nuevo;
    }
}
//Se crea una funcion que calcula el IMC de cada paciente
float calcular_imc(Paciente* p){
    return p->peso / (p->altura * p->altura); //Aqui se aplica la formula dada en el laboratorio
}
void imprimirPacientes(Paciente* head) {
    cout << "\n=== Lista de Pacientes ===\n" << endl;
    Paciente* actual = head;
    while (actual != nullptr) {
        cout << "Nombre: " << actual->nombre << endl;
        cout << "Edad: " << actual->edad << " años" << endl;
        cout << "Peso: " << actual->peso << " kg" << endl;
        cout << "Altura: " << actual->altura << " m" << endl;
        cout << "IMC: " << calcular_imc(actual) << endl;
        actual = actual->next; //Esta linea hace que se vaya avanzando en su posicion en la lista y va anotando los datos de cada paciente
    }
}

float promedio_edad(Paciente* head) {
    int suma = 0;
    int contador = 0;
    Paciente* actual = head;

    while (actual != nullptr) {
        suma = suma + actual->edad;  // sumamos las edades
        contador = contador + 1;     // se hace un contador para los paciente que haya en la lista
        actual = actual->next;       //Esto hace que la lista avance
    }

    if (contador == 0) {
        return 0;   // si la lista está vacía, el promedio es 0
    } else {
        return (float)suma / contador; // se calcula el promedio
    }
}

float promedio_peso(Paciente* head) { //En esencia esta funcion hace exactamente lo mismo que la anterior, asi que no creo que sea necesaria una explicacion como tal
    float suma = 0;
    int contador = 0;
    Paciente* actual = head;

    while (actual != nullptr) {
        suma = suma + actual->peso;  
        contador = contador + 1;      
        actual = actual->next;      
    }

    if (contador == 0) {
        return 0;   
    } else {
        return suma / contador; 
    }
}
//(Dato, en esencia al ser similar hice un copypaste de la funcion del ejercicio2)
void liberar_memoria(Paciente* head){
    Paciente* current = head;
    while(current != nullptr){

        Paciente* next = current -> next;
        delete current; //Lo que hace el delete es borrar espacio utilizado por el puntero
        current = next; //Esta linea es clave para poder avanzar en la lista, (esto lo investigue, ya que en caso de que no exista esta linea dice que podria haber un memory leaks)
    }
}

int main() {
    Paciente* lista = nullptr; //En esencia toda la funcion main es super parecida a la del ejercicio 2, más que nada añadiendo lo de calcular los promedios

    agregar_paciente(&lista, crear_paciente("Nicolás", 19,91.7, 1.81));
    agregar_paciente(&lista, crear_paciente("Nicol", 19,66, 1.62));
    agregar_paciente(&lista, crear_paciente("Jose", 16,55.0, 1.70));

    // Imprimir pacientes con IMC
    imprimirPacientes(lista);

    // Calcular promedios
    cout << "\nPromedio de edad: " << promedio_edad(lista) << " años" << endl;
    cout << "Promedio de peso: " << promedio_peso(lista) << " kg" << endl;


    liberar_memoria(lista);

    return 0;
}
