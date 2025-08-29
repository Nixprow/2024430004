#include <iostream>
using namespace std;

int verificar_string(char cadena[]){

    int i= 0;

    while (cadena[i]!= '\0') {
        i++;

    }
    return i;
}

void es_par(int x){
    if (x % 2 == 0){
        cout<<"El numero "<< x << " es par"<< endl;
    }
    else {
        cout<<"El numero "<< x <<" no es par"<<endl;
    }

}

void ciclo_numeros(){
    int i = 1;

    while (i <= 10 ){
        es_par(i);
        i++;
    }
}

int main(){
    int n;
    char palabra[70];
    cout<<"Ingrese un numero para verificar si es par o no: ";
    cin>>n;
    es_par(n);
    cout<<"------------------------------------------------"<<endl;
    cout<<"Numeros de el 1 al 10 para corroborar si son pares o impares:"<<endl;
    ciclo_numeros();
    cin.ignore();
    cout<<"-------------------------------------------------"<<endl;
    cout<<"Ingrese una palabra para contar la cantidad de letras: ";
    cin.getline(palabra,70);
    cout<<"El largo de la palabra: "<< palabra <<" es: "<< verificar_string(palabra)<< endl;


    



    return 0;
}