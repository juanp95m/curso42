# Remove Invalid Parentheses (RIP) - Explicación Paso a Paso

El objetivo de RIP es eliminar la cantidad mínima necesaria de paréntesis mal cerrados explorando todas las combinaciones mediante backtracking.

## Código Principal (Core de Backtracking)
```c
while (str[pos]) 
{
    if (str[pos] == '(' || str[pos] == ')')  // Solo nos importan los paréntesis
    {
        char tmp = str[pos];     
        str[pos] = ' ';          // 1. MARCAR estado (Borro este paréntesis reemplazándolo por espacio)
        rip(str, remove, pos + 1, deleted + 1); // 2. RECURSIÓN (Avanzo con 1 eliminado más)
        str[pos] = tmp;          // 3. DESHACER estado (Backtracking: devuelvo el paréntesis)
    }
    pos++; // Avanzamos al siguiente caracter, independientemente de borrar el actual
}
```

## Simulación Paso a Paso 
Supongamos "())(", donde `invalid()` dice que sobran 2 elementos (un `)` extra, y un `(` extra abierto al final). Target `remove = 2`. `deleted` cuenta cuantos llevamos.

### Visualización en Árbol
```text
[ Nivel 0 ] pos=0, deleted=0, str="())("
 |
 |-- pos=0, str[0]='(': Borra '(' => " '))( "
 |    |
 |    [ Nivel 1 ] pos=1, deleted=1, str=" '))( "
 |     |
 |     |-- pos=1, str[1]=')': Borra ')' => " '  )( "
 |     |    |
 |     |    [ Nivel 2 ] pos=2, deleted=2 (Limíte!). 
 |     |    Es válido " '  )( "? NO. Retorna sin hacer print.
 |     |
 |     |-- pos=2, str[2]=')': Borra ')' ...
 |
 |-- pos=1, str[1]=')': (No borrar [0], borra [1]) => "( ')( "
 |    |
 |    [ Nivel 1 ] pos=2, deleted=1, str="( ')( "
 |     |
 |     |-- pos=3, str[3]='(': Borra '(' => "( ')  "
 |          |
 |          [ Nivel 2 ] pos=3, deleted=2 (Límite max de eliminaciones).
 |          Es válido "( ')  "? (Quitando los espacios "()"). ¡SI ES VÁLIDO! IMPRIME: "( ) "
 |
 ... Continúa probando otras iteraciones moviendo pos++ ...
```

## Narrativa
1. Calculamos previamente cuántos paréntesis inválidos deberíamos quitar (`remove`).
2. Recorremos el string con un bucle de izquierda a derecha usando `pos`.
3. Si encontramos un `(` o `)`, probamos a "borrarlo", tapándolo temporalmente con un espacio vacío `' '`.
4. Hacemos recursión incrementando `deleted+1` para indicar que ya borramos 1, y pasamos al siguiente caracter `pos+1`.
5. **Backtracking:** Una vez que evaluamos esa rama, reconstruimos la cadena original devolviendo el `(` o `)` donde estaba (`str[pos] = tmp`), y seguimos el bucle buscando otros sitios para eliminar.
6. Si la cantidad deseadas de borrados se alcanza (`deleted == remove`), llamamos a `invalid` sobre la cadena. Si da 0, significa que la cadena borrada es un set de paréntesis perfecto -> Lo imprimimos.