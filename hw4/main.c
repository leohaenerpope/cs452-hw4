#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"
#include "threads.h"
#include "mtq.h"
 
static void *produce(void *a) {
  void **arg = a;
  Mtq q = (Mtq)arg[0];
  Lawn l = (Lawn)arg[1];
  usleep(200000);
  mtq_tail_put(q, mole_new(l, 0, 0));
  return 0;
}
static void *consume(void *a) {
  void **arg = a;
  Mtq q = (Mtq)arg[0];

  Mole m  = mtq_head_get(q);
  if (m) mole_whack(m);
  return 0;
}

int main() {
  srandom(time(0));
  const int n=10;
  Lawn lawn=lawn_new(0,0);
  Mtq q = mtq_new(4);

  void *p_arg[] = {q, lawn};
  void *c_arg[] = {q};


  Threads prods = threads_create(n, produce, p_arg);
  Threads cons = threads_create(n, consume, c_arg);
  threads_join(prods);
  threads_join(cons);

  mtq_del(q, 0);
  lawn_free(lawn);
  return 0;
}
