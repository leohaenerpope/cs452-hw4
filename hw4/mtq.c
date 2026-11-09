#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mtq.h"
#include "error.h"

typedef struct {
    Deq q;
    int capacity;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} *Rep;

static Rep rep(Mtq q) {
    if (!q) ERROR("bad pointer for q in mtq.c rep()");
    return (Rep)q;
}

extern Mtq mtq_new(int capacity) {
    Rep r = malloc(sizeof(*r));
    if (!r) ERROR("malloc failed in mtq.c mtw_new()");

    r->q = deq_new();
    r->capacity = capacity;

    pthread_mutex_init(&r->mutex, NULL);
    pthread_cond_init(&r->not_empty, NULL);
    pthread_cond_init(&r->not_full, NULL);

    return r;
}

extern int  mtq_len(Mtq q) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);
    int len = deq_len(r->q);
    pthread_mutex_unlock(&r->mutex);
    return len;
}

extern void mtq_head_put(Mtq q, Data d) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);

    while (r->capacity > 0 && deq_len(r->q) >= r->capacity) {
        pthread_cond_wait(&r->not_full, &r->mutex);
    }

    deq_head_put(r->q, d);

    pthread_cond_signal(&r->not_empty);
    pthread_mutex_unlock(&r->mutex);
}
extern Data mtq_head_get(Mtq q) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);
    
    while (deq_len(r->q) == 0) pthread_cond_wait(&r->not_empty, &r->mutex);

    Data d = deq_head_get(r->q);

    pthread_cond_signal(&r->not_full);
    pthread_mutex_unlock(&r->mutex);
    return d;
}
extern Data mtq_head_ith(Mtq q, int i) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);
    Data d = deq_head_ith(&r->q, i);
    pthread_mutex_unlock(&r->mutex);
    return d;
}
extern Data mtq_head_rem(Mtq q, Data d) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);
    Data res = deq_head_rem(r->q, d);
    if (res) pthread_cond_signal(&r->not_full);
    pthread_mutex_unlock(&r->mutex);
    return res;
}

extern void mtq_tail_put(Mtq q, Data d) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);

    while (r->capacity > 0 && deq_len(r->q) >= r->capacity) {
        pthread_cond_wait(&r->not_full, &r->mutex);
    }

    deq_tail_put(r->q, d);

    pthread_cond_signal(&r->not_empty);
    pthread_mutex_unlock(&r->mutex);
}
extern Data mtq_tail_get(Mtq q) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);
    
    while (deq_len(r->q) == 0) pthread_cond_wait(&r->not_empty, &r->mutex);

    Data d = deq_tail_get(r->q);

    pthread_cond_signal(&r->not_full);
    pthread_mutex_unlock(&r->mutex);
    return d;
}
extern Data mtq_tail_ith(Mtq q, int i) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);
    Data d = deq_tail_ith(&r->q, i);
    pthread_mutex_unlock(&r->mutex);
    return d;
}
extern Data mtq_tail_rem(Mtq q, Data d) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);
    Data res = deq_tail_rem(r->q, d);
    if (res) pthread_cond_signal(&r->not_full);
    pthread_mutex_unlock(&r->mutex);
    return res;
}

extern void mtq_map(Mtq q, DeqMapF f) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);
    deq_map(r->q, f);
    pthread_mutex_unlock(&r->mutex);
}
extern void mtq_del(Mtq q, DeqMapF f) {
    if (!q) return;
    Rep r = (Rep)q;

    deq_del(r->q, f);
    pthread_mutex_destroy(&r->mutex);
    pthread_cond_destroy(&r->not_empty);
    pthread_cond_destroy(&r->not_full);
    free(r);
}
extern Str  mtq_str(Mtq q, DeqStrF f) {
    Rep r = rep(q);
    pthread_mutex_lock(&r->mutex);
    Str s = deq_str(r->q, f);
    pthread_mutex_unlock(&r->mutex);
    return s;
}