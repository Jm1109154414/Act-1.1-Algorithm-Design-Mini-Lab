# Problema C — Budgeted Study Plan (0/1 Knapsack)

Calcula el máximo valor de aprendizaje alcanzable eligiendo un subconjunto de
`n` módulos de estudio (cada uno usable a lo más una vez) sin exceder un
presupuesto de tiempo `T`. Se resuelve con Programación Dinámica (variante de
Knapsack 0/1) en tiempo O(n·T).

## Compilación

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Ejecución

El programa lee de la entrada estándar (stdin):
- Línea 1: dos enteros `n T`
- Las siguientes `n` líneas: `time value` de cada módulo

Y escribe en la salida estándar (stdout) un solo entero: el valor máximo
alcanzable.

```bash
./main < tests/test1.txt
```

## Tests incluidos

| Archivo | Entrada | Salida esperada | Caso |
|---|---|---|---|
| tests/test1.txt | n=3, T=10; (3,4)(4,5)(7,10) | `14` | Caso general (módulos 1 y 3) |
| tests/test2.txt | n=3, T=5; (6,10)(7,20)(8,30) | `0` | Ningún módulo cabe en el presupuesto |
| tests/test3.txt | n=4, T=6; (1,2)(2,4)(3,4)(4,7) | `11` | Múltiples combinaciones posibles |

Para correr todos:
```bash
./main < tests/test1.txt
./main < tests/test2.txt
./main < tests/test3.txt
```

## Idea del algoritmo

Se construye una tabla `dp[i][t]` = máximo valor alcanzable usando los
primeros `i` módulos con presupuesto `t`. Cada celda se calcula comparando
dos opciones: no tomar el módulo `i` (`dp[i-1][t]`), o tomarlo si el
presupuesto alcanza (`value[i] + dp[i-1][t - time[i]]`). La respuesta final
es `dp[n][T]`.

## Complejidad

- **Tiempo:** O(n·T) — se llena una tabla de `(n+1)×(T+1)` celdas, cada una
  en tiempo constante.
- **Espacio:** O(n·T) — por la tabla completa de programación dinámica.
