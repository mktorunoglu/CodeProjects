#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define SIZE 5

void *multiply(void* arg) {
    int *data = (int *) arg;
    int i, j = 0;
    int x = data[0];

    for(i = 1; i <= x; i++) {
        j += data[i] * data[i + x];
    }

    int *p = (int*)malloc(sizeof(int));
    *p = j;
    pthread_exit(p);
}

int main() {
    int matrixA[SIZE][SIZE] = {
        {7, 1, 1, 8, 7},
        {1, 8, 0, 8, 3},
        {6, 7, 0, 7, 4},
        {4, 9, 5, 9, 2},
        {3, 2, 7, 1, 3},
    };
    int matrixB[SIZE][SIZE] = {
        {1, 1, 8, 6, 7},
        {4, 7, 4, 1, 5},
        {1, 0, 8, 6, 4},
        {2, 3, 9, 8, 0},
        {3, 9, 7, 6, 7},
    };
    int i, j;
    
    printf("A marisi:\n");
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }
    
    printf("\nB marisi:\n");
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++)
            printf("%d ", matrixB[i][j]);
        printf("\n");
    }
    
    int max = SIZE * SIZE;
    pthread_t *threads;
    threads = (pthread_t*)malloc(max*sizeof(pthread_t));

    int k, counter = 0;
    int* data = NULL;

    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            data = (int *)malloc((20)*sizeof(int));
            data[0] = SIZE;

            for(k = 0; k < SIZE; k++) {
                data[k + 1] = matrixA[i][k];
            }

            for(k = 0; k < SIZE; k++) {
                data[k + SIZE + 1] = matrixB[k][j];
            }

            pthread_create(&threads[counter++], NULL, multiply, (void*)(data));
        }
    }

    printf("\nA ve B matrisinin carpimi sonucu olusan C matrisi:\n");
    for(i = 0; i < max; i++) {
        void *k;
        pthread_join(threads[i], &k);

        int *p = (int *)k;
        printf("%d ", *p);
        if((i + 1) % SIZE == 0) {
            printf("\n");
        }
    }
    return 0;
}

