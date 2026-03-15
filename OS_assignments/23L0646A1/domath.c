#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void execution(const char *operation, int number, int pipee) {
    // Convert number and pipe to string (execv only takes strings)
    char numstr[12];
    snprintf(numstr, sizeof(numstr), "%d", number);

    char pipestr[12];
    snprintf(pipestr, sizeof(pipestr), "%d", pipee);

    char *arguments[] = { (char *)operation, numstr, pipestr, NULL };

    // Forming executable path
    char execpath[256];
    snprintf(execpath, sizeof(execpath), "./%s", operation);

    // Execute the operation
    if (execv(execpath, arguments) == -1) {
        printf("execv failed");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("error\n");
        return 1;
    }

    int x = argc - 2; // Number of operations
    char *operations[5]; 
    int number = atoi(argv[argc - 1]); // Initial number

    // Get operations
    for (int i = 0; i < x; i++) {
        operations[i] = argv[i + 1];
    }

    //execute operations in reverse order
    for (int i = x - 1; i >= 0; i--) {
        int pipe1[2]; 

        // Create a pipe
        if (pipe(pipe1) == -1) {
            printf("pipe failed");
            return 1;
        }

        pid_t pid = fork();
        if (pid < 0) {
            printf("fork failed");
            return 1;
        } 
        else if (pid == 0) {
            // Child 
            close(pipe1[0]);
            execution(operations[i], number, pipe1[1]);
        } 
        else {
            // Parent 
            close(pipe1[1]); 
            wait(NULL); 

            if (read(pipe1[0], &number, sizeof(number)) == -1) {
                printf("read failed");
                return 1;
            }
            close(pipe1[0]); // Close read end
        }
    }

    printf("RESULT : %d\n", number);
    return 0;
}
