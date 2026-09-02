# Problema A — Inversion Counter

Cuenta el número de inversiones en un arreglo de `n` enteros usando un algoritmo de
Divide y Vencerás (variante de Merge Sort), en tiempo O(n log n).

## Compilación

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Ejecución

El programa lee de la entrada estándar (stdin):
- Línea 1: un entero `n`
- Línea 2: `n` enteros separados por espacio

Y escribe en la salida estándar (stdout) un solo entero: el número de inversiones.

```bash
./main < tests/test1.txt
```

## Tests incluidos

| Archivo | Entrada | Salida esperada | Caso |
|---|---|---|---|
| tests/test1.txt | `[2, 4, 1, 3, 5]` | `3` | Caso general |
| tests/test2.txt | `[1, 2, 3, 4, 5]` | `0` | Ya ordenado (sin inversiones) |
| tests/test3.txt | `[4, 3, 2, 1]` | `6` | Orden totalmente inverso (máximo de inversiones) |

Para correr todos:
```bash
./main < tests/test1.txt
./main < tests/test2.txt
./main < tests/test3.txt
```

## Idea del algoritmo

Se modifica Merge Sort para que, además de ordenar, cuente inversiones:

1. Se divide el arreglo en dos mitades y se resuelve cada una recursivamente
   (esto ordena la mitad y devuelve las inversiones internas de esa mitad).
2. Al fusionar (`merge`) las dos mitades ya ordenadas, cada vez que un elemento
   de la derecha es menor que el elemento actual de la izquierda, se suman de
   una sola vez todas las inversiones que ese elemento forma con el resto de
   la mitad izquierda que aún no se ha tomado (`mid - i + 1` elementos), en
   lugar de compararlos uno por uno.
3. El total de inversiones es la suma de: inversiones en la mitad izquierda +
   inversiones en la mitad derecha + inversiones "cruzadas" encontradas en el merge.

## Complejidad

- **Tiempo:** O(n log n) — igual que Merge Sort: log n niveles de recursión,
  cada uno hace un merge de O(n) en total.
- **Espacio:** O(n) — por el arreglo temporal usado en cada merge (más O(log n)
  de la pila de recursión).
