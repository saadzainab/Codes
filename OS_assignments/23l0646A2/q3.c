#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


char light[6] = "Red";

void* toggle(void* arg) {
    while (1) {
        if (rand() % 2 == 0) {
            strcpy(light, "Red");
        } else {
            strcpy(light, "Green");
        }
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

void* display(void* arg) {
    while (1) {
        printf("\r%s Light   ", light);
        fflush(stdout);
        sleep(1); 
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    int score = 0;
    char input;

    pthread_t t1, t2;
    pthread_create(&t1, NULL, toggle, NULL);
    pthread_create(&t2, NULL, display, NULL);

    printf("\nstart playing\n");

    while (1) {
        input = getchar();
        if (input == '\n') {
         
            if (strcmp(light, "Green") == 0) {
                score++;
                printf("\nCorrect! Score: %d\n", score);
            } else {
                printf("\nGame Over. Final Score: %d\n", score);
                break;
            }
        }
    }

    return 0;
}

/*
leads to race condition as both might try to alter the "light" 
*/
