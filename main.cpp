/* Copyright 2014 ToxaKniotee */
#include <limits.h>     /* INT_MAX */
#include <stdio.h>

#define INF 1 << 30

/* Definición de las funciones */
void theSalesmanProblem();
int compute(int start, int set);
void getPath(int start, int set);

/* Variables estáticas */
int *distanceMatrix, *path, rowMax, n = 4;
int graph[] = {
    INF, 20, 42, 35,
    20, INF, 30, 34,
    42, 30, INF, 12,
    35, 34, 12, INF
};

int main(int argc, char const *argv[]) {
    theSalesmanProblem();
    system("PAUSE");
    return 0;
}

void theSalesmanProblem() {
    /* Función que se encarga de conseguir el circuito hamiltoniano mas corto
     * para un problema */
    /* Creamos las variables que vamos a usar */
    int result;

    /* Inicializamos las variables y matrices */
    rowMax = 1 << n;
    distanceMatrix = new int[n * rowMax];
    path = new int[n * rowMax];

    /* Llenamos las dos matrices con -1 */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < rowMax; j++) {
            distanceMatrix[i * rowMax + j] = -1;
            path[i * rowMax + j] = -1;
        }
    }

    /* Ponemos la distancia de cada nodo hacia el primer */
    for (int i = 0; i < n; i++)
        distanceMatrix[i * rowMax] = graph[i * n];

    /* Mandamos a ejecutar la función que calcula el camino mínimo */
    result = compute(0, rowMax - 2);

    /* Imprimimos el resultado */
    printf("El camino mas corto es : 1 ");
    getPath(0, rowMax - 2);
    printf("1\nCon un pedo de: %d\n", result);
}

int compute(int start, int set) {
    /* Creamos las variables */
    int masked, mask, result = INT_MAX, temp;

    /* Si el valor que queremos ya lo tenemos entonces lo regresamos */
    if (distanceMatrix[start * rowMax + set] != -1)
        return distanceMatrix[start * rowMax + set];

    /* Si no entonces tenemos que calcularlo */
    for (int i = 0; i < n; i++) {
        /* Removemos la ciudad número i, así como la ciudad número 0 */
        mask = (rowMax - 1) - (1 << i);
        masked = set & mask;

        /* Si el resultado fue diferente al set que teníamos */
        if (masked != set) {
            /* La distancia desde la ciudad start hasta la i + el camino de la
             * ciudad i */
            temp = graph[start * n + i] + compute(i, masked);

            /* Si la distancia obtenida es la menor de todas */
            if (temp < result) {
                result = temp;
                path[start * rowMax + set] = i;
            }
        }
    }

    /* Almacenamos el resultado y lo regresamos */
    distanceMatrix[start * rowMax + set] = result;
    return result;
}

void getPath(int start, int set) {
    /* Si ya terminamos de recorrer todo el grafo */
    if (path[start * rowMax + set] == -1) return;

    int x = path[start * rowMax + set];
    int mask = (rowMax - 1) - (1 << x);
    int masked = set & mask;

    printf("%d ", x + 1);
    getPath(x, masked);
}
