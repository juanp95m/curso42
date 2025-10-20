

## ✅ **VERIFICACIÓN**

### **Ahora estos comandos producen fractales correctos:**

```bash
# Fractal de Julia tipo "dragón"
./fractol julia -0.7 0.27015

# Fractal de Julia "dendrita"
./fractol julia -0.835 -0.2321

# Fractal de Julia "espiral"
./fractol julia 0.285 0.01

# Fractal de Julia "relámpago"
./fractol julia -0.8 0.156
```
# Clásicos
./fractol julia -0.4 0.6          # Flor
./fractol julia 0.285 0.0          # Espiral triple
./fractol julia -0.70176 -0.3842  # San Marco
./fractol julia -0.162 1.04        # Simetría radial

# Complejos
./fractol julia -0.7269 0.1889     # Galaxia
./fractol julia 0.3 -0.01          # Espiral doble
./fractol julia -0.4 -0.59         # Cruz
./fractol julia 0.355 0.355        # Dendritas cuadradas

# Extremos
./fractol julia -0.8 0.156         # Relámpago
./fractol julia -1.476 0.0         # Polvo de Cantor

## 📝 **LECCIÓN APRENDIDA**

### **Orden de inicialización importa:**

Cuando una estructura tiene campos que pueden ser configurados por el usuario Y también inicializados por defecto, es crucial:

1. ✅ Inicializar valores por defecto **ANTES** de parsear argumentos, o
2. ✅ Parsear argumentos y **NO sobrescribir** después, o
3. ✅ Inicializar solo en un lugar (donde corresponda)



