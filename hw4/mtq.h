// Wrapper for deq to make it multi-thread safe
// Basically just does the deq function you want but utilizes mutexes and mutex conditions to make sure
// the action being performed is multi-thread safe (no other thread is doing something to it while current thread is doing something)

#ifndef MTQ_H
#define MTQ_H

#include "deq.h"

typedef void *Mtq;

extern Mtq  mtq_new(int capacity);
extern int  mtq_len(Mtq q);

extern void mtq_head_put(Mtq q, Data d);
extern Data mtq_head_get(Mtq q);
extern Data mtq_head_ith(Mtq q, int i);
extern Data mtq_head_rem(Mtq q, Data d);

extern void mtq_tail_put(Mtq q, Data d);
extern Data mtq_tail_get(Mtq q);
extern Data mtq_tail_ith(Mtq q, int i);
extern Data mtq_tail_rem(Mtq q, Data d);

extern void mtq_map(Mtq q, DeqMapF f);
extern void mtq_del(Mtq q, DeqMapF f);
extern Str  mtq_str(Mtq q, DeqStrF f);



#endif