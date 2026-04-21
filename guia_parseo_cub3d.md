# 🏰 Guía de Parseo cub3D: Tu Hoja de Ruta Actual

He analizado tu código en `42cursus/cub3D`. Tienes una estructura excelente (`t_game` dividida lógicamente) y el esqueleto de lectura del archivo (`get_next_line` iterativo) ya está montado. 

Esta guía parte exactamente de lo que tienes escrito y te indica los pasos para terminarlo con rigor 42.

---

## 1. Análisis de tu Estado Actual y Correcciones Inmediatas

Antes de avanzar, hay un par de detalles en tu código actual que debes corregir para que el programa no colapse:

### Correcciones en `src/parsing.c`
En tu función `analize_line`:
1.  **El error lógico de las líneas vacías**:
    Tienes `if (!is_empty_line(line) == 1) return ;`. La lógica de `is_empty_line` (en tu `utils.c`) devuelve `1` si está vacía y `0` si tiene contenido. 
    Tu condición actual hace que si la línea **NO** está vacía, se salga de la función. Debe ser:
    ```c
    if (is_empty_line(line))
        return ;
    ```
2.  **Argumentos Faltantes**:
    Tus llamadas a `save_texture()` y `save_color()` no le están pasando argumentos, pero en `utils.c` esperas recibir el `line`, el `game` y la dirección. Debes actualizarlas:
    ```c
    if (ft_strncmp("NO ", line, 3) == 0)
        save_texture(line, game, NORTH);
    // ...
    else if (ft_strncmp("F ", line, 2) == 0)
        save_color(line, game, 'F'); // O pasándole un enum/macro si lo prefieres
    ```

---

## 2. Hoja de Ruta: Paso a Paso para Completar el Parseo

Aquí tienes las fases ordenadas para terminar de rellenar tu `t_game`.

### FASE 1: Terminar las Texturas (`save_texture` en `utils.c`)
Tu función recorta la ruta bien usando `ft_strtrim`, pero le falta la **validación estricta**.

**Lo que debes añadir a `save_texture`:**
1.  **Comprobación de Duplicados**: Si `game->map.route_north` ya tiene un valor (no es NULL) y te vuelve a llegar un `NO`, debes lanzar un error (el mapa es inválido).
2.  **Verificar que el archivo existe**: Antes de guardar el `clean_route`, usa `open(clean_route, O_RDONLY)` temporalmente. Si devuelve `< 0`, la ruta está mal o el archivo no existe. Lanza error, haz `free` del string y sal. (No olvides hacer `close` del `fd` si se abrió bien).

### FASE 2: Implementar los Colores (`save_color` en `utils.c`)
El pseudocódigo que te dejaste en los comentarios es perfecto. Vamos a llevarlo a código C mentalmente.

**Pasos para programar `save_color(char *line, t_game *game, char id)`:**
1.  **Saltar espacios iniciales**: Como en las texturas, salta la 'F' o 'C' y los espacios.
2.  **Limpiar y Dividir**:
    *   Usa `clean_line = ft_strtrim(&line[i], " \t\n")`.
    *   Usa `char **rgb = ft_split(clean_line, ',')`.
    *   Haz `free(clean_line)`.
3.  **Validar Formato Estricto (¡Cuidado con la Norminette!)**:
    *   Asegúrate de que el array `rgb` tiene **exactamente 3 elementos**. Si no, error.
    *   Itera sobre cada string (`rgb[0]`, `rgb[1]`, `rgb[2]`). Verifica que todos sus caracteres sean dígitos con `ft_isdigit`. Si hay un solo carácter raro (`"220a"` o un espacio extra raro), error.
4.  **Convertir y Comprobar Rango**:
    *   Usa `ft_atoi` en cada uno.
    *   Si algún número es `< 0` o `> 255`, error.
5.  **Codificar en `uint32_t` (RGBA para MLX42)**:
    *   La MinilibX42 trabaja con colores en formato `RGBA` (Red, Green, Blue, Alpha). Por defecto, el Alpha para colores opacos es `255` (`0xFF`).
    *   La fórmula es: `(R << 24) | (G << 16) | (B << 8) | 255`.
    *   Guarda este número resultante en `game->map.color_floor` o `color_ceiling` según el `id` recibido.
    *   Libera el array `rgb` (la doble matriz completa).

### FASE 3: El Extractor del Mapa (`save_map_line`)
El mapa es especial porque puede tener espacios en blanco y no tiene un identificador al principio de la línea.

**Modificación en tu `analize_line`:**
En el último `else`, debes gestionar el mapa.
**OJO:** Según la norma de cub3D, las texturas y colores pueden venir desordenados, pero **el mapa DEBE ir al final**. Por lo tanto, no deberías empezar a guardar líneas de mapa hasta que no hayas confirmado que ya tienes las 4 texturas y los 2 colores rellenados en tu `t_game`.

**Estrategia para `save_map_line`:**
Dado que vas leyendo línea a línea con `get_next_line`, no sabes cuántas líneas tendrá el mapa (no puedes hacer `malloc` del array 2D de una vez). 

1.  **Opción A (Realloc manual)**:
    Cada vez que entra una línea, calculas el tamaño de `game->map.grid`, creas un array nuevo con un hueco más, copias los punteros anteriores, añades la nueva línea limpia de `\n` y haces `free` del array viejo.
2.  **Opción B (Acumular en un String)**:
    En lugar de hacer todo esto en `analize_line`, podrías leer el mapa concatenando todas las líneas en un único y gigante `char *map_raw` usando un `ft_strjoin` especial (añadiendo `\n` entre líneas). Cuando termine el archivo, haces un `ft_split(map_raw, '\n')` y ¡bum!, tienes tu `game->map.grid`.

### FASE 4: Validación del Contenido del Mapa
Una vez que has cerrado el archivo y ya tienes `game->map.grid` relleno, debes crear una función `validate_map_content(t_game *game)`.

1.  **Caracteres válidos**: Itera la matriz. Solo puedes tener `0, 1, N, S, E, W` y espacio ` `. Si hay otro caracter -> Error.
2.  **Localizar al Jugador**: Mientras iteras, busca la letra.
    *   Guárdala en `game->player.dir_x` / `dir_y` o `FOV` según corresponda (veremos matemáticas más adelante, por ahora puedes guardar el char en un char temporal).
    *   Guarda la `X` e `Y` en `game->player.pos_x` / `pos_y` (¡Cuidado, al guardar añade `0.5` para que el jugador nazca en el centro de la celda!).
    *   Reemplaza la letra en el `grid` por un `'0'`.
    *   Si encuentras 0 jugadores o más de 1 jugador -> Error.
3.  **Comprobar Líneas Vacías Interiores**: Si ves una fila de tu matriz que solo contiene espacios o está vacía, y no es la última del mapa -> Error de mapa discontinuo.

### FASE 5: El Algoritmo de Muros (Flood Fill / Perimeter)
Debes asegurar que ningún `0` (suelo) toque el "vacío".
Crea una función `check_walls(t_map *map)`.

La forma más lógica y segura (sin modificar el mapa original):
*   Recorre el mapa `y` por `y`, `x` por `x`.
*   Si `grid[y][x] == '0'`:
    *   Comprueba sus 4 vecinos (`grid[y-1][x]`, `grid[y+1][x]`, `grid[y][x-1]`, `grid[y][x+1]`).
    *   Si intentas mirar fuera de los límites de la matriz (ej. `y == 0`, o `x` es mayor que el largo de la línea superior/inferior), significa que el 0 toca el borde -> Mapa Abierto (Error).
    *   Si el vecino es el caracter de espacio `' '` -> Mapa Abierto (Error).

---

## 3. Próximos pasos recomendados

1.  Corrige el bug lógico de `is_empty_line` en tu `parsing.c`.
2.  Actualiza las llamadas en `analize_line` para que reciban argumentos.
3.  Remata la función `save_texture` en `utils.c` añadiendo la comprobación con `open()`.
4.  Crea `save_color` usando `ft_split` y comprobando el rango.

Cuando tengas tu `t_map` capaz de guardar todas las rutas y los colores convertidos a `uint32_t`, dímelo y atacaremos el guardado de la matriz del mapa y el algoritmo de Flood Fill para los muros.