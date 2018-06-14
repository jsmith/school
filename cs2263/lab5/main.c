//
// Jacob Smith 47118500
// Raven-Lee Mills 47308881
//

#include <stdio.h>
#include "vector.h"
#include "sort.h"
#include "math.h"
#include "search.h"

int main() {
    int n_vectors, i;
    scanf("%d", &n_vectors);
    Vector vectors[n_vectors];

    for (i = 0; i < n_vectors; i++){
        scanf("%d %d", &vectors[i].x, &vectors[i].y);
        vectors[i].index = i;
    }

    int targets[n_vectors];
    for (i = 0; i < n_vectors; i++){
        scanf("%d", &targets[i]);
    }

    for (i = 0 ; i < n_vectors; i ++){
        vectors[i].length = (int) sqrt( (double)((vectors[i].x * vectors[i].x) + (vectors[i].y * vectors[i].y)));
    }

    selectionSort(vectors, n_vectors);
    for (i = 0; i < n_vectors; i++) {
        int index = binarySearch(vectors, n_vectors, targets[i]);
        if (index == -1) {
            printf("-1\n");
        } else {
            printf("%d\n", vectors[index].index);
        }
    }
}