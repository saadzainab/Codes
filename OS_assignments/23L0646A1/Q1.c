#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int arr[10];


void insertionsort(int p) {
    int key = arr[p];  // Current element to insert
    int j = p- 1;

    while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];  // Shift elements forward
        j--;
    }
    arr[j + 1] = key;  // Place in correct position
}


void print(int p) {
    printf("P %d: (pid: %d, ppid: %d)\n Array: ", p + 1, getpid(), getppid());
    for (int i = 0; i <= p; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

    // converting to int
    for (int i = 0; i < 10; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    //starts at position 0
    for (int i = 0; i < 10; i++) {
        insertionsort(i);  // Sort up to current position
        print(i);  

        if (i < 10 - 1) {
            pid_t pid = fork();

            if (pid < 0) {
                printf("error");
            }
            else if (pid > 0) {
                wait(NULL);
                exit(0);
            }
            // Child process increments
        }
    }

    return 0;
}
