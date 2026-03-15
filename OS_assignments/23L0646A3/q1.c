#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int light = 0; 
int flag[2] = {0, 0}; 
int turn = 0;
int over = 0;
int score = 0;


void* toggle(void* arg) {
    while (!over) {
        sleep(1); 

        flag[0] = 1;
        turn = 1;
        while (flag[1] == 1 && turn == 1); 

        // Cs -> change light 
        light = rand() % 2; 

        flag[0] = 0;
    }
    return NULL;
}

void* display(void* arg) {
    while (!over) {
        
        flag[1] = 1;
        turn = 0;
        while (flag[0] == 1 && turn == 0); 

        // Cs -> display 
        if (light == 1) {
            printf("\rGreen Light ");
        } 
        else {
            printf("\rRed Light ");
        }
        fflush(stdout);

        flag[1] = 0;

        sleep(1); 
    }
    return NULL;
}


int main() {
    pthread_t t1, t2;
    srand(time(0));

    pthread_create(&t1, NULL, toggle, NULL);
    pthread_create(&t2, NULL, display, NULL);

    while (!over) {
        getchar(); //press enter
        if (light) {
            score++;
            printf("\nscore= %d\n", score);
        } 
        else {
            printf("Game Over! score: %d\n", score);

            over = 1;
        }
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}