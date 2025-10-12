#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int ready = 0; 

void* waiter(void* arg) {
    pthread_mutex_lock(&lock);

    while (!ready) { 
        printf("Waiter: waiting for signal...\n");
        //pthread_cond_wait atomically unlocks mutex
        //until a signal has been received
        pthread_cond_wait(&cond, &lock);
    }

    printf("Waiter: got signal! ready = %d\n", ready);

    pthread_mutex_unlock(&lock);
    return NULL;
}

void* signaler(void* arg) {
    sleep(2);

    pthread_mutex_lock(&lock);
    ready = 1;
    printf("Signaler: setting ready=1 and signaling...\n");
    pthread_cond_broadcast(&cond); 
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, waiter, NULL);
    pthread_create(&t2, NULL, signaler, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

