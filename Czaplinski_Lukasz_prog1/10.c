#include "common.h"
#include <pthread.h>
#define THREAD_NR 4

void* routine(void* barrier)
{
  assert(barrier!=NULL);
  printf(" thread id: %lld\n", (long long int)pthread_self());
  int r;
  r = pthread_barrier_wait((pthread_barrier_t*) barrier);
  if(r != PTHREAD_BARRIER_SERIAL_THREAD && r != 0)
  {
    printf("pthread_barrier_wait failed\n");
  }
  return NULL;
}

int main(void)
{
  char str[64];
  pthread_barrier_t barrier;
  pthread_barrier_init(&barrier, NULL, THREAD_NR+1);
  pthread_t threads[THREAD_NR];
  for (int i = 0; i < THREAD_NR; i++) {
    sprintf(str, "thread nr %d creation failed", i);
    CERRS(pthread_create(&threads[i],NULL,&routine, (void*) &barrier) != 0,str);
  }
  sprintf(str, "ps -T -%d", getpid());
  system(str);
  pthread_barrier_wait(&barrier);
  return 0;
}
