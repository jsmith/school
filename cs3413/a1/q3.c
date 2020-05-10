//
// Created by Jacob Smith on 2020-05-09.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include <pthread.h>
#include "lib.h"
#include <unistd.h>

static pthread_mutex_t jobsMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t userMutex = PTHREAD_MUTEX_INITIALIZER;
static JobQueue jobs = { .first = NULL };
static UserQueue users = { .first = NULL };


void* run(void* arg) {
  int id = *((int*)arg); // make a copy on the stack
  free(arg);
  int time = 0;

  while (1) {
    pthread_mutex_lock(&jobsMutex);
    if (jobs.first == NULL) {
      printf("%d\tCPU %d IDLE\n", time, id);
      pthread_mutex_unlock(&jobsMutex); // lol make sure to unlock
      break;
    }

    Job* job = jobs.first;
    jobs.first = jobs.first->next;
    pthread_mutex_unlock(&jobsMutex);

    if (job->arrival > time) {
      if (time != 0) {
        printf("%d\tCPU %d IDLE\n", time, id);
      }
      // printf("%d sleeping for %d\n", id, job->arrival - time);
      sleep(job->arrival - time);
    }

    // The time can't be less than the arrival time of a process (ie. we can't process until a job arrives)
    time = max(job->arrival, time);
    int endTime = time + job->duration;

    pthread_mutex_lock(&userMutex);
    User* user = findUserOrAppend(&users, job->name);
    user->endTime = max(endTime, user->endTime); // the max is very important
    pthread_mutex_unlock(&userMutex);

    // Now print out the thread information
    printf("%d\tCPU %d %c\n", time, id, job->process);

    // And then sleep
    // printf("Thread %d sleeping for %d @ %d to process %c\n", id, job->duration, time, job->process);
    sleep(job->duration);
    time = endTime;

    // make sure to free the job since we are done with it
    free(job);
  }

  return 0;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid # of arguments. Expected one argument.\n");
    return 1;
  }

  // Process jobs first so threads have something to do
  processStdin(&jobs);

  // Print this too before processors start
  printf("Time\tJob\n");

  int n = str2int(argv[argc - 1]);
  Processor* threadQueue = NULL;
  for (int i = 0; i < n; i++) {
    Processor* processor = createProcessor(i + 1);
    threadQueue = appendQueue(threadQueue, processor);
    pthread_t* thread = malloc(sizeof(pthread_t));
    int* arg = malloc(sizeof(int));
    (*arg) = processor->id;
    pthread_create(thread, NULL, &run, arg); // note that we pass the start time to each thread
    processor->thread = thread;
  }

  // Join the threads
  while (threadQueue != NULL) {
    // printf("Joining %d\n", threadQueue->id);
    pthread_join(*(threadQueue->thread), NULL);
    threadQueue = threadQueue->next;
  }

  freeProcessors(threadQueue);

  printf("\n");
  printSummary(&users);

  pthread_mutex_destroy(&jobsMutex);
  pthread_mutex_destroy(&userMutex);
}
