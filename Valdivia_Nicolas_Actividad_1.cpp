#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct Nodo {
    Nodo* izq;      // Puntero al hijo izquierdo
    Nodo* der;      // Puntero al hijo derecho
    string go;      // Codigo referente al Gen Ontology asociado
    string function;// Nombre de la función biológica
    double score;   // Puntaje del csv
    int FE;         // Factor de equilibrio
};

// Esta funcion tiene por proposito el insertar un termino en el arbol y luego verificar si está balanceado o se requiere de eso
//Como dato la variable BO, es un booleano el cual verifica si es que ha cambiado la altura del arbol o no
void InsercionBalanceado(Nodo** nodocabeza, bool* BO, string go, string function, double score) {
    Nodo* nodo = *nodocabeza;  // Nodo actual 
    Nodo* nodo1;               // Nodo auxiliar para rotaciones II,DD
    Nodo* nodo2;               // Nodo auxiliar para rotaciones dobles ID, DI

    if (nodo != nullptr) { //Si el nodo es nulo, se ve para insertar
        // Si el termino a insertar es menor que el del nodo actual, se va a la izq
        if (score < nodo->score) {
            // Llamada recursiva al subárbol izquierdo
            InsercionBalanceado(&(nodo->izq), BO, go, function, score);
            
            if (*BO == true) { //Luego de insertar se verifica si es que hay necesidad de balanceo
                // Todo esto depende del FE o factor de equilibrio del arbol en este momento (si es 2 o -2 se requiere balancearxd)
                if (nodo->FE == 1) {
                    // Si tenía +1 y creció la izquierda, ahora queda balanceado
                    nodo->FE = 0;
                    *BO = false;  // El árbol ya no creció en altura por lo cual, está balanceado
                } else if (nodo->FE == 0) {
                    // Si estaba balanceado y creció la izquierda, ahora tiene -1 (aun no se necesita balanceo, ya que tiene que ser 1,0,-1)
                    nodo->FE = -1;
                } else if (nodo->FE == -1) {
                    // Si ya tenía -1 y creció la izquierda, necesitamos rotación
                    nodo1 = nodo->izq;  // Tomamos el hijo izquierdo
                    
                    if (nodo1->FE <= 0) { //Se verifica el factor de equilibrio para saber que tipo de rotacion haremos
                        // Rotación II
                        nodo->izq = nodo1->der;  // El der del hijo pasa a ser izq del padre
                        nodo1->der = nodo;       // El padre pasa a ser el der del hijo
                        nodo->FE = 0;            // Se balancea
                        nodo = nodo1;            // El hijo ahora es la nueva raíz del subárbol
                    } else {
                        // Rotación ID 
                        nodo2 = nodo1->der;      // Tomamos el nieto (hijo derecho del hijo izquierdo)
                        nodo->izq = nodo2->der;  
                        nodo2->der = nodo;
                        nodo1->der = nodo2->izq;
                        nodo2->izq = nodo1;
                        
                        // Se ajustan los factores de equilibrio según el nieto
                        if (nodo2->FE == -1) {
                            nodo->FE = 1;
                        } else {
                            nodo->FE = 0;
                        }
                        if (nodo2->FE == 1) {
                            nodo1->FE = -1;
                        } else {
                            nodo1->FE = 0;
                        }
                        nodo = nodo2;  // El nieto ahora es la nueva raíz
                    }
                    nodo->FE = 0;  // La nueva raíz queda balanceada
                    *BO = false;   // El árbol ya no creció en altura
                }
            }
        } 
        // Si el termino a insertar es mayor, que el termino actual, se va hacia a la derecha y se repite algo similar a lo del lado izquierdo
        else if (score > nodo->score) {
            // Llamada recursiva al subárbol derecho
            InsercionBalanceado(&(nodo->der), BO, go, function, score);
            
            // Luego de insertar, se debe verificar si necesitamos rebalancear
            if (*BO == true) {
                if (nodo->FE == -1) {
                    // Si tenía -1 y creció la derecha, ahora queda balanceado
                    nodo->FE = 0;
                    *BO = false;
                } else if (nodo->FE == 0) {
                    // Si estaba balanceado y creció la derecha, ahora tiene +1
                    nodo->FE = 1;
                } else if (nodo->FE == 1) {
                    // Si ya tenía +1 y creció la derecha, necesitamos rotación
                    nodo1 = nodo->der;  // Tomamos el hijo derecho
                    
                    // Se verifica q tipo de rotacion se necesita
                    if (nodo1->FE >= 0) {
                        // Rotación DD 
                        nodo->der = nodo1->izq;  // El izq del hijo pasa a ser der del padre
                        nodo1->izq = nodo;       // El padre pasa a ser izq del hijo
                        nodo->FE = 0;            // Se balancea
                        nodo = nodo1;            // El hijo ahora es la nueva raíz
                    } else {
                        // Rotación DI 
                        nodo2 = nodo1->izq;      // Tomamos el nieto (hijo izquierdo del hijo derecho) y en esencia se hace lo mismo que con el anterior
                        nodo->der = nodo2->izq;  
                        nodo2->izq = nodo;
                        nodo1->izq = nodo2->der;
                        nodo2->der = nodo1;
                        
                        // Se ajustan los nuevos factores de equilibrio, para que asi el nieto sea la nueva raiz
                        if (nodo2->FE == 1) {
                            nodo->FE = -1;
                        } else {
                            nodo->FE = 0;
                        }
                        if (nodo2->FE == -1) {
                            nodo1->FE = 1;
                        } else {
                            nodo1->FE = 0;
                        }
                        nodo = nodo2;  // El nieto ahora es la nueva raíz
                    }
                    nodo->FE = 0;  
                    *BO = false;   
                }
            }
        } else {
            // Si por alguna razon el score fuera el mismo, pero el codigo GO fuera distinto, se insertaria a la derecha
            if (go != nodo->go) {
                InsercionBalanceado(&(nodo->der), BO, go, function, score);
            } else {
                // El término GO ya existe en el árbol
                cout << "El termino GO ya se encuentra en el arbol" << endl;
            }
        }
    } else {
        // Llegamos a una hoja nula, creamos nuevo nodo aquí
        nodo = new Nodo();
        nodo->izq = nullptr;      // Sin hijo izquierdo
        nodo->der = nullptr;      // Sin hijo derecho
        nodo->go = go;            // Se asigna código GO
        nodo->function = function;// Se asigna nombre de función
        nodo->score = score;      // Se asigna puntaje
        nodo->FE = 0;            
        *BO = true;               // Se indica que el arbol crecio en cuanto a su altura
    }
    *nodocabeza = nodo;  // Aqui se actualiza el puntero asociado al nodo padre
}

// Esta funcion busca un termino, con respecto a su score en el arbol
void Busqueda(Nodo* nodo, double score) {
    // Si llegamos a un nodo nulo, el término no existe
    if (nodo != nullptr) {
        // Si el score buscado es menor, se busca en subárbol izquierdo
        if (score < nodo->score) {
            Busqueda(nodo->izq, score);
        } 
        // Si el score buscado es mayor,se busca en subárbol derecho
        else if (score > nodo->score) {
            Busqueda(nodo->der, score);
        } else {
            // Si encontramos el termino se desplega informacion
            cout << endl;
            cout << "--- TERMINO ENCONTRADO ---" << endl;
            cout << "GO: " << nodo->go << endl;
            cout << "Funcion: " << nodo->function << endl;
            cout << "Score: " << nodo->score << endl;
            cout << "FE: " << nodo->FE << endl;
            cout << "--------------------------" << endl;
        }
    } else {
        //Si no se encuentra pues, se dice q no se encontró xd
        cout << "No se encontraron terminos con score: " << score << endl;
    }
}

// Función de reestructuración después de eliminación en subárbol izquierdo
void Restructura1(Nodo** nodocabeza, bool* BO) {
    Nodo *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    
    // Solo reestructurar si la altura disminuyó
    if (*BO == true) {
        if (nodo->FE == -1) {
            // Si tenía -1 y disminuyó izquierda, ahora queda balanceado
            nodo->FE = 0;
        } else if (nodo->FE == 0) {
            // Si estaba balanceado y disminuyó izquierda, ahora tiene +1
            nodo->FE = 1;
            *BO = false;  // La altura ya no disminuyó
        } else if (nodo->FE == 1) {
            // Si tenía +1 y disminuyó izquierda, necesitamos rotación
            nodo1 = nodo->der;  // Tomar hijo derecho
            
            if (nodo1->FE >= 0) {
                // Rotación simple DD
                nodo->der = nodo1->izq;
                nodo1->izq = nodo;
                
                // Ajustar factores de equilibrio
                if (nodo1->FE == 0) {
                    nodo->FE = 1;
                    nodo1->FE = -1;
                    *BO = false;
                } else if (nodo1->FE == 1) {
                    nodo->FE = 0;
                    nodo1->FE = 0;
                    *BO = false;
                }
                nodo = nodo1;  // Nueva raíz del subárbol
            } else {
                // Rotación doble DI
                nodo2 = nodo1->izq;
                nodo->der = nodo2->izq;
                nodo2->izq = nodo;
                nodo1->izq = nodo2->der;
                nodo2->der = nodo1;
                
                // Ajustar factores de equilibrio
                if (nodo2->FE == 1) {
                    nodo->FE = -1;
                } else {
                    nodo->FE = 0;
                }
                if (nodo2->FE == -1) {
                    nodo1->FE = 1;
                } else {
                    nodo1->FE = 0;
                }
                nodo = nodo2;    // Nueva raíz del subárbol
                nodo2->FE = 0;   // Balancear nueva raíz
            }
        }
    }
    *nodocabeza = nodo;  // Actualizar puntero
}

// Función de reestructuración después de eliminación en subárbol derecho
void Restructura2(Nodo** nodocabeza, bool* BO) {
    Nodo *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    
    if (*BO == true) {
        if (nodo->FE == 1) {
            // Si tenía +1 y disminuyó derecha, ahora queda balanceado
            nodo->FE = 0;
        } else if (nodo->FE == 0) {
            // Si estaba balanceado y disminuyó derecha, ahora tiene -1
            nodo->FE = -1;
            *BO = false;  // La altura ya no disminuyó
        } else if (nodo->FE == -1) {
            // Si tenía -1 y disminuyó derecha, necesitamos rotación
            nodo1 = nodo->izq;  // Se toma el hijo izquierdo
            
            if (nodo1->FE <= 0) {
                // Rotación simple II
                nodo->izq = nodo1->der;
                nodo1->der = nodo;
                
                // Se ajustan factores de equilibrio
                if (nodo1->FE == 0) {
                    nodo->FE = -1;
                    nodo1->FE = 1;
                    *BO = false;
                } else if (nodo1->FE == -1) {
                    nodo->FE = 0;
                    nodo1->FE = 0;
                    *BO = false;
                }
                nodo = nodo1;  // Nueva raíz del subárbol
            } else {
                // Rotación doble ID
                nodo2 = nodo1->der;
                nodo->izq = nodo2->der;
                nodo2->der = nodo;
                nodo1->der = nodo2->izq;
                nodo2->izq = nodo1;
                
                // Ajustar factores de equilibrio
                if (nodo2->FE == -1) {
                    nodo->FE = 1;
                } else {
                    nodo->FE = 0;
                }
                if (nodo2->FE == 1) {
                    nodo1->FE = -1;
                } else {
                    nodo1->FE = 0;
                }
                nodo = nodo2;    // Nueva raíz del subárbol
                nodo2->FE = 0;   // Balancear nueva raíz
            }
        }
    }
    *nodocabeza = nodo;  // Actualizar puntero
}

// Esta funcion auxiliar para encontrar el mayor elemento del subárbol izquierdo
void Borra(Nodo** aux1, Nodo** otro1, bool* BO) {
    Nodo *aux, *otro;
    aux = *aux1;
    otro = *otro1;
    
    // Se tiene que buscar el elemento más a la derecha del subárbol izquierdo
    if (aux->der != nullptr) {
        Borra(&(aux->der), &otro, BO);
        Restructura2(&aux, BO);  // Rebalancear después de la eliminación
    } else {
        // Encontramos el mayor elemento, copiar sus datos al nodo a eliminar
        otro->go = aux->go;
        otro->function = aux->function;
        otro->score = aux->score;
        aux = aux->izq;  // Se reemplaza por su hizo izq en caso de que este exista
        *BO = true;      
    }
    *aux1 = aux;    // Actualizar puntero auxiliar
    *otro1 = otro;  // Actualizar puntero del nodo a eliminar
}

// Esta funcion es para eliminar en un AVL y balancear o verificar si se encuentra balanceado posterior a la eliminacion
void EliminacionBalanceado(Nodo** nodocabeza, bool* BO, double score) {
    Nodo *nodo, *otro;
    nodo = *nodocabeza;
    
    // Si el árbol no está vacío
    if (nodo != nullptr) {
        // Se busca el nodo a eliminar por score
        if (score < nodo->score) {
            // Primero se busca en el subárbol izquierdo
            EliminacionBalanceado(&(nodo->izq), BO, score);
            Restructura1(&nodo, BO);  // Se rebalancea después de eliminar
        } else if (score > nodo->score) {
            // Luego en el subárbol derecho
            EliminacionBalanceado(&(nodo->der), BO, score);
            Restructura2(&nodo, BO);  // Nuevamente se rebalancea después de eliminar
        } else {
            // Nodo encontrado, se elimina
            otro = nodo;  // Se guarda la referencia al nodo a eliminar
            
            // Caso 1: Nodo con solo hijo izquierdo o es hoja
            if (otro->der == nullptr) {
                nodo = otro->izq;  // Se reemplaza por hijo izquierdo
                *BO = true;        // Indica que altura disminuyó
                delete otro;       // Libera memoria
            } 
            // Caso 2: Nodo con solo hijo derecho
            else if (otro->izq == nullptr) {
                nodo = otro->der;  // Se reemplaza por hijo derecho
                *BO = true;        // Indica que altura disminuyó
                delete otro;       // Libera memoria
            } 
            // Caso 3: Nodo con dos hijos
            else {
                // Primero se encuentra el mayor del subárbol izquierdo y reemplazar
                Borra(&(otro->izq), &otro, BO);
                Restructura1(&nodo, BO);  // Rebalancea
                delete otro;              // Libera memoria del nodo original
            }
            cout << "Termino GO eliminado correctamente." << endl;
        }
    } else {
        // Nodo no encontrado
        cout << "No se encontraron terminos con score: " << score << endl;
    }
    *nodocabeza = nodo;  // Se actualiza el puntero del nodo padre
}

// Se crea una funcion con preorden para crear el .dot para el graphviz
void PreOrden(Nodo* a, ofstream& fp) {
    if (a != nullptr) {
        // Crear etiqueta con función, score y factor de equilibrio
        string label = "\"" + a->function + "\\n" + to_string(a->score) + "\\nFE:" + to_string(a->FE) + "\"";
        
        // Procesar hijo izquierdo
        if (a->izq != nullptr) {
            // Si existe hijo izquierdo, crear conexión
            string labelIzq = "\"" + a->izq->function + "\\n" + to_string(a->izq->score) + "\\nFE:" + to_string(a->izq->FE) + "\"";
            fp << "    " << label << " -> " << labelIzq << " [label=\"izq\"];" << endl;
        } else {
            // Si no existe hijo izquierdo, crear nodo fantasma
            string nullName = "\"null" + to_string(a->score) + "l\"";
            fp << "    " << nullName << " [shape=point];" << endl;
            fp << "    " << label << " -> " << nullName << " [label=\"izq\"];" << endl;
        }
        
        // Procesar hijo derecho
        if (a->der != nullptr) {
            // Si existe hijo derecho, crear conexión
            string labelDer = "\"" + a->der->function + "\\n" + to_string(a->der->score) + "\\nFE:" + to_string(a->der->FE) + "\"";
            fp << "    " << label << " -> " << labelDer << " [label=\"der\"];" << endl;
        } else {
            // Si no existe hijo derecho, crear nodo fantasma
            string nullName = "\"null" + to_string(a->score) + "r\"";
            fp << "    " << nullName << " [shape=point];" << endl;
            fp << "    " << label << " -> " << nullName << " [label=\"der\"];" << endl;
        }

        // Recorrer recursivamente subárboles
        PreOrden(a->izq, fp);
        PreOrden(a->der, fp);
    }
}

// Función para generar el gráfico del árbol usando Graphviz
void GenerarGrafo(Nodo* ArbolInt) {
    // Verificar si el árbol está vacío
    if (ArbolInt == nullptr) {
        cout << "El arbol esta vacio. No se puede generar grafo." << endl;
        return;
    }
    
    
    ofstream fp("grafo.txt");
    if (!fp.is_open()) {
        cout << "Error al crear archivo grafo.txt" << endl;
        return;
    }
    
   
    fp << "digraph G {" << endl;
    fp << "    node [style=filled fillcolor=yellow shape=box];" << endl;  
    fp << "    rankdir=TB;" << endl;  
    
    
    PreOrden(ArbolInt, fp);
    
  
    fp << "}" << endl;
    fp.close();
    
    // Ejecutar Graphviz para generar la imagen PNG
    system("dot -Tpng -ografo.png grafo.txt");
    cout << "Archivo grafo.png generado correctamente." << endl;
}

// Función para cargar términos GO desde archivo CSV (limitado a 12 términos)
void CargarDesdeArchivo(Nodo** raiz, const char* filename) {
    // Abrir archivo CSV
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << filename << endl;
        return;
    }

    string linea;
    bool primeraLinea = true;  // Para saltar el encabezado
    int contador = 0;          // Contador de términos cargados
    int maxTerminos = 12;      // Límite máximo de términos a cargar
    
  
    while (getline(archivo, linea) && contador < maxTerminos) {
        if (primeraLinea == true) {
            primeraLinea = false;  
            continue;
        }
        
        size_t pos1 = linea.find(';');  
        size_t pos2 = linea.find(';', pos1 + 1); 
        
        // Si encontramos los separadores, procesar la línea
        if (pos1 != string::npos && pos2 != string::npos) {
            // Extraer datos de la línea
            string go = linea.substr(0, pos1);  // Código GO
            string function = linea.substr(pos1 + 1, pos2 - pos1 - 1);  // Nombre función
            double score = stod(linea.substr(pos2 + 1));  
            
            // Insertar en el árbol AVL
            bool inicio = false;
            InsercionBalanceado(raiz, &inicio, go, function, score);
            
            // Contar términos insertados 
            if (inicio == true) {
                contador++;  // Solo contar si realmente se insertó 
                cout << "Cargado: " << function << " (Score: " << score << ")" << endl;
            }
        }
    }
    
    // Cerrar archivo y mostrar resultado
    archivo.close();
    cout << "Se cargaron " << contador << " terminos GO desde el archivo." << endl;
}

// Función para insertar un término GO manualmente
void InsertarManual(Nodo** raiz) {
    string go, function;
    double score;
    
    // Solicitar datos al usuario
    cout << "Ingresar codigo GO (ej: GO:0090398): ";
    cin >> go;
    cin.ignore();  // Limpiar buffer del teclado
    
    cout << "Ingresar nombre de la funcion: ";
    getline(cin, function);  // Leer línea completa para la función
    
    cout << "Ingresar score: ";
    cin >> score;
    
    // Insertar en el árbol
    bool inicio = false;
    InsercionBalanceado(raiz, &inicio, go, function, score);
    cout << "Termino GO insertado correctamente." << endl;
}

// para liberar la memoria de todo
void liberarMemoria(Nodo* nodo){
    // Caso base: si el nodo es nulo, terminar recursión
    if (nodo == nullptr){
        return;
    }

    // Liberar primero los subárboles izquierdo y derecho
    liberarMemoria(nodo->izq);
    liberarMemoria(nodo->der);
    
    // Finalmente se libera el nodo actual
    delete nodo;
}

// Función para mostrar el menú principal
int Menu() {
    int Op;
    do {
        // Mostrar opciones del menú
        cout << endl;
        cout << "--- Menu Arbol AVL GO (Ordenado por Score) ---" << endl;
        cout << "1. Insertar termino GO" << endl;
        cout << "2. Buscar por Score" << endl;
        cout << "3. Eliminar por Score" << endl;
        cout << "4. Generar grafo" << endl;
        cout << "5. Recargar desde archivo" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> Op;
    } while (Op < 0 || Op > 5);  
    return Op;
}

int main(int argc, char** argv) {
    int opcion;
    Nodo* raiz = nullptr;  //Se inicializa el arbol vacio

    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <archivo_funciones_GO.csv>" << endl;
        cout << "Cargando datos limitados por defecto..." << endl;
        CargarDesdeArchivo(&raiz, "funciones_GO.csv");
    } else {
        // Se cargan datos desde el archivo deseado
        cout << "Cargando datos limitados desde: " << argv[1] << endl;
        CargarDesdeArchivo(&raiz, argv[1]);
    }
    
  
    GenerarGrafo(raiz);

   
    do {
        opcion = Menu();  
        
    
        switch(opcion) {
            case 1: 
                
                InsertarManual(&raiz);
                GenerarGrafo(raiz);  
                break;
            case 2: {
                
                double score;
                cout << "Ingrese el score a buscar: ";
                cin >> score;
                Busqueda(raiz, score);
                break;
            }
            case 3: {
                
                double score;
                cout << "Ingrese score a eliminar: ";
                cin >> score;
                bool inicio = false;
                EliminacionBalanceado(&raiz, &inicio, score);
                GenerarGrafo(raiz);  
                break;
            }
            case 4:
                
                if (raiz == nullptr) {
                    cout << "El arbol esta vacio. Inserte terminos antes de volver a intentarlo" << endl;
                } else {
                    GenerarGrafo(raiz);
                }
                break;
            case 5:
                // Se recargan los datos desde archivo
                // Liberar memoria antes de recargar
                liberarMemoria(raiz);
                raiz = nullptr;
                if (argc == 2) {
                    CargarDesdeArchivo(&raiz, argv[1]);
                } else {
                    CargarDesdeArchivo(&raiz, "funciones_GO.csv");
                }
                GenerarGrafo(raiz);
                break;
            case 0:
                
                cout << "Saliendo del programa" << endl;
                liberarMemoria(raiz);  // Se libera toda la memoria
                raiz = nullptr;        // Asi se evita un puntero colgante
                break;
            default:
                
                cout << "Opcion no valida. Intente nuevamente" << endl;
        }
    } while(opcion != 0);  

    return 0;
}