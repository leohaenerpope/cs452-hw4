#ifndef THREADS_H
#define THREADS_H

typedef void *Threads;

// Creates pthreads (with an array of pthread ids), executing function f for each thread along with info args
Threads threads_create(int n, void *(*f)(void *), void *arg);

// Joins up all threads and frees data
void threads_join(Threads t);

#endif