El funcionamiento es

El programa implementa un sistema de gestión de contenedores en un
**puerto seco** mediante el uso de **pilas con arreglos**.

-   No es posible colocar más de `n` contenedores en una misma pila.
-   Solo se pueden tener `m` pilas en total.
-   Cada contenedor posee un identificador único.
-   Para retirar un contenedor es necesario mover los que se encuentran
    sobre él hacia otras pilas disponibles, mostrando por pantalla cada
    movimiento.
-   El tamaño máximo de las pilas (`n`) y el número de pilas (`m`) se
    leen como **argumentos desde la línea de comandos** (`argc` y
    `argv`).

Ejemplo:

``` bash
./Laboratorio2_Act2 3 5
```

donde: - `3` → altura máxima de cada pila (`n`). - `5` → número de pilas
(`m`).


Uso del programa

Compilación

``` bash
g++ main.cpp -o Laboratorio2_Act2
```

Ejecución

``` bash
./Laboratorio2_Act2 <n> <m>
```

Ejemplo:

``` bash
./Laboratorio2_Act2 4 3
```

Un Menú interactivo

El programa despliega un menú con las siguientes opciones:

    === MENU ===
    1. Ingresar contenedor
    2. Retirar contenedor
    3. Ver pilas
    0. Salir

Opciones explicadas.

-   **1. Ingresar contenedor** → Solicita el ID y lo coloca en la
    primera pila disponible con espacio.
-   **2. Retirar contenedor** → Solicita el ID, localiza el contenedor y
    mueve los que están encima a otras pilas antes de retirarlo.
-   **3. Ver pilas** → Muestra el estado actual de todas las pilas en
    pantalla.
-   **0. Salir** → Termina el programa.

A considerar

-   Si todas las pilas están llenas, no es posible ingresar más
    contenedores.
-   Si no existe espacio para mover un contenedor en el proceso de
    retiro, la operación se interrumpe.
-   Se muestran todos los movimientos realizados en pantalla para
    mantener claridad de la gestión.
-   El programa define límites máximos internos:
    -   `MAX_N = 100` (altura máxima por pila).
    -   `MAX_M = 20` (número máximo de pilas).
