# Algorithm Design Mini-Lab

Solución a los tres problemas del mini-lab, cada uno resuelto con la técnica
de diseño de algoritmos que mejor se ajusta a su estructura:

| Problema | Nombre | Técnica |
|---|---|---|
| A | Inversion Counter | Divide y Vencerás (Merge Sort modificado) |
| B | Minimum Meeting Rooms | Greedy (dos punteros) |
| C | Budgeted Study Plan | Programación Dinámica (Knapsack 0/1) |

## Estructura del repositorio

```
problemA_inversions/
  main.cpp
  README.md
  tests/
problemB_rooms/
  main.cpp
  README.md
  tests/
problemC_knapsack/
  main.cpp
  README.md
  tests/
report.md
README.md
```

## Cómo compilar y ejecutar cada problema

Cada carpeta contiene su propio `main.cpp` y se compila igual:

```bash
cd problemA_inversions
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
./main < tests/test1.txt
```

```bash
cd problemB_rooms
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
./main < tests/test1.txt
```

```bash
cd problemC_knapsack
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
./main < tests/test1.txt
```

En Windows con CMD/PowerShell, el ejecutable se genera como `main.exe` y se
corre con `main.exe < tests\test1.txt` (o `.\main.exe < ...` en PowerShell).

## Formato de entrada/salida de cada problema

- **Problema A:** entrada = `n` y luego `n` enteros; salida = número de
  inversiones.
- **Problema B:** entrada = `m` y luego `m` pares `s e`; salida = número
  mínimo de salas.
- **Problema C:** entrada = `n T` y luego `n` pares `time value`; salida =
  valor máximo alcanzable sin exceder `T`.

## Reporte

El análisis completo (idea del algoritmo, pseudocódigo, ejemplo de ejecución
y análisis de complejidad de cada problema) está en [`report.md`](report.md).

## Asunciones generales

- Todas las entradas se asumen válidas y dentro de los rangos especificados
  en el enunciado (no se valida entrada malformada).
- Se usa `long long` (64 bits) para cualquier valor que pueda exceder el
  rango de un entero de 32 bits (conteo de inversiones, valores acumulados).
