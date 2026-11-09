#ifndef THREADS_H
#define THREADS_H

typedef void *Threads;

Threads threads_create(int n, void *(*f)(void *), void *arg);

void threads_join(Threads t);

#endif