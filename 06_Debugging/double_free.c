#include <stdlib.h>

#define N 1000

int main() {
    int *array = (int *)malloc(sizeof(int)*N);
    for(int i = 0; i < N; i++) {
        array[i] = i;
    }
    for(int i = 1; i < N; i++) {
        array[i] += array[i-1];
    }
    free(array);
    free(array);
    return 0;
}
