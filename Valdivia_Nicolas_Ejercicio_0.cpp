#include <iostream>
using namespace std;

struct Paciente{
    string nombre;
    int edad;
    float peso;
    float altura;


};


int main (){
    //Se crea una variable del tipo paciente llamada p1
    Paciente p1,p2,p3;
    //Se les asignan datos al paciente en cuestion (ola si peso 93 kilos)
    p1.nombre = "Nicolas";
    p1.edad= 19;
    p1.peso= 93;
    p1.altura= 181;
    //-----------------------------
    //Se le asignan datos al paciente 2
    p2.nombre= "Danilo";
    p2.edad=20;
    p2.peso=80;
    p2.altura=150;
    //----------------------------
    p3.nombre= "ByJxSx";
    p3.edad=20;
    p3.peso= 72;
    p3.altura= 170;

    cout<<"Paciente 1: "<<p1.nombre<<"\nEdad: "<<p1.edad<<"\nPeso: "<<p1.peso<<"\nAltura: "<<p1.altura<<"cm"<<endl;
    cout<<"------------------------------------------------------"<<endl;
    cout<<"Paciente 2: "<<p2.nombre<<"\nEdad: "<<p2.edad<<"\nPeso: "<<p2.peso<<"\nAltura: "<<p2.altura<<"cm"<<endl;
    cout<<"------------------------------------------------------"<<endl;
    cout<<"Paciente 3: "<<p3.nombre<<"\nEdad: "<<p3.edad<<"\nPeso: "<<p3.peso<<"\nAltura: "<<p3.altura<<"cm"<<endl;

    



    return 0; 
}