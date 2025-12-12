**Algoritmo de Needleman-Wunsch**

##
Descripcion del proyecto:

El proyecto se encarga de implementar el algoritmo de Needleman-Wunsch, buscando hacer el alineamiendo optimo de dos secuencias de nucleotidos

Como objetivo principal este posee verificar una maxima similitud evolutiva entre secuencias ortologas en este caso

Para este caso se estudió el alineamiento del Gen del Citocromo C somatico (CYCS)

##
Este codigo, representa adecuamente el algoritmo de Needleman-Wunsch a través de una programacion dinamica, con respecto a la creacion de la matriz

##
**Compilacion**

-Para la compilacion adecuada del codigo debe escribir en al terminar:

"g++ -o needleman Valdivia_Nicolas_Proyecto.cpp"

**Luego su ejecucion**

-para ejecutar se requieren de 4 argumentos para poder ejecutar adecuadamente el codigo

"./needleman -C1 sec1.txt(fasta) -C2 sec2.txt(fasta) -U (archivo de la matriz U) -V (la cantidad del gap, ej: -2)"

##
**Salida**
Como salida el programa imprime los siguientes resultados:

-Puntaje Optimo de la matriz

-Estadisticas: Conteo de matches, mismatches y gaps

-Similitud global: Porcentaje de identidad basado en el alineamiento

-Alineamiento por bloques de 80 bases (luego de eso se hace un salto de espacio)

-Generacion del Graphviz

##
**Finalmente**

Se libera la memoria que usa la matriz F y la matriz U