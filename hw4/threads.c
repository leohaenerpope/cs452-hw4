#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#include "threads.h"
#include "error.h"

typedef struct{
    pthread_t *array;
    int count;
} *ThreadsRep;

extern Threads threads_create(int n, void*(*f)(void *), void *arg) { 
    ThreadsRep tr = malloc(sizeof(*tr));
    if (!tr) ERROR("malloc failed in threads.c threads_create()");

    tr->count = n;
    tr->array = malloc(sizeof(pthread_t) * n);
    if (!tr->array) ERROR("malloc failed in threads.c threads_create()");

    for (int i = 0; i < n; i++) {
        if (pthread_create(&tr->array[i], NULL, f, arg) != 0) {
            ERROR("pthread_create failed in threads.c threads_create()");
        }
    }
    return tr;
}

extern void threads_join(Threads t) {
    ThreadsRep tr = (ThreadsRep) t;
    
    for (int i = 0; i < tr->count; i++) {
        if (pthread_join(tr->array[i], NULL) != 0) {
            ERROR("pthread_join failed in threads.c threads_join()");
        }
    }

    free(tr->array);
    free(tr);
}