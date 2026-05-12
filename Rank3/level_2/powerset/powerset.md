# Powerset - Explicación Paso a Paso

Busca encontrar todos los subconjuntos que sumen un "target" específico.

## Código Principal (Core de Backtracking)
```c
// ixn: Índice del número actual que evaluamos (¿Lo añadimos o no?)
// ixc: Cantidad elementos en buffer (Índice de escritura)
// sum: Suma acumulada

// Opción A: NO cogemos el número nums[ixn]
powerset(ixn + 1, size, ixc, sum);

// Opción B: SÍ cogemos el número nums[ixn]
buffer[ixc] = nums[ixn];
powerset(ixn + 1, size, ixc + 1, sum + nums[ixn]);
```

## Simulación Paso a Paso 
Supongamos nums = [1, 2, 3], target = 3

### Visualización en Árbol
Bifurcamos en dos por cada índice `ixn`.
`ixn=0 (Evaluar nº 1), ixn=1 (Evaluar nº 2), ixn=2 (Evaluar nº 3)`

```text
[ Nivel 0 ] ixn=0, nums[0]=1. Decision: ¿Tomo el 1?
 |
 |-- (NO) Llama powerset con índice siguiente (ixn=1), buffer=[],_sum=0
 |    |
 |    [ Nivel 1 ] ixn=1, nums[1]=2. ¿Tomo el 2?
 |     |-- (NO) sum=0 ...
 |     |-- (SÍ) buffer=[2], sum=2...
 |
 |-- (SÍ) Lo anoto: buffer[0]=1. Llama powerset(ixn=1), buffer=[1], sum=1
      |
      [ Nivel 1 ] ixn=1, nums[1]=2. ¿Tomo el 2?
       |
       |-- (NO) Llama powerset(ixn=2), buffer=[1], sum=1
       |    |
       |    [ Nivel 2 ] ixn=2, nums[2]=3. ¿Tomo el 3?
       |     |-- (NO) Llama con ixn=3 -> ixn==size. sum=1 != 3. Descarta.
       |     |-- (SÍ) buffer=[1, 3], sum=4. Llama ixn=3. sum=4 != 3. Descarta.
       |
       |-- (SÍ) buffer=[1, 2], sum=3. Llama powerset(ixn=2), sum=3
            |
            [ Nivel 2 ] ixn=2, nums[2]=3. ¿Tomo el 3?
             |-- (NO) Llama con ixn=3 -> ixn==size. sum=3 == target(3). IMPRIME "1 2".
             |-- (SÍ) buffer=[1, 2, 3], sum=6 -> sum!=target. Descarta.
```

## Narrativa
1. A diferencia del bucle `while` en permutaciones o n_queens, aquí cada nivel representa un elemento del array de entrada (cada número).
2. Para cada número, tenemos dos opciones: **Ignorarlo** o **Añadirlo**.
3. El primer llamado recursivo lo "Ignora": simplemente avanzamos al siguiente índice (`ixn+1`) sin cambiar la suma.
4. El segundo llamado recursivo lo "Añade": lo guardamos en nuestro buffer, sumamos su valor, y avanzamos al siguiente índice.
5. El **backtracking** sucede de forma implícita tras volver de llamar a la primera recursión, donde sobreescribiremos el buffer en `buffer[ixc]` y cambiamos de opinión.