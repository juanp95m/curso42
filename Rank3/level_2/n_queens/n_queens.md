# N-Queens - Explicación Paso a Paso

El problema de las N-Reinas busca colocar N reinas en un tablero de NxN sin que se ataquen.

## Código Principal (Core de Backtracking)
```c
while (current < size) // current representa la FILA donde intentamos colocarla
{
    if (validation(table, current, col)) // ¿Es seguro colocarla aquí?
    {
        table[col] = current;            // 1. MARCAR estado (Anotar fila elegida para esta columna)
        n_queen(0, col + 1, size, table); // 2. RECURSIÓN (Explorar la siguiente columna)
        // Backtracking implícito: No hace falta deshacer table[col] porque en la siguiente iteración se sobrescribe si falla.
    }
    current++; 
}
```

## Simulación Paso a Paso para "4" reinas (Fragmento)

- `col`: Nivel actual (la columna en la que estamos).
- `current`: La fila en esa columna.
- `table[x]`: Guarda la fila donde se puso la reina en la columna `x`.

### Visualización en Árbol
```text
[ Nivel 0 ] col=0, intentando colocar reina en columna 0
 |
 |-- current=0 (Fila 0): Seguro. table[0] = 0.
 |    |
 |    [ Nivel 1 ] col=1, intentando en columna 1
 |     |
 |     |-- current=0: INSEGURO (Misma fila)
 |     |-- current=1: INSEGURO (Diagonal)
 |     |-- current=2: Fila 2. Seguro. table[1] = 2.
 |     |    |
 |     |    [ Nivel 2 ] col=2, intentando columna 2
 |     |     |
 |     |     |-- current=0 (Inseguro), current=1 (Inseguro), current=2 (Inseguro), current=3 (Inseguro)
 |     |     | MUERTO. Retrocede a Nivel 1.
 |     | 
 |     |-- current=3: Fila 3. Seguro. table[1] = 3.
 |          |
 |          [ Nivel 2 ] col=2, intentando columna 2
 |           |-- current=0: INSEGURO
 |           |-- current=1: Seguro. table[2]=1.
 |                |
 |                [ Nivel 3 ] col=3, intentando en columna 3 ...
```

## Narrativa
1. Por cada "nivel recursivo", visitamos una columna entera.
2. Dentro de esa columna, intentamos poner la reina en cada fila (`current` iterando de 0 a `size`).
3. La función `validation` verifica si choca de frente o en diagonal con reinas anteriores. 
4. Si es seguro, guardamos la posición en nuestro array unidimensional (`table[col] = current`) y pasamos al siguiente nivel (`col+1`).
5. **Backtracking:** Si al avanzar vemos que ninguna posición es válida en la columna siguiente, la recursión termina sin avanzar, volvemos a la capa anterior, y el bucle avanza al siguiente `current++` para cambiar la posición anterior.