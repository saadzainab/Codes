#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t mutex; //shared variables
sem_t waitA;     
sem_t waitB;      

int rope = 0;           // currently on the rope
int countA = 0;           // waiting at A
int countB = 0;           // waiting at B
int direction = 0;        // 0 = A->B, 1 = B->A 
int passed = 0;           // crossed in this direction

void *chimpanzee(void *arg) {
    int id = *((int *)arg);
    int dir = rand() % 2; // chimpanzee dir 

if (dir == 0) {
    printf("Chimpanzee %d arrived at point A\n", id);
} 
else {
    printf("Chimpanzee %d arrived at point B\n", id);
}


if (dir == 0) { // A to B
    sem_wait(&mutex);
    countA++;  // Add to waiting count at A
    while (direction != 0 || rope >= 5 || passed >= 10) {
        sem_post(&mutex);
        sem_wait(&waitA);
        sem_wait(&mutex);
    }
    countA--;
    rope++;     // on rope
    passed++;     // crossing
    sem_post(&mutex);
} 
else { // B to A
    sem_wait(&mutex);
    countB++;    // Add to count at B
    while (direction != 1 || rope >= 5 || passed >= 10) {
        sem_post(&mutex);
        sem_wait(&waitB);
        sem_wait(&mutex);
    }
    countB--;
    rope++;    // on rope
    passed++;
    sem_post(&mutex);
}

if (dir == 0) {
    printf("Chimpanzee %d is crossing from A to B\n", id);
} 
else {
    printf("Chimpanzee %d is crossing from B to A\n", id);
}

sleep(1);

if (dir == 0) {
    printf("Chimpanzee %d has crossed to B\n", id);
} 
else {
    printf("Chimpanzee %d has crossed to A\n", id);
}


    sem_wait(&mutex);
    rope--; // One less on rope now

    // If no one is on the rope, switch direction
    if (rope == 0) {
       if ((passed >= 10 && ((direction == 0 && countB > 0) || (direction == 1 && countA > 0))) ||
            ((direction == 0 && countA == 0 && countB > 0) || (direction == 1 && countB == 0 && countA > 0))) {
            direction = 1 - direction; // change direction
            passed = 0;                // Reset counter
        }

        // Wake up chimpanzees on the current direction side
        int i;
        if (direction == 0) {
            for (i = 0; i < 5 && countA > 0; i++) {
                sem_post(&waitA);
            }
        } else {
            for (i = 0; i < 5 && countB > 0; i++) {
                sem_post(&waitB);
            }
        }
    }

    sem_post(&mutex); 
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]); 
    pthread_t threads[n];
    int ids[n];

    sem_init(&mutex, 0, 1);     
    sem_init(&waitA, 0, 0);     
    sem_init(&waitB, 0, 0);     

    srand(time(NULL)); 

    for (int i = 0; i < n; i++) {
        ids[i] = i + 1;
        pthread_t t;
        pthread_create(&t, NULL, chimpanzee, &ids[i]);
        pthread_detach(t);
    }

    sleep(3); 
    return 0;
}
