#define _OPEN_THREADS
#define _GNU_SOURCE
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <sys/time.h>

void handler(int arg) {
  struct timeval t0, t1, dt;
  gettimeofday(&t0, NULL);
  printf("we're going to sleep for '%d'\n", arg);
  sleep('%d',arg);
  for (int i = 0; i < 1000000; i++) {
  }
  gettimeofday(&t1, NULL);
  timersub(&t1, &t0, &dt);
  fprintf(stderr, "the thread took %d.%06d sec\n",
   dt.tv_sec, dt.tv_usec);
}

pthread_t limiteThreadCpu(pthread_t* thread){
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
  // this function takes a thread and is supposed to specify the cpu core that should be assigned to the passed thread
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&attr,SCHED_FIFO);

  struct sched_param param;
  pthread_attr_getschedparam (&attr, &param);
  param.sched_priority = 10;
  pthread_attr_setschedparam (&attr, &param);

  if (pthread_create(&tOne, &attr, handler, 1) != 0) {
    perror("pthread_create() error");
    exit(1);
  }
  param.sched_priority = 20;
  pthread_attr_setschedparam (&attr, &param);
    if (pthread_create(&tTwo, &attr, handler, 2) != 0) {
    perror("pthread_create() error");
    exit(1);
  }
  param.sched_priority = 30;
  pthread_attr_setschedparam (&attr, &param);
    if (pthread_create(&tThree, &attr, handler, 3)!= 0) {
    perror("pthread_create() error");
    exit(1);
  }
  param.sched_priority = 40;
  pthread_attr_setschedparam (&attr, &param);
    if (pthread_create(&tFour, &attr, handler, 4) != 0) {
    perror("pthread_create() error");
    exit(1);
  };

  pthread_join(tOne, NULL);
  pthread_join(tTwo, NULL);
  pthread_join(tThree, NULL);
  pthread_join(tFour, NULL);

  return 0;
}
