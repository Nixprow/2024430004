Nicolás Valdivia
Actividad 1
Laboratorio 5

##Descripcion
En este codigo se hace una implementacion de un arbol AVL balanceado el cual tiene por proposito almacenar y gestionar terminos de Gene Ontology (GO).Este arbol se ordena automaticamente gracias al score, ya que este es el que determina la posicion de cada funcion biologica.

##Utilizacion
Se toma el ejecutable y antes de ejecutarlo hay que escribir
"./Actividad_1 funciones_Go.csv" (para asegurarse de ejecutar el codigo con el csv adecuado)

## Nodo AVL
struct Nodo {
    Nodo* izq;      // Puntero al hijo izquierdo
    Nodo* der;      // Puntero al hijo derecho 
    string go;      // Código GO 
    string function;// Nombre de la función biológica
    double score;   // Puntaje del csv
    int FE;         // Factor de equilibrio
};
