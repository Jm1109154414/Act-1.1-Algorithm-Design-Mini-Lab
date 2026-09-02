# Problema B — Minimum Meeting Rooms

Calcula el número mínimo de salas necesarias para que `m` reuniones, cada una
con un intervalo `(inicio, fin)`, puedan llevarse a cabo sin que dos
reuniones traslapadas compartan sala. Se resuelve con un enfoque Greedy en
tiempo O(m log m).

## Compilación

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Ejecución

El programa lee de la entrada estándar (stdin):
- Línea 1: un entero `m`
- Las siguientes `m` líneas: `s e` (inicio y fin de cada reunión)

Y escribe en la salida estándar (stdout) un solo entero: el mínimo de salas.

```bash
./main < tests/test1.txt
```

## Tests incluidos

| Archivo | Entrada | Salida esperada | Caso |
|---|---|---|---|
| tests/test1.txt | `(0,30), (5,10), (15,20)` | `2` | Caso general |
| tests/test2.txt | `(0,10), (10,20), (20,30)` | `1` | Back-to-back (sin traslape real) |
| tests/test3.txt | `(1,10), (2,9), (3,8), (4,7)` | `4` | Todas traslapadas entre sí |

Para correr todos:
```bash
./main < tests/test1.txt
./main < tests/test2.txt
./main < tests/test3.txt
```

## Idea del algoritmo

Se separan los tiempos de inicio y de fin en dos listas, se ordenan por
separado, y se recorren con dos punteros simulando cronológicamente los
eventos de "empieza reunión" / "termina reunión". Cada vez que el próximo
inicio ocurre antes de que se libere la próxima sala, se abre una sala nueva;
en caso contrario, se libera una y se reutiliza. El máximo número de salas
usadas simultáneamente durante el recorrido es la respuesta.

## Complejidad

- **Tiempo:** O(m log m) — dominado por ordenar las dos listas de tamaño `m`.
- **Espacio:** O(m) — por los dos arreglos auxiliares de inicios y fines.
