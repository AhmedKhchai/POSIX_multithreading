/* CELEBP27 */
#define _OPEN_THREADS
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
void *handler(void *arg) {

  printf("we're going to sleep for '%d'\n", arg);
  sleep('%d', arg);
  for (int i = 0; i < 1000000; i++) {
  }

}

main() {
  pthread_t tOne;
  pthread_t tTwo;
  pthread_t tThree;
  pthread_t tFour;

  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&attr,SCHED_FIFO);

  struct sched_param param;
  pthread_attr_getschedparam (&attr, &param);
  (param.sched_priority)++;
  pthread_attr_setschedparam (&attr, &param);

  if (pthread_create(&tOne, &attr, handler, 1) != 0) {
    perror("pthread_create() error");
    exit(1);
  }
  (param.sched_priority)++;
    if (pthread_create(&tTwo, &attr, handler, 2) != 0) {
    perror("pthread_create() error");
    exit(1);
  }
  (param.sched_priority)++;
    if (pthread_create(&tThree, &attr, handler, 3)!= 0) {
    perror("pthread_create() error");
    exit(1);
  }
  (param.sched_priority)++;
    if (pthread_create(&tFour, &attr, handler, 4) != 0) {
    perror("pthread_create() error");
    exit(1);
  };



}
