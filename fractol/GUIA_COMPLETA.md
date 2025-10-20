# 📖 GUÍA COMPLETA DEL PROYECTO FRACTOL

## 🎯 ¿Qué es Fractol?

Fractol es un programa que renderiza fractales (Mandelbrot y Julia) usando la librería gráfica MLX42.

---

## 📂 ESTRUCTURA DE ARCHIVOS EXPLICADA

### **fractol.h** - Header principal
**Contenido:**
- Definiciones de constantes (tamaño de ventana, iteraciones máximas)
- Enum `t_fractal_type` para identificar el tipo de fractal
- Struct `t_fractal` con toda la información del estado del programa
- Prototipos de todas las funciones

**Uso:** Se incluye en todos los archivos `.c` del proyecto

---

### **main.c** - Punto de entrada
**Funciones principales:**
1. `show_error_message()` - Muestra uso correcto del programa
2. `parse_args()` - Valida y procesa argumentos de línea de comandos
3. `main()` - Inicializa todo y arranca el loop de MLX

**Flujo:**
```
Usuario ejecuta → parse_args valida → init_fractal configura → 
MLX loops comienza → render_fractal dibuja → MLX muestra ventana
```

---

### **init.c** - Inicialización
**Función:** `init_fractal()`

**Responsabilidades:**
1. Inicializa MLX (biblioteca gráfica)
2. Crea la imagen donde se dibujará el fractal
3. Establece los límites del plano complejo por defecto
4. Inicializa los parámetros de Julia a 0
5. Marca que necesita renderizarse

**Valores iniciales:**
- Ventana: 800x600 píxeles
- Plano complejo: de -2 a +2 (real e imaginario)

---

### **render.c** - Motor de renderizado
**Funciones:**

#### `handle_pixel(int x, int y, t_fractal *fractal)`
**Propósito:** Calcula y dibuja UN solo píxel

**Proceso:**
1. Convierte coordenadas de píxel (x,y) → coordenadas complejas (c_r, c_i)
2. Determina qué fractal calcular (Mandelbrot o Julia)
3. Llama a la función de cálculo correspondiente
4. Obtiene el color según las iteraciones
5. Dibuja el píxel en la imagen

#### `render_fractal(t_fractal *fractal)`
**Propósito:** Renderiza TODO el fractal

**Proceso:**
- Doble bucle: recorre cada píxel (800×600 = 480,000 píxeles)
- Llama a `handle_pixel()` para cada uno

---

### **mandelbrot.c** - Cálculo de Mandelbrot
**Función:** `calculate_mandelbrot(double c_r, double c_i)`

**Algoritmo:**
```
z = 0 + 0i
repetir hasta MAX_ITERATIONS:
    si |z|² > 4 → punto escapa, retorna iteraciones
    z = z² + c
```

**Retorna:** Número de iteraciones antes de escapar (o MAX_ITERATIONS si no escapa)

**Significado:**
- Retorna rápido (pocas iteraciones) → fuera del conjunto → coloreado
- Retorna MAX_ITERATIONS → dentro del conjunto → negro

---

### **julia.c** - Cálculo de Julia
**Función:** `calculate_julia(double z_r, double z_i, t_fractal *fractal)`

**Diferencia con Mandelbrot:**
- Mandelbrot: z empieza en 0, c varía por píxel
- Julia: z empieza en el píxel, c es constante (julia_r, julia_i)

**Algoritmo:**
```
c = constante (parámetros del usuario)
z = píxel actual
repetir hasta MAX_ITERATIONS:
    si |z|² > 4 → punto escapa
    z = z² + c
```

---

### **colors.c** - Sistema de colores ✨
**Funciones:**

#### `get_color(int iterations)`
**Propósito:** Asigna color final a un píxel

**Lógica:**
```
Si iterations == MAX_ITERATIONS:
    → Negro (punto dentro del conjunto)
Sino:
    → Interpola entre azul y magenta
```

#### `interpolate_color(int iterations, int color1, int color2)`
**Propósito:** Crea gradiente suave entre dos colores

**Matemática:**
```
factor = (iterations % 50) / 50.0  // 0.0 a 1.0
color_final = color1 × (1-factor) + color2 × factor
```

**Resultado:** Transiciones suaves en lugar de bandas de color

---

### **events.c** - Manejo de eventos
**Funciones:**

#### `zoom(t_fractal *fractal, double zoom_factor)`
**Propósito:** Aplica zoom al plano complejo

**Proceso:**
1. Calcula el centro actual del plano
2. Multiplica el rango por zoom_factor
3. Reajusta los límites centrados

**Ejemplos:**
- `zoom_factor = 0.9` → Acerca (zoom in) 10%
- `zoom_factor = 1.1` → Aleja (zoom out) 10%

#### `scroll_hook(double xdelta, double ydelta, void *param)`
**Propósito:** Detecta scroll del mouse

**Mapeo:**
- Scroll hacia arriba → zoom in
- Scroll hacia abajo → zoom out
- Marca `needs_render = 1` para redibujar

#### `render_loop(void *param)`
**Propósito:** Loop principal de renderizado

**Optimización:**
- Solo renderiza si `needs_render == 1`
- Después de renderizar, pone `needs_render = 0`
- Evita renderizar innecesariamente

---

### **hooks.c** - Hooks de teclado
**Funciones:**

#### `key_hook(mlx_key_data_t keydata, void *param)`
**Propósito:** Detecta teclas presionadas

**Funcionalidad actual:**
- ESC → Cierra la ventana

**Extensible:** Puedes añadir más teclas (flechas para mover, R para reset, etc.)

#### `close_hook(void *param)`
**Propósito:** Maneja clic en el botón X de la ventana

---

### **utils.c** - Utilidades matemáticas
**Funciones:**

#### `map(double unscaled_num, double new_min, double new_max, double old_max)`
**Propósito:** Convierte un valor de un rango a otro

**Ejemplo:**
```c
// Píxel 400 (de 0-800) → -0.5 (de -2 a +2)
double c_r = map(400, -2.0, 2.0, 800);
```

**Fórmula:**
```
resultado = (new_max - new_min) × (valor / old_max) + new_min
```

#### `ft_atof(const char *str)`
**Propósito:** Convierte string a número decimal

**Ejemplo:**
```c
double num = ft_atof("-0.7");  // -0.7
double num2 = ft_atof("0.285"); // 0.285
```

**Uso:** Para parsear argumentos de Julia

---

## 🎮 USO DEL PROGRAMA

### **Compilar:**
```bash
make
```

### **Ejecutar Mandelbrot:**
```bash
./fractol mandelbrot
```

### **Ejecutar Julia:**
```bash
./fractol julia <parte_real> <parte_imaginaria>
```

**Ejemplos de Julia interesantes:**
```bash
./fractol julia -0.7 0.27015
./fractol julia -0.835 -0.2321
./fractol julia 0.285 0.01
./fractol julia -0.8 0.156
```

### **Controles:**
- **Scroll** → Zoom in/out
- **ESC** → Salir

---

## 🔧 CÓMO EXTENDER EL PROGRAMA

### **Añadir un nuevo fractal:**

1. **Añadir al enum** (fractol.h):
```c
typedef enum e_fractal_type
{
    FRACTAL_MANDELBROT,
    FRACTAL_JULIA,
    FRACTAL_BURNING_SHIP  // Nuevo
}   t_fractal_type;
```

2. **Crear archivo de cálculo** (burning_ship.c):
```c
int calculate_burning_ship(double c_r, double c_i)
{
    // Implementación del algoritmo
}
```

3. **Actualizar render.c**:
```c
else if (fractal->type == FRACTAL_BURNING_SHIP)
    iterations = calculate_burning_ship(c_r, c_i);
```

4. **Actualizar main.c**:
```c
else if (argc == 2 && ft_strncmp(argv[1], "burning_ship", 12) == 0)
{
    fractal->name = "burning_ship";
    fractal->type = FRACTAL_BURNING_SHIP;
}
```

---

### **Cambiar esquema de colores:**

Edita `colors.c`, función `get_color()`:

```c
int get_color(int iterations)
{
    if (iterations == MAX_ITERATIONS)
        return (0x000000FF);
    
    // Prueba diferentes combinaciones:
    int color1 = 0xFF0000FF;  // Rojo
    int color2 = 0xFFFF00FF;  // Amarillo
    
    return (interpolate_color(iterations, color1, color2));
}
```

---

### **Añadir movimiento con teclas:**

En `hooks.c`:

```c
void key_hook(mlx_key_data_t keydata, void *param)
{
    t_fractal *fractal = (t_fractal *)param;
    double shift = 0.1;
    
    if (keydata.action == MLX_PRESS)
    {
        if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(fractal->mlx);
        else if (keydata.key == MLX_KEY_LEFT)
        {
            fractal->min_r -= shift;
            fractal->max_r -= shift;
            fractal->needs_render = 1;
        }
        // Similar para RIGHT, UP, DOWN
    }
}
```

---

## 🐛 DEBUGGING

### **El programa no compila:**
```bash
make fclean
make
```

### **La ventana está negra:**
- Verifica que `needs_render = 1` en init_fractal
- Verifica que render_loop se está llamando

### **Colores extraños:**
- Verifica el formato RGBA (0xRRGGBBAA)
- El último byte debe ser FF (opaco)

### **Lentitud extrema:**
- Aumenta `MAX_ITERATIONS` (pero renderizará más lento)
- Optimiza funciones de cálculo

---

## 📚 CONCEPTOS MATEMÁTICOS

### **¿Qué es un número complejo?**
```
z = a + bi
donde:
- a = parte real
- b = parte imaginaria
- i = √(-1)
```

### **Operaciones con complejos:**
```c
// Suma: (a+bi) + (c+di) = (a+c) + (b+d)i
z_r = a + c;
z_i = b + d;

// Multiplicación: (a+bi) × (c+di) = (ac-bd) + (ad+bc)i
real = a*c - b*d;
imag = a*d + b*c;

// Cuadrado: (a+bi)² = (a²-b²) + (2ab)i
real = a*a - b*b;
imag = 2*a*b;
```

### **Magnitud (valor absoluto):**
```c
// |z|² = a² + b²
magnitude_squared = z_r * z_r + z_i * z_i;
```

---

## ✅ CHECKLIST DE BUENAS PRÁCTICAS

- [x] No usar magic numbers (usar constantes)
- [x] Funciones cortas y específicas
- [x] Nombres descriptivos
- [x] Comentarios útiles (no obvios)
- [x] Manejo de errores consistente
- [x] Código modular y reutilizable
- [x] Sin memory leaks
- [x] Compilar sin warnings

---

## 🎓 CONCLUSIÓN

Este proyecto demuestra:
- ✅ Programación gráfica con MLX42
- ✅ Algoritmos matemáticos complejos
- ✅ Optimización de rendimiento
- ✅ Arquitectura de software modular
- ✅ Manejo de eventos y hooks

**Estado final:** Código limpio, rápido y extensible 🚀
