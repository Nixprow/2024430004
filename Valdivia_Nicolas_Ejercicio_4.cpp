#include <iostream>
#include <fstream>
#include <cstring>  
using namespace std;

struct Paciente {
    char nombre[30];
    int edad;
    float peso;
    float altura;
    Paciente* next;
};

//En esencia todo esto es parecido y hacen lo mismo que en los codigos anteriores
Paciente* crear_paciente(const char* nombre, int edad, float peso, float altura) {
    Paciente* nuevo = new Paciente;
    strcpy(nuevo->nombre, nombre);
    nuevo->edad = edad;
    nuevo->peso = peso;
    nuevo->altura = altura;
    nuevo->next = nullptr;
    return nuevo;
}

// Hace lo mismo que en los otros codigos
void agregar_paciente(Paciente** head, Paciente* nuevo) {
    if (*head == nullptr) {
        *head = nuevo;
    } else {
        Paciente* actual = *head;
        while (actual->next != nullptr) {
            actual = actual->next;
        }
        actual->next = nuevo;
    }
}
//hace lo mismo que en los otros codigos
void imprimir_pacientes(Paciente* head) {
    Paciente* actual = head;
    cout << "\n--- Lista de pacientes ---\n";
    while (actual != nullptr) {
        cout << "Nombre: " << actual->nombre 
             << " | Edad: " << actual->edad 
             << " | Peso: " << actual->peso 
             << " | Altura: " << actual->altura 
             << " | IMC: " << (actual->peso / (actual->altura * actual->altura)) 
             << endl;
        actual = actual->next;
    }
    cout << "---------------------------\n";
}

// Calcula el promedio de edad
float promedio_edad(Paciente* head) {
    int suma = 0, contador = 0;
    Paciente* actual = head;
    while (actual != nullptr) {
        suma += actual->edad;
        contador++;
        actual = actual->next;
    }
    return (contador > 0) ? (float)suma / contador : 0;
}

// Calcula el promedio de peso
float promedio_peso(Paciente* head) {
    float suma = 0;
    int contador = 0;
    Paciente* actual = head;
    while (actual != nullptr) {
        suma += actual->peso;
        contador++;
        actual = actual->next;
    }
    return (contador > 0) ? suma / contador : 0;
}

// Libera la memoria utilizada por el paciente (se repite en esencia lo de los ejercicios anteriores)
void liberar_memoria(Paciente* head) {
    while (head != nullptr) {
        Paciente* siguiente = head->next;
        delete head;
        head = siguiente;
    }
}

// Me guie de un repositorio de programacion 1
void cargar_desde_archivo(Paciente** head, const char* nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        char nombre[30];
        int edad;
        float peso, altura;
        while (archivo >> nombre >> edad >> peso >> altura) {
            Paciente* nuevo = crear_paciente(nombre, edad, peso, altura);
            agregar_paciente(head, nuevo);
        }
        archivo.close();
        cout << "Pacientes cargados desde archivo correctamente.\n";
    } else {
        cout << "No se pudo abrir el archivo.\n";
    }
}

//Saque informacion de un repositorio de programacion 1 para hacer lo de guardar archivo y tal
void guardar_en_archivo(Paciente* head, const char* nombre_a) {
    ofstream archivo(nombre_a);
    if (archivo.is_open()) {
        Paciente* actual = head;
        while (actual != nullptr) {
            archivo << actual->nombre << " "
                    << actual->edad << " "
                    << actual->peso << " "
                    << actual->altura << endl;
            actual = actual->next;
        }
        archivo.close();
        cout << "Pacientes guardados en archivo correctamente.\n";
    } else {
        cout << "No se pudo abrir el archivo para escritura.\n";
    }
}

//Aqui en el main se asigna lo necesario para el menu
int main() {
    Paciente* lista = nullptr;
    int opcion;

    do {
        cout << "\n=== Menu de Gestion de Pacientes ===\n";
        cout << "1. Agregar paciente manualmente\n";
        cout << "2. Mostrar pacientes\n";
        cout << "3. Calcular promedio de edad\n";
        cout << "4. Calcular promedio de peso\n";
        cout << "5. Cargar pacientes desde archivo\n";
        cout << "6. Guardar pacientes en archivo\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            char nombre[30];
            int edad;
            float peso, altura;
            cout << "Nombre: "; cin >> nombre;
            cout << "Edad: "; cin >> edad;
            cout << "Peso: "; cin >> peso;
            cout << "Altura: "; cin >> altura;

            Paciente* nuevo = crear_paciente(nombre, edad, peso, altura);
            agregar_paciente(&lista, nuevo);
        }
        else if (opcion == 2) {
            imprimir_pacientes(lista);
        }
        else if (opcion == 3) {
            cout << "Promedio de edad: " << promedio_edad(lista) << endl;
        }
        else if (opcion == 4) {
            cout << "Promedio de peso: " << promedio_peso(lista) << endl;
        }
        else if (opcion == 5) {
            cargar_desde_archivo(&lista, "datos.txt");
        }
        else if (opcion == 6) {
            guardar_en_archivo(lista, "salida.txt");
        }

    } while (opcion != 7);

    liberar_memoria(lista);
    return 0;
}
