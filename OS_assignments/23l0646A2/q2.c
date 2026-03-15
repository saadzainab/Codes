#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int **A, **B, **C;
int n;

void* multiply(void *arg) {
    int *rows = (int *)arg;
    int start = rows[0], end = rows[1];

    for (int i = start; i < end; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {

    n = atoi(argv[1]); // convert num to int
    srand(time(0));

    // memory alloc on heap
    A = malloc(n * sizeof(int *));
    B = malloc(n * sizeof(int *));
    C = malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {   // memory alloc for each row
        A[i] = malloc(n * sizeof(int));
        B[i] = malloc(n * sizeof(int));
        C[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {  // add random numbers 
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

   
    FILE *file1 = fopen("A.txt", "w");
    FILE *file2 = fopen("B.txt", "w");
   
    for (int i = 0; i < n; i++) {       // printing in files
        for (int j = 0; j < n; j++) {
            fprintf(file1, "%d ", A[i][j]);
            fprintf(file2, "%d ", B[i][j]);
        }
        fprintf(file1, "\n");
        fprintf(file2, "\n");
    }
    fclose(file1);
    fclose(file2);


    printf("[");

    for (int i = 1; i <= 128; i++) { // i = number of threads
        pthread_t *threads = malloc(i * sizeof(pthread_t));  
       

        clock_t start, end;
        start = clock();  // Start timing

        int rowperthread = n / i;  // how many rows / thread
        int remaining = n % i;
        int rstart = 0;

        for (int j = 0; j < i; j++) {  
            int *args = malloc(2 * sizeof(int));
           
            // assign start and end rows 
            args[0] = rstart;
            int extrarow = 0;
            if (j < remaining) {
                extrarow = 1;
            }
            args[1] = rstart + rowperthread + extrarow;

            rstart = args[1];

            pthread_create(&threads[j], NULL, multiply, args);
        }

        for (int j = 0; j < i; j++) {     // all threads complete exec
            pthread_join(threads[j], NULL);
        }

        end = clock();  
        double time = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("(%d, %d, %f)", n, i, time);
        if (i < 128) {
            printf(", ");
        }
        free(threads); 
    }

    printf("]\n");

    // copy to c
    FILE *file3 = fopen("C.txt", "w");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file3, "%d ", C[i][j]);
        }
        fprintf(file3, "\n");
    }
    fclose(file3);

    // Free memory
    for (int i = 0; i < n; i++) {
        free(A[i]); free(B[i]); free(C[i]);
    }
    free(A); free(B); free(C);

    return 0;
}