#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void findmax(int arr[], int start, int end, int pipe1[]);

int main() {
    int arr[100], n = 0;
    FILE *file = fopen("input.txt", "r");

    if (!file) {
        printf("Error");
    }

    while (fscanf(file, "%d", &arr[n]) != EOF && n < 100) {
        n++;
    }
    fclose(file);

    if (n == 0) {
        printf("error");
    }

    int pipe1[2];  // File descriptors for pipe
    if (pipe(pipe1) == -1) {
        printf("Pipe failed");
    }

    pid_t pid = fork();
    if (pid < 0) {
        printf("Fork failed");
    } 
    else if (pid == 0) {
        close(pipe1[0]);  // Close unused read end
        findmax(arr, 0, n - 1, pipe1);
    } 
    else {
        close(pipe1[1]);  // Close unused write end
        int max;
        read(pipe1[0], &max ,sizeof(max));
        close(pipe1[0]);

        wait(NULL);  // Wait for the child process
        printf("The maximum value is: %d\n", max);
    }

    return 0;
}


void findmax(int arr[], int start, int end, int pipe1[]) {
    if (start == end) {
        int maxnum= arr[start];
        write(pipe1[1], &maxnum, sizeof(maxnum));
        close(pipe1[1]);
        exit(0);
    }

    int mid = (start + end) / 2;
    int leftpipe[2], rightpipe[2];
    
    pipe(leftpipe);
    pipe(rightpipe);

    pid_t pid1 = fork(); //left
    if (pid1 == 0) {
        close(leftpipe[0]);
        findmax(arr, start, mid, leftpipe);
    }

    pid_t pid2 = fork(); // right
    if (pid2 == 0) {
        close(rightpipe[0]);
        findmax(arr, mid + 1, end, rightpipe);
    }

    // Parent process waits and reads values from both children
    close(leftpipe[1]);
    close(rightpipe[1]);

    int maxleft, maxright;
    read(leftpipe[0], &maxleft, sizeof(maxleft));
    read(rightpipe[0], &maxright, sizeof(maxright));

    close(leftpipe[0]);
    close(rightpipe[0]);

    wait(NULL);
    wait(NULL);

    int maxnum;
    if (maxleft > maxright) {
        maxnum = maxleft;
    }
    else {
        maxnum = maxright;
    }

    write(pipe1[1], &maxnum, sizeof(maxnum));
    close(pipe1[1]);
    exit(0);
}
