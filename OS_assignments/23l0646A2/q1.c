#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>



int half1[25000], half2[25000];

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high] ; // last element pivot
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) { // if curr smaller than j element
            i++;
            swap(&arr[i], &arr[j]); // moving smaller to the left 
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1; 
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quicksort(arr, low, p - 1);  // calls recursively
        quicksort(arr, p + 1, high);
    }
}

void* thread1(void* arg) {
    quicksort(half1, 0, (25000) - 1);
    return NULL;
}

void* thread2(void* arg) {  // insertion sort 
    for (int i = 1; i < 25000; i++) {
        int key = half2[i], j = i - 1;
        while (j >= 0 && half2[j] > key) {
            half2[j + 1] = half2[j];
            j--;
        }
        half2[j + 1] = key;
    }
    return NULL;
}

void wfile(const char* filename, int data[], int size) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", data[i]);
    }
    fclose(file);
}

int main() {
    srand(time(0));
    int arr[50000];
    for (int i = 0; i < 50000; i++){
        arr[i] = rand() % 100000;
    } 
    for (int i = 0; i < 25000 ; i++) {
        half1[i] = arr[i];
        half2[i] = arr[i + 25000];
    }

    pthread_t t1, t2;
    clock_t start1, end1, start2, end2;
    
    start1 = clock();
    pthread_create(&t1, NULL, thread1, NULL);
    start2 = clock();
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    end1 = clock();
    pthread_join(t2, NULL);
    end2 = clock();

    printf("thread 1 time: %f seconds\n", ((double)(end1 - start1)) / CLOCKS_PER_SEC);
    printf("thread 2 time: %f seconds\n", ((double)(end2 - start2)) / CLOCKS_PER_SEC);

    wfile("firstHalf.txt", half1, 25000);
    wfile("secondHalf.txt", half2, 25000);
    printf("Done\n");
    return 0;
}