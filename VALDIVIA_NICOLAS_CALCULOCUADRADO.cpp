#include <iostream>
using namespace std;

double cuadrado (double x){
    return x*x;
}

void escribir_cuadrado(double x){

    cout<<"El cuadrado de "<< x << " es " << cuadrado(x)<< endl;
}

int main(){

    escribir_cuadrado(3.14);
    escribir_cuadrado(1.5);
    
    return 0;
}