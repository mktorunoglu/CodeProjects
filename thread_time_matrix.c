#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <time.h>

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

int main(int argc, char *argv[]) {

    clock_t timeMainStart = clock();
    srand(time(NULL));

    int rowA = atoi(argv[1]), colA = atoi(argv[2]), rowB = atoi(argv[2]), colB = atoi(argv[3]), i, j;
    int matrixA[rowA][colA];  
    int matrixB[rowB][colB];

    for(i = 0; i < rowA; i++) {

        for (j = 0; j < colA; j++) {
            matrixA[i][j] = rand() % 10;
        }
    }

    for (i = 0; i < rowB; i++) {

        for (j = 0; j < colB; j++) {
            matrixB[i][j] = rand() % 10;
        }
    }
    
    printf("A marisi (%s x %s):\n", argv[1], argv[2]);

    for(i = 0; i < rowA; i++) {

        for(j = 0; j < colA; j++) {
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }
    
    printf("\nB marisi (%s x %s):\n", argv[2], argv[3]);

    for(i = 0; i < rowB; i++){

        for(j = 0; j < colB; j++)
            printf("%d ", matrixB[i][j]);
        printf("\n");
    }
    
    int max = rowA * colB;
    pthread_t *threads;
    threads = (pthread_t*)malloc(max*sizeof(pthread_t));

    int k, counter = 0;
    int* data = NULL;

    clock_t timeThreadStart[max];
    clock_t timeThreadEnd[max];

    for(i = 0; i < rowA; i++) {

        for(j = 0; j < colB; j++) {
            data = (int *)malloc((20)*sizeof(int));
            data[0] = colA;

            for(k = 0; k < colA; k++) {
                data[k + 1] = matrixA[i][k];
            }

            for(k = 0; k < rowB; k++) {
                data[k + colA + 1] = matrixB[k][j];
            }

            timeThreadStart[counter] = clock();
            pthread_create(&threads[counter++], NULL, multiply, (void*)(data));
        }
    }

    float timeCounter[max];
    printf("\nA ve B matrisinin carpimi sonucu olusan C matrisi (%s x %s):\n", argv[1], argv[3]);

    for(i = 0; i < max; i++) {
        void *k;
        pthread_join(threads[i], &k);
        
        timeThreadEnd[i] = clock();
        double timeThread = ((double)(timeThreadEnd[i] - timeThreadStart[i])) / CLOCKS_PER_SEC;
        timeCounter[i] = timeThread;

        int *p = (int *)k;
        printf("%d ", *p);

        if((i + 1) % colB == 0) {
            printf("\n");
        }
    }
    printf("\n");

    for(i = 0; i < max; i++) {
        printf("%d.threadin harcadigi zaman: %f\n", i + 1, timeCounter[i]);
    }
    printf("\n");

    clock_t timeMainEnd = clock();
    double timeMain = ((double)(timeMainEnd - timeMainStart)) / CLOCKS_PER_SEC;
    printf("Tum kodun harcadigi zaman: %f\n", timeMain);

    return 0;
}

