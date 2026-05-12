# Permutations - Explicación Paso a Paso

El código de `permutations` utiliza **backtracking** para generar todas las combinaciones posibles variando el orden de los caracteres.

## Código Principal (Core de Backtracking)
```c
while (i < size)
{
    if (!used[i])
    {
        used[i] = 1;          // 1. MARCAR estado (Elegir)
        result[pos] = str[i]; // 2. CONSTRUIR candidato
        permu(str, result, used, pos + 1, size); // 3. RECURSIÓN (Explorar)
        used[i] = 0;          // 4. DESHACER estado (Backtracking)
    }
    i++;
}
```

## Simulación Paso a Paso para "abc"

### Niveles de Recursividad
- **Nivel 0 (pos = 0):** Se elige la 1ª letra.
- **Nivel 1 (pos = 1):** Se elige la 2ª letra de las restantes.
- **Nivel 2 (pos = 2):** Se elige la 3ª letra de las restantes.
- **Nivel 3 (pos = 3):** Fin (pos == size), se imprime.

### Visualización en Árbol
```text
[ Nivel 0 ] pos=0, result=___
 |
 |-- i=0: Marca 'a' -> result="a__", used=[1,0,0]
 |    |
 |    [ Nivel 1 ] pos=1, result="a__"
 |     |
 |     |-- i=1: Marca 'b' -> result="ab_", used=[1,1,0]
 |     |    |
 |     |    [ Nivel 2 ] pos=2, result="ab_"
 |     |     |
 |     |     |-- i=2: Marca 'c' -> result="abc", used=[1,1,1]
 |     |          |
 |     |          [ Nivel 3 ] pos=3 == size -> IMPRIME: "abc"
 |     |          | (Backtrack: desmarca 'c', used=[1,1,0])
 |     | 
 |     | (Backtrack: desmarca 'b', used=[1,0,0])
 |     |
 |     |-- i=2: Marca 'c' -> result="ac_", used=[1,0,1]
 |          |
 |          [ ... explora y encuentra "acb" ... ]
 |
 |-- i=1: Marca 'b' -> result="b__", used=[0,1,0]
 |    [ ... explora y encuentra "bac", "bca" ... ]
 |
 |-- i=2: Marca 'c' -> result="c__", used=[0,0,1]
      [ ... explora y encuentra "cab", "cba" ... ]
```

## Narrativa
1. Iteramos sobre las letras posibles. Si la letra `i` no está usada, la marcamos.
2. Añadimos la letra elegida a la posición actual de nuestro string resultante.
3. Llamamos a la misma función incrementando `pos` (bajamos un nivel) para rellenar el siguiente hueco.
4. Cuando el hueco actual es igual a la longitud total, la permutación está completa y se imprime. Tras imprimir (o tras probar una rama parcial fallida, si existiese), volvemos y **deshacemos** (`used[i]=0`) la última letra puesta para probar con la siguiente en el `while`.