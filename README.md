# Laberinto — Generador y Resolutor

Programa en C++ que genera un laberinto aleatorio usando **DFS** y lo resuelve con **BFS**, midiendo el tiempo de ejecución de cada proceso.

---

## ¿Cómo funciona?

### Generación — DFS recursivo
El laberinto se construye partiendo de una matriz llena de muros. Desde la celda `(1,1)`, el algoritmo DFS avanza de 2 en 2 celdas en dirección aleatoria, abriendo paredes intermedias para crear los caminos.

### Resolución — BFS
BFS recorre el laberinto nivel por nivel desde la entrada hasta encontrar la salida, garantizando el **camino más corto**. Al terminar, reconstruye el camino usando una matriz de padres y lo marca en el tablero.

---

## Convención del tablero

| Valor | Símbolo | Significado |
|---|---|---|
| `0` | `#` | Muro |
| `1` | ` ` | Camino libre |
| `2` | `.` | Camino solución |
| `3` | `E` | Entrada |
| `4` | `S` | Salida |

---

## Uso

```
Ingrese la cantidad de filas: 15
Ingrese la cantidad de columnas: 15
```

> Si ingresás un valor menor a 6, se usará **11** por defecto.  
> Las dimensiones impares se fuerzan automáticamente.

---

## Librerías utilizadas

| Librería | Uso |
|---|---|
| `iostream` | Entrada y salida por consola |
| `vector` | Matriz del laberinto y estructuras auxiliares |
| `queue` | Cola para el algoritmo BFS |
| `algorithm` / `random` | Mezcla aleatoria de direcciones en DFS |
| `chrono` | Medición de tiempos de ejecución |

---

## Ejemplo de salida

```
 #  #  #  #  #  #  #
 E        #        #
 #  #     #     #  #
 #     .  .  .     #
 #  #  .  #  .  #  #
 #     .  .  .     S
 #  #  #  #  #  #  #

El tiempo en generar el laberinto: 312 ms
El tiempo de resolucion por bfs:    48 ms
```

---

## Estructura del código

```
main.cpp
├── algoritmo_DFS()      → genera los caminos del laberinto
├── generar_laberinto()  → inicializa la matriz y llama a DFS
├── resolver_laberintoBFS() → resuelve y marca el camino más corto
└── imprimir_matriz()    → imprime el laberinto en consola
```
