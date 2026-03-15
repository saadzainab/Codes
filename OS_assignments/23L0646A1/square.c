
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   
    if (argc < 3) {
       printf("error");
    }

    int n = atoi(argv[1]);        //no of args
    int pipee = atoi(argv[2]); // pipe

  
    int result = n * n;

    if (write(pipee, &result, sizeof(result)) == -1) {
        printf("write failed");
     }

    close(write_fd);
    return 0;
}