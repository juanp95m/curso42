# Teoría del Backtracking - Paralelismos

El **Backtracking** (Vuelta Atrás) es un mecanismo para explorar sistemáticamente un montón de posibles "decisiones". Cuando tomas una secuencia de decisiones y ves que no funciona, "das un paso atrás" deshaciendo el último movimiento y pruebas con otra opción.

A nivel de código en C (y en los ejercicios de nivel 2 y rank 3 de la escuela), habitualmente todos comparten fases muy estructuradas:

## Las 5 Fases Estándar del Backtracking

### 1. La Condición de Parada (Caso Base)
Si no tenemos condición de parada, la recursividad sería infinita.
* **Permutations:** `if (pos == size)` -> Rellenados los mismos huecos que hay letras.
* **N_Queens:** `if (col == size)` -> Hemos puesto reinas en todas las columnas requeridas.
* **Powerset:** `if (ixn == size)` -> Hemos valorado todos y cada uno de los números del array inicial (cogiendolos o no).
* **RIP:** `if (deleted == remove)` -> Hemos "arrancado" la cantidad de paréntesis mal puestos que nos dijeron usando validation.

Cuando llegamos aquí, valoramos: "¿Es la solución actual correcta o válida?", si lo es se imprime, y en cualquier caso hacemos `return ;` para **volver atrás**.

### 2. El Iterador / Explorador (Tomar la decisión)
Siempre necesitamos explorar opciones, habitualmente a través de opciones posibles o índices de un elemento.
* **Permutations:** `while(i < size)` Prueba a poner absolutamente cualquier carácter en la posición actual prestando atención al array `used`.
* **N_Queens:** `while(current < size)` Prueba todas las filas (current) posibles dentro de la columna actual.
* **Powerset:** Opción Binaria Estática. (No hay `while`). La decisión se ramifica en dos recursiones idénticas: La primera ignorando al número actual y la segunda asimilando el número en nuestro buffer.
* **RIP:** `while(str[pos])` Recorre todos los caracteres y, si son eliminables, trata de borrarlo temporalmente a ver qué pasaría.

### 3. Marcado (Avance de Estado)
Modificamos nuestras variables locales o arrays para dejar rastros de la pequeña decisión tomada.
* **Permutations:** `used[i] = 1; result[pos] = str[i];`
* **N_Queens:** `table[col] = current;`
* **Powerset:** `buffer[ixc] = nums[ixn];`
* **RIP:** `str[pos] = ' ';`

### 4. La Recursión (Búsqueda en Profundidad / DFS)
Una vez hecho el cambio de arriba, "hacemos lo mismo para el nivel/paso siguiente".
* **Permutations:** `permu(..., pos + 1 ...)` -> Pasamos al hueco `pos + 1`.
* **N_Queens:** `n_queen(..., col + 1 ...)` -> Pasamos a revisar la columna siguiente.
* **Powerset:** `powerset(ixn + 1, ...)` -> Pasamos a estudiar el indice numérico siguiente.
* **RIP:** `rip(..., pos + 1, deleted + 1)` -> Pasamos a estudiar el carácter siguiente diciendo que ya hemos restado un error.

### 5. Desmarcar (El auténtico Backtrack - "Volver a dejar limpio")
Si la recursión de arriba devuelve algo y el bucle sigue bajando, significa que esa "elección de rama de árbol" ya ha sido completamente explorada hasta el fondo o fue un fallo. ¡Necesitamos deshacer nuestro movimiento antes de probar con el siguiente elemento del bucle!
* **Permutations:** `used[i] = 0;` (La desmarcamos para que en la próxima iteración pueda usarse de otra forma).
* **N_Queens:** (Implícito) Al no tener un array `used`, al hacer `current++`, sobreescribiremos amigablemente sobre `table[intento=nuevo_current]` en el próximo nivel.
* **Powerset:** (Implícito) Al devolver de forma recursiva, la escritura en array recede por índices.
* **RIP:** `str[pos] = tmp;` (Devolvemos el `)` o `(` sacado de la basura temporal donde guardamos la variable para que el string vuelva a estar íntegro para otra prueba posterior).

---

## Esquema Visual Comparado de Árbol

La raíz del árbol es siempre un nivel `0`.
- En **Permutations** avanzas abriendo tantas ramas como letras esten libres (`size - pos`).
- En **N-Queens** abres tantas ramas como celdas por columna no estén atacadas por cruces previos en `validation()`.
- En **Powerset** siempre, siempre abres 2 ramas: "Tomar o no tomar"
- En **RIP** abres una rama por cada "supuesto eliminado posible". Moverlo de uno en uno o saltárselo. 

# El Patrón Universal del Backtracking

Todo ejercicio de Backtracking puede reducirse a una **Misma Estructura Maestra**. Si dominas esta plantilla mental, podrás enfrentarte a `permutations`, `n_queens`, `powerset`, `rip` o cualquier otro problema similar, viéndolos solo como variaciones de una misma fórmula.

---

## 🏗️ La Plantilla Maestra (El "Esqueleto")

Imagina el backtracking como un explorador en un laberinto. Esta es la rutina que sigue en cada intersección:

```c
void resolver(Estado_Actual)
{
    // 1. CASO BASE (Condición de parada)
    // ¿He llegado al final del camino o a la meta?
    if (hemos_terminado(Estado_Actual)) 
    {
        if (es_solucion_valida(Estado_Actual))
            imprimir(Estado_Actual);
        return; // ¡Vuelve atrás y prueba otra ruta!
    }

    // 2. ITERADOR DE OPCIONES
    // ¿Qué caminos (opciones) puedo tomar desde aquí?
    for (cada_opcion_posible) 
    {
        // 3. VALIDACIÓN
        // ¿Es seguro/lógico tomar esta opción?
        if (es_valida(opcion)) 
        {
            // 4. DO (HACER / MARCAR)
            // Aplico la opción al estado actual ("Dejo una miga de pan")
            aplicar(opcion); 

            // 5. RECURSIÓN (AVANZAR)
            // Bajo al siguiente nivel habiendo tomado esta decisión
            resolver(Estado_Siguiente); 

            // 6. UNDO (DESHACER / BACKTRACKING PURO)
            // Al volver del nivel inferior, deshago mi decisión
            // para poder probar la siguiente opción del bucle ("Recojo la miga")
            deshacer(opcion); 
        }
    }
}
```

A continuación, vamos a encajar cada uno de tus 4 ejercicios en este mismo esqueleto exacto.

---

## 1. Permutations: El Modelo Clásico (Reordenamiento)

**Objetivo:** Elegir qué letra va en cada "hueco".
**Opciones por nivel:** Todas las letras del string original.

```c
void permu(char *str, char *result, int *used, int pos, int size)
{
    // 1. CASO BASE (Llené todos los huecos)
    if (pos == size) {
        result[size] = '\0';
        puts(result);
        return;
    }

    // 2. ITERADOR DE OPCIONES (Pruebo TODAS las letras [i])
    int i = 0;
    while (i < size) {
        
        // 3. VALIDACIÓN (¿Esta letra está libre?)
        if (!used[i]) {
            
            // 4. DO (La marco como usada y la pongo en el resultado)
            used[i] = 1;         
            result[pos] = str[i];
            
            // 5. RECURSIÓN (Paso al siguiente 'hueco' -> pos + 1)
            permu(str, result, used, pos + 1, size);
            
            // 6. UNDO (La libero para probar con otras letras luego)
            used[i] = 0;
        }
        i++;
    }
}
```
* **Diferenciador:** Se basa en un array externo `used` para rastrear qué hemos cogido. El UNDO explícito (`used[i] = 0`) es clave.

---

## 2. N-Queens: El Modelo de Tablero / Coordenadas

**Objetivo:** Decidir en qué fila poner la reina, por cada columna.
**Opciones por nivel:** Todas las filas (de `0` a `size - 1`).

```c
void n_queen(int current_row, int col, int size, int *table) 
{
    // 1. CASO BASE (Llegué a la última columna imaginada)
    if (col == size) {
        imprimir_tablero(table);
        return;
    }

    // 2. ITERADOR DE OPCIONES (Prueba todas las filas posibles en esta columna)
    while (current_row < size) {
        
        // 3. VALIDACIÓN (¿Nos atacan otras reinas por fila/diagonal?)
        if (validation(table, current_row, col)) {
            
            // 4. DO (Guardo la fila elegida en esta columna)
            table[col] = current_row;
            
            // 5. RECURSIÓN (Avanzo a la SIGUIENTE COLUMNA -> col + 1)
            n_queen(0, col + 1, size, table);
            
            // 6. UNDO (¡Implícito!) 
            // En el siguiente ciclo del while, `table[col]` se sobrescribirá
            // pacíficamente con el nuevo `current_row`. No hay que borrar nada.
        }
        current_row++; 
    }
}
```
* **Diferenciador:** La validación es compleja (cruceros verticales/diagonales), pero el *Undo* es automático por cómo usamos el array.

---

## 3. Powerset: El Modelo Binario (Tomar / Ignorar)

**Objetivo:** Formar subconjuntos buscando una suma.
**Opciones por nivel:** ¡Solo hay DOS opciones! O coges el número, o pasas de él. En lugar de un bucle `while` o `for`, ponemos las 2 opciones a mano.

```c
void powerset(int ixn, int size, int ixc, int sum)
{
    // 1. CASO BASE (He mirado todos los números del array original)
    if (ixn == size) {
        // ¿Suman lo que pido? (Mini-validación final)
        if (sum == target)
            imprimir(buffer);
        return;
    }

    // --- OPCIÓN 1: IGNORAR EL NÚMERO ---
    // DO / UNDO: No hay. No lo guardamos ni sumamos.
    // RECURSIÓN: (Paso al siguiente numero)
    powerset(ixn + 1, size, ixc, sum);


    // --- OPCIÓN 2: TOMAR EL NÚMERO ---
    // 4. DO (Lo meto en el buffer)
    buffer[ixc] = nums[ixn];
    
    // 5. RECURSIÓN (Avanzo índice array original Y avanzo índice de mi buffer)
    powerset(ixn + 1, size, ixc + 1, sum + nums[ixn]);
    
    // 6. UNDO (¡Implícito!)
    // Cuando vuelva, como retrocede mi `ixc`, el próximo número que coja en otra
    // rama sobrescribirá esta posición del buffer.
}
```
* **Diferenciador:** Falta el bucle `while`. Las "opciones" son simplemente 2 caminos duros codificados uno debajo del otro.

---

## 4. RIP (Remove Invalid Parentheses): Modelo Búsqueda y Modificación

**Objetivo:** Borrar 'N' caracteres específicos.
**Opciones por nivel:** Probar a "borrar" cada paréntesis que encuentre desde mi posición hasta el final del string.

```c
void rip(char *str, int remove, int pos, int deleted)
{
    // 1. CASO BASE (Ya borré la cantidad de símbolos requeridos)
    if (deleted == remove) {
        if (!invalid(str)) // ¿Quedó balanceado tras los borrados?
            puts(str);
        return;
    }

    // 2. ITERADOR DE OPCIONES (Busco hacia adelante un candidato a borrar)
    while (str[pos]) {
        
        // 3. VALIDACIÓN (Solo quiero borrar '(' o ')')
        if (str[pos] == '(' || str[pos] == ')') {
            
            // 4. DO (HACER: Lo sustituyo por un espacio en blanco para "desactivarlo")
            char tmp = str[pos]; // Guardo el original
            str[pos] = ' ';
            
            // 5. RECURSIÓN (Avanzo una posición y registro {deleted + 1})
            rip(str, remove, pos + 1, deleted + 1);
            
            // 6. UNDO (Lo restauro de la ceniza para probar borrando otro)
            str[pos] = tmp;
        }
        pos++; 
    }
}
```
* **Diferenciador:** Modificamos el estado mutando el string en el acto. El `Undo` es super importante aquí (`str[pos] = tmp`) para restaurar el orden.

---

## 🎓 Cuadro Resumen Comparativo

| Concepto | Permutations | N-Queens | Powerset | RIP |
| :--- | :--- | :--- | :--- | :--- |
| **¿Qué es un "Nivel"?** | Cada "hueco" del string final | Cada columna del tablero | Cada número a mirar | Número de borrados acumulados |
| **Iterador/Opciones** | Todas las letras de `str` (`while`) | Todas las filas / `current` (`while`) | 2 Vías Singulares (Tomar o NO) | Buscar hacia la derecha (`while`) |
| **Caso Base (Stop)** | Llené `size` posiciones | Llegué a la columna `size` | Valoré el elemento `size` | Alcancé objetivo `removed` |
| **Validación** | ¡Si `!used[i]`! | ¡Si `validation(f, c)`! (Reglas Reina) | Ninguna, siempre podemos tomar | Que sea `(` o `)` |
| **El "DO"** | Lo marco `used=1` | Lo anoto en `table[col]` | Lo guardo en `buffer[ixc]` | Pongo en blanco la letra `=' '`|
| **El "UNDO"** | Lo libero `used=0` | *No se hace, se sobrescribe* | *No se hace, se sobrescribe* | Restauro letra `tmp` |

Si te mantienes fiel a esta estructura: **(Condición) -> (Bucle Opciones) -> (Verificar) -> (Hacer) -> (Recursión) -> (Deshacer)** jamás te desorientarás al aprender un backtracking en C.