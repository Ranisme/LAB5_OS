#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int sell = 0;
int product = 0;
sem_t sem;


void* seller(void* arg) {
    while(1) {
        sem_wait(&sem);
        if (sell <= product) {
            sell++;
            printf("[SELLER] sell = %d, product = %d\n", sell, product);
        }
    }
    return NULL;
}

void* worker(void* arg) {
    while(1) {
        if (product <= sell + 1083) {
            product++;
            printf("[WORKER] sell = %d, product = %d\n", sell, product);
        }
        sem_post(&sem);
    }
    return NULL;
}

int main() {
    pthread_t seller_thread, worker_thread;

    sem_init(&sem, 0, 1);

    pthread_create(&seller_thread, NULL, seller, NULL);
    pthread_create(&worker_thread, NULL, worker, NULL);

    sleep(10);
    return 0;
}
