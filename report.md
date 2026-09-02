# Problema A — Inversion Counter for Quality Control

## Resumen del problema

Dado un arreglo `A` de `n` enteros, una inversión es un par de índices `(i, j)`
tal que `i < j` pero `A[i] > A[j]`; es decir, un elemento "grande" aparece antes
que uno "pequeño" en el arreglo. El objetivo es contar cuántos pares de este
tipo existen. Una solución por fuerza bruta (comparar todos los pares) toma
O(n²), lo cual es demasiado lento para `n` hasta 2×10⁵.

## Idea del algoritmo (Divide y Vencerás)

Se adapta Merge Sort para que, mientras ordena el arreglo, también cuente las
inversiones. La clave es que las inversiones totales se separan en tres grupos
disjuntos:

1. Inversiones donde ambos índices caen en la mitad izquierda.
2. Inversiones donde ambos índices caen en la mitad derecha.
3. Inversiones "cruzadas": un índice en la izquierda y otro en la derecha.

Los grupos 1 y 2 se resuelven recursivamente aplicando el mismo algoritmo a
cada mitad. El grupo 3 se cuenta durante el paso de `merge`, aprovechando que,
para cuando se llega a fusionar, ambas mitades ya están ordenadas (por las
llamadas recursivas previas).

Durante el merge, se recorren ambas mitades con dos punteros `i` (izquierda) y
`j` (derecha). Si `arr[i] <= arr[j]`, no hay inversión y se toma el elemento de
la izquierda. Si `arr[i] > arr[j]`, como la mitad izquierda está ordenada,
`arr[j]` es menor que `arr[i]` y también menor que **todos** los elementos que
quedan en la izquierda desde la posición `i` hasta `mid` (inclusive). Por lo
tanto se suman `mid - i + 1` inversiones de una sola vez, en lugar de compararlas
una por una.

## Pseudocódigo

```
function mergeSortCount(arr, left, right):
    if left >= right:
        return 0
    mid = left + (right - left) / 2
    invLeft  = mergeSortCount(arr, left, mid)
    invRight = mergeSortCount(arr, mid + 1, right)
    invSplit = merge(arr, left, mid, right)
    return invLeft + invRight + invSplit

function merge(arr, left, mid, right):
    temp = []
    inv = 0
    i = left
    j = mid + 1

    while i <= mid and j <= right:
        if arr[i] <= arr[j]:
            temp.append(arr[i]); i = i + 1
        else:
            inv = inv + (mid - i + 1)
            temp.append(arr[j]); j = j + 1

    while i <= mid:
        temp.append(arr[i]); i = i + 1
    while j <= right:
        temp.append(arr[j]); j = j + 1

    for k = 0 to length(temp) - 1:
        arr[left + k] = temp[k]

    return inv
```

## Correctness (argumento breve)

**Invariante:** al llegar a `merge(arr, left, mid, right)`, los subarreglos
`arr[left..mid]` y `arr[mid+1..right]` están completamente ordenados. Esto se
cumple por inducción: el caso base (0 o 1 elemento) está trivialmente ordenado,
y cada llamada recursiva a `mergeSortCount` deja ordenado su rango antes de
regresar.

Dado ese invariante, cuando `arr[i] > arr[j]` durante el merge, como
`arr[left..mid]` está ordenado ascendentemente, se cumple
`arr[i] <= arr[i+1] <= ... <= arr[mid]`. Por lo tanto `arr[j] < arr[i] <= arr[k]`
para todo `k` en `[i, mid]`, es decir, `arr[j]` forma inversión con cada uno de
esos `mid - i + 1` elementos. Ningún par se cuenta dos veces porque cada
inversión cruzada involucra exactamente un elemento fijo de la derecha (`arr[j]`)
en el momento en que se procesa, y cada elemento de la derecha se procesa una
sola vez.

## Ejemplo de ejecución

Entrada: `A = [2, 4, 1, 3, 5]`

- Se divide en `[2, 4]` y `[1, 3, 5]`.
- `[2, 4]` no tiene inversiones internas (ya ordenado); se mantiene igual.
- `[1, 3, 5]` no tiene inversiones internas; se mantiene igual.
- Merge cruzado entre `[2, 4]` y `[1, 3, 5]`:
  - Compara `2` vs `1`: `2 > 1` → suma `mid - i + 1 = 2` inversiones (elementos `2` y `4`
    ambos son mayores que `1`). Toma `1`.
  - Compara `2` vs `3`: `2 <= 3` → sin inversión. Toma `2`.
  - Compara `4` vs `3`: `4 > 3` → suma `1` inversión. Toma `3`.
  - Compara `4` vs `5`: `4 <= 5` → sin inversión. Toma `4`.
  - Sobra `5` en la derecha, se copia sin generar inversiones.
- Total del merge: `2 + 1 = 3` inversiones.
- Total general: `0 (izquierda) + 0 (derecha) + 3 (cruzadas) = 3`.

Salida: `3` — coincide con el resultado esperado.

## Análisis de complejidad

**Tiempo: O(n log n).**
La recursión divide el arreglo por la mitad en cada llamada, generando
`log₂ n` niveles de profundidad. En cada nivel, la suma de trabajo de todos los
merges de ese nivel es O(n) (cada elemento se procesa una cantidad constante de
veces por nivel). Esto da la recurrencia clásica de Merge Sort:

```
T(n) = 2T(n/2) + O(n)  →  T(n) = O(n log n)
```

por el Teorema Maestro (caso 2: a=2, b=2, f(n)=O(n) = Θ(n^(log_b a)) = Θ(n)).

**Espacio: O(n).**
El vector `temp` usado en cada llamada a `merge` ocupa, en total sumado por
nivel, O(n) (no se acumulan simultáneamente todos los niveles, cada llamada
libera su `temp` al terminar). Adicionalmente, la pila de llamadas recursivas
alcanza una profundidad máxima de O(log n). Por lo tanto el espacio auxiliar
total es O(n) (dominado por el arreglo temporal), más O(log n) de pila de
recursión.
# Problema B — Minimum Meeting Rooms (Scheduling)

## Resumen del problema

Se tienen `m` reuniones, cada una definida por un intervalo `(s_i, e_i)` con
`s_i < e_i`, donde una sala solo puede alojar una reunión a la vez. El objetivo
es determinar el número mínimo de salas necesarias para que todas las
reuniones puedan llevarse a cabo sin que dos reuniones traslapadas compartan
sala. Por convención del problema, si una reunión termina exactamente en el
mismo instante en que otra comienza, no se consideran traslapadas y pueden
usar la misma sala.

El problema es equivalente a encontrar, en cualquier instante de tiempo, el
número máximo de reuniones que están ocurriendo simultáneamente — ese máximo
es la cantidad mínima de salas requerida.

## Idea del algoritmo (Greedy)

Se separan los tiempos de inicio y los tiempos de fin de todas las reuniones
en dos listas independientes, y cada una se ordena de forma ascendente. Luego
se recorren ambas listas con dos punteros (`i` para inicios, `j` para fines),
simulando cronológicamente los eventos de "una reunión empieza" y "una
reunión termina":

- Si el próximo inicio ocurre **antes** de que se libere la próxima sala
  (`starts[i] < ends[j]`), se necesita abrir una sala nueva.
- En caso contrario, la sala que se iba a liberar ya está libre para cuando
  llega la siguiente reunión, así que se libera una sala (se reutiliza).

Se lleva un contador de salas en uso (`rooms`) y se registra el máximo valor
que alcanza (`maxRooms`) a lo largo del recorrido; ese máximo es la respuesta.

**Propiedad greedy (por qué es correcto):** ordenar los inicios y los fines
por separado permite procesar los eventos en el orden cronológico real en que
ocurren, sin importar a qué reunión pertenece cada uno. En cualquier punto del
recorrido, `rooms` refleja exactamente cuántas reuniones han comenzado y
todavía no han terminado — es decir, cuántas salas están ocupadas en ese
instante. Tomar la decisión localmente correcta en cada paso (abrir sala solo
si es estrictamente necesario, y reciclar salas tan pronto como sea posible)
nunca produce un resultado peor que la solución óptima, porque el máximo de
reuniones simultáneas es una propiedad fija de la entrada que este recorrido
mide exactamente, sin necesidad de reconsiderar decisiones pasadas.

## Pseudocódigo

```
function minRooms(meetings, m):
    starts = lista de s_i para cada reunión
    ends   = lista de e_i para cada reunión

    sort(starts)
    sort(ends)

    i = 0
    j = 0
    rooms = 0
    maxRooms = 0

    while i < m:
        if starts[i] < ends[j]:
            rooms = rooms + 1
            maxRooms = max(maxRooms, rooms)
            i = i + 1
        else:
            rooms = rooms - 1
            j = j + 1

    return maxRooms
```

## Ejemplo de ejecución

Entrada: reuniones `(0, 30), (5, 10), (15, 20)`

- Inicios ordenados: `[0, 5, 15]`
- Fines ordenados: `[10, 20, 30]`

Recorrido:

| Paso | Comparación | Acción | rooms | maxRooms |
|---|---|---|---|---|
| 1 | `0 < 10` | abre sala | 1 | 1 |
| 2 | `5 < 10` | abre sala | 2 | 2 |
| 3 | `15 >= 10` | libera sala | 1 | 2 |

`i` llega a `m=3` y el recorrido termina.

Salida: `2` — coincide con el resultado esperado (la reunión `(5,10)` y
`(15,20)` se traslapan con `(0,30)` pero no entre sí, así que comparten sala).

## Análisis de complejidad

**Tiempo: O(m log m).**
Construir las listas de inicios y fines toma O(m). Ordenar cada lista toma
O(m log m) (usando un algoritmo de ordenamiento estándar, como el `sort` de
la librería estándar de C++, que es O(m log m) en el peor caso). El recorrido
con los dos punteros procesa cada elemento de ambas listas a lo más una vez,
por lo que es O(m). El término dominante es el ordenamiento: **O(m log m)**.

**Espacio: O(m).**
Se usan dos arreglos auxiliares (`starts` y `ends`) de tamaño `m` cada uno,
además de variables de tamaño constante para los punteros y contadores. No se
requiere espacio adicional dependiente del tiempo de las reuniones (que puede
llegar a 10^9), ya que no se construye una línea de tiempo explícita.
# Problema C — Budgeted Study Plan (0/1 Knapsack Variant)

## Resumen del problema

Se tienen `n` módulos de estudio, cada uno con un costo en horas `time[i]` y
un beneficio `value[i]`. Se dispone de un presupuesto total de `T` horas, y
cada módulo puede tomarse a lo más una vez (no es divisible). El objetivo es
seleccionar el subconjunto de módulos que maximice el valor total acumulado
sin que la suma de sus tiempos exceda `T`.

Este es el problema clásico de la mochila 0/1 (0/1 Knapsack). No admite una
solución greedy simple (por ejemplo, ordenar por valor/hora y tomar
codiciosamente) porque el mejor subconjunto depende de cómo los tiempos
encajan exactamente dentro del presupuesto, y una elección localmente
atractiva puede desperdiciar presupuesto que otra combinación aprovecharía
mejor. Una búsqueda exhaustiva de todos los subconjuntos es O(2^n), inviable
para `n` hasta 2000.

## Idea del algoritmo (Programación Dinámica)

Se define `dp[i][t]` como el máximo valor alcanzable usando únicamente los
primeros `i` módulos, con un presupuesto de tiempo de `t` horas. La respuesta
final del problema es `dp[n][T]`.

Cada celda se calcula a partir de la fila anterior, considerando las dos
únicas decisiones posibles sobre el módulo `i`:

- **No tomar el módulo `i`:** el valor es el mismo que ya se tenía
  considerando solo los primeros `i-1` módulos, con el mismo presupuesto:
  `dp[i-1][t]`.
- **Tomar el módulo `i`** (solo posible si `time[i] <= t`): se gana
  `value[i]`, y queda un presupuesto de `t - time[i]` para los módulos
  anteriores: `value[i] + dp[i-1][t - time[i]]`.

`dp[i][t]` es el máximo entre ambas opciones. La fila `dp[0][*]` se
inicializa en 0 (sin módulos disponibles, el valor máximo es 0 para cualquier
presupuesto), y la tabla se llena fila por fila, de menor a mayor `i`.

## Pseudocódigo

```
function budgetedStudyPlan(n, T, time[], value[]):
    dp = tabla de (n+1) x (T+1), inicializada en 0

    for i = 1 to n:
        for t = 0 to T:
            noTomar = dp[i-1][t]
            siTomar = 0
            if time[i-1] <= t:
                siTomar = value[i-1] + dp[i-1][t - time[i-1]]
            dp[i][t] = max(noTomar, siTomar)

    return dp[n][T]
```

## Correctness (argumento breve)

**Invariante:** `dp[i][t]` almacena exactamente el máximo valor alcanzable
usando un subconjunto de los primeros `i` módulos con tiempo total `<= t`.
Esto se cumple por inducción: el caso base (`i=0`, sin módulos) es
trivialmente 0. Suponiendo que `dp[i-1][*]` es correcto para todo presupuesto,
`dp[i][t]` solo tiene dos decisiones mutuamente excluyentes sobre el módulo
`i` (incluirlo o no), y el óptimo es necesariamente el mejor de esos dos
casos, cada uno de los cuales se reduce a un subproblema ya resuelto
correctamente en la fila `i-1`. Como se cubren exhaustivamente ambas
decisiones sin duplicar ni omitir módulos (cada módulo se decide una sola
vez, en su propia fila), el valor final `dp[n][T]` es óptimo.

## Ejemplo de ejecución

Entrada: módulos `(time=3, value=4), (time=4, value=5), (time=7, value=10)`,
`T=10`

Construcción de la tabla (`dp[i][t]`, filas = módulos considerados, columnas
= presupuesto):

| i \ t | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 0 (ninguno) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 (+A: t=3,v=4) | 0 | 0 | 0 | 4 | 4 | 4 | 4 | 4 | 4 | 4 | 4 |
| 2 (+B: t=4,v=5) | 0 | 0 | 0 | 4 | 5 | 5 | 5 | 9 | 9 | 9 | 9 |
| 3 (+C: t=7,v=10) | 0 | 0 | 0 | 4 | 5 | 5 | 5 | 10 | 10 | 10 | 14 |

Razonamiento clave en la última celda (`i=3, t=10`): no tomar el módulo C
deja `dp[2][10] = 9`; tomar C aporta `10 + dp[2][10-7] = 10 + dp[2][3] = 10+4
= 14`. Como `14 > 9`, se toma C, y `dp[2][3] = 4` corresponde a haber tomado
solo el módulo A con las 3 horas restantes — es decir, la solución óptima
combina los módulos A y C.

Salida: `14` — coincide con el resultado esperado.

## Análisis de complejidad

**Tiempo: O(n·T).**
La tabla tiene `(n+1)` filas y `(T+1)` columnas, y cada celda se calcula en
tiempo constante a partir de celdas ya calculadas de la fila anterior. El
trabajo total es proporcional al número de celdas: **O(n·T)**. Con los
límites del enunciado (`n <= 2000`, `T <= 5000`), esto da como máximo
`10^7` operaciones aproximadamente, bien dentro de límites de tiempo
razonables.

**Espacio: O(n·T).**
La tabla completa `dp` ocupa `(n+1)*(T+1)` enteros de 64 bits. (Nota: es
posible optimizar el espacio a O(T) manteniendo solo la fila anterior y la
actual, ya que cada fila solo depende de la inmediatamente anterior, pero la
versión con tabla completa es la más directa de implementar y verificar.)
