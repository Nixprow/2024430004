#include <iostream>
using namespace std;

struct Paciente{
    string nombre;
    int edad;
    float peso;
    float altura;


};


int main(){
    //Se define un arreglo para los pacientes que almacena hasta 3 pacientes siendo el numero 0, 1 y 2 (por que parte contando desde el 0)
    Paciente p[3];

    p[0].nombre= "Nicolás";
    p[0].edad=19;
    p[0].peso=92;
    p[0].altura= 180;
    //----------------------------------
    p[1].nombre= "Sebastian";
    p[1].edad=20;
    p[1].peso=102;
    p[1].altura= 190;
    //----------------------------------
    p[2].nombre= "Ebesteban";
    p[2].edad=19;
    p[2].peso=80;
    p[2].altura= 185;
    //------------------------------------
    //Se hace uso de una funcion for la cual viaje a traves del arreglo con los pacientes 

    cout<<"---LISTA DE PACIENTES---"<<endl;

    for(int i= 0;i<3 ;i++){
        cout<<"Paciente N°"<<i+1<<": "<<endl;
        cout<<"Nombre: "<<p[i].nombre<<endl;
        cout<<"Edad: "<<p[i].edad<<endl;
        cout<<"Peso: "<<p[i].peso<<endl;
        cout<<"Altura: "<<p[i].altura<<"cm"<<endl;
        cout<<endl;
    }

    return 0;
}