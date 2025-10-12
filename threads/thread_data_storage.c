#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MINIMUM_NUM_KEYS 128

#ifdef PTHREAD_KEYS_MAX
pthread_key_t keys[PTHREAD_KEYS_MAX];
#else
pthread_key_t keys[MINIMUM_NUM_KEYS];
#endif

void destructor(void *ptr_to_alloc_mem) {
    printf("Destructor on TDS invoked\n");
    free((char*)ptr_to_alloc_mem);
}

void* thread1(void* arg) {
    char* tds = malloc(0xff);
    if (!tds) {
        fprintf(stderr, "failed calling malloc\n");
        pthread_exit(NULL);
    }

    snprintf(tds, 0xff, "this is thread1");
    pthread_setspecific(keys[0], (void*)tds);

    char* data = (char*)pthread_getspecific(keys[0]);
    printf("From thread1: %s\n", data);

    pthread_exit(NULL);
}

void* thread2(void* arg) {
    char* tds = malloc(0xff);
    if (!tds) {
        fprintf(stderr, "failed calling malloc\n");
        pthread_exit(NULL);
    }

    snprintf(tds, 0xff, "this is thread2");
    pthread_setspecific(keys[0], (void*)tds);

    char* data = (char*)pthread_getspecific(keys[0]);
    printf("From thread2: %s\n", data);

    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    if (pthread_key_create(&keys[0], destructor) != 0) {
        fprintf(stderr, "Failed to create pthread key\n");
        return 1;
    }

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_key_delete(keys[0]);

    return 0;
}

