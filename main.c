/* CELEBP27 */
#define _OPEN_THREADS
#define _GNU_SOURCE

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>

void *handler(void *arg) {

  printf("we're going to sleep for '%d'\n", arg);
  sleep('%d', arg);
  for (int i = 0; i < 100000000; i++) {
  }

}
pthread_t *limiteThreadCpu(pthread_t* thread){
    cpu_set_t cpuset;
    thread = pthread_self();
    CPU_ZERO(&cpuset);
	CPU_SET(1, &cpuset);
	pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
	return thread;
}
int main() {
  pthread_t tOne;
  pthread_t tTwo;
  pthread_t tThree;
  pthread_t tFour;
  tOne = limiteThreadCpu(tOne);
  tTwo = limiteThreadCpu(tTwo);
  tThree = limiteThreadCpu(tThree);
  tFour = limiteThreadCpu(tFour);

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
  int pthread_join(tOne, null);
  int pthread_join(tTwo, null);
  int pthread_join(tThree, null);
  int pthread_join(tFour, null);
  return 0;
}
