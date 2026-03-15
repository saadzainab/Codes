#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



int shared_var = 0;
int plus, minus, total;

int flag[50]; // taking max threads as 50
int turn[50];

void entercs(int id) {
    for (int level = 0; level < total ;level++) {
        flag[id] = level; // at this level says it wants to enter
        turn[level] = id; // sets turn 

        for (int j = 0; j < total; j++) { // checks if anyother is above or at that lvl its that threads turn
            if (j == id) continue;

            while (flag[j] >= level && turn[level] == id) {
                // wait
            }
        }
    }
}

void exitcs(int id) {
    flag[id] = -1;
}

void* increment(void* arg) {
    int id = *((int*)arg);

    entercs(id);

    int temp = shared_var;
    usleep(1000); // simulate work
    shared_var = temp + 1;
    printf("Thread %d incremented: %d\n", id, shared_var);

    exitcs(id);
    return NULL;
}

void* decrement(void* arg) {
    int id = *((int*)arg);

    entercs(id);

    int temp = shared_var;
    usleep(1000); // simulate work
    shared_var = temp - 1;
    printf("Thread %d decremented: %d\n", id, shared_var);

    exitcs(id);
    return NULL;
}

int main(int argc, char* argv[]) {
    plus = atoi(argv[1]);
    minus = atoi(argv[2]);
    total= plus + minus;

    for (int i = 0; i < total; i++) {
        flag[i] = -1;
    }

    pthread_t threads[total];
    int ids[total];

    for (int i = 0; i < plus; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, increment, &ids[i]);
    }

    for (int i = plus; i < total; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, decrement, &ids[i]);
    }

    for (int i = 0; i < total; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final value of shared_var: %d\n", shared_var);
    return 0;
}
