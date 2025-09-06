#include <iostream>
#include <cstring>
using namespace std;

struct Paciente{

    char nombre[20];
    int edad;
    int habitacion;
    //Aqui me guie un poco por ejemplo dado por el docente, así que para demostrar como funcionan partes del codigo
    //Reduje las variables, de peso y altura que habian en los anteriores codigos

    Paciente* next; //Lo que hace el next es generar un puntero hacia el siguiente nodo en la lista
};

Paciente* crear_paciente(const char* nombre_,int edad_, int habitacion_){
    Paciente* nuevo_paciente = new Paciente; //Tomando idea del ejemplo otorgado por el profesor que hace uso de malloc en este caso, aqui se reemplazaria por nuevo la cual hace una reserva dinamica de memoria
    strcpy(nuevo_paciente->nombre, nombre_); //Copia el string de nombre
    nuevo_paciente->edad= edad_; //Se le asigna edad
    nuevo_paciente->habitacion=habitacion_;//Se le asigna una habitacion
    nuevo_paciente->next=nullptr;//El siguiente es nulo

    return nuevo_paciente; //Aqui se retorna la informacion creada para el nuevo paciente
}
//Lo que en esencia hace esta funcion es añadir pacientes al final de la lista
void añadir_paciente(Paciente** head,Paciente* nuevo_paciente){

    if (*head==nullptr){ //Esta linea verifica si es que la posicion cabeza o inicial es nula o está vacia
    
        *head=nuevo_paciente; //Y en caso de que esta esté vacia se le asigna el nuevo paciente
    } else {
        Paciente* current = *head;
        while (current->next != nullptr){ //Lo que hace este while es recorrer hasta el ultimo siendo current el actual y next pues el siguiente nodo
            current=current ->next;
        }
        current->next=nuevo_paciente;
        

    }
}

void imprimir_pacientes(Paciente* head){
    cout<<"\n---Lista de Pacientes---\n"<<endl;
    Paciente* current = head;
    while(current!=nullptr){ //La funcion que cumple el while es que si el dato actual es distinto de null muestra los datos del paciente que se encuentran en el nodo actual
        cout<<"Nombre: "<<current->nombre<<endl;
        cout<<"Edad: "<<current->edad<<endl;
        cout<<"Habitacion: "<<current->habitacion<<endl;
        current=current->next; //Esta linea es clave, ya que asi se avanza adecuadamente a traves de la lista dinamica
    }


}

void liberar_memoria(Paciente* head){
    Paciente* current = head;
    while(current != nullptr){

        Paciente* next = current -> next;
        delete current; //Lo que hace el delete es borrar espacio utilizado por el puntero
        current = next; //Esta linea es clave para poder avanzar en la lista, (esto lo investigue, ya que en caso de que no exista esta linea dice que podria haber un memory leaks)
    }
}


int main(){
    Paciente* head= nullptr; //Es un puntero que va a la cabeza de la lista dinamica
    Paciente* nuevo_paciente; //Se crea un puntero temporal para la creacion

    nuevo_paciente= crear_paciente("Nicolás",19,2); //Aqui se llama a la funcion de crear paciente y se le asignan los datos necesarios
    añadir_paciente(&head,nuevo_paciente);// Lo que hace el ampersand con el head, es añadir el paciente creado en la cabeza de la lista dinamica xdd

    nuevo_paciente= crear_paciente("Nicol",19,3);
    añadir_paciente(&head,nuevo_paciente);

    nuevo_paciente= crear_paciente("Antonella",15,6);
    añadir_paciente(&head,nuevo_paciente);

    imprimir_pacientes(head); //Muestra la lista de paciente
    liberar_memoria(head); //Libera la memoria utilizada para no disminuir rendimiento del pc




    return 0;
}