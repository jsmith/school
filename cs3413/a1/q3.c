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
static pthread_mutex_t pendingMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t runningMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t userMutex = PTHREAD_MUTEX_INITIALIZER;
static JobQueue jobs = { .first = NULL };
/**
 * Processors that haven't started yet.
 */
static Processor* pendingStart = NULL;
/**
 * Currently running processors.
 */
static Processor* running = NULL;
static UserQueue users = { .first = NULL };

typedef struct ThreadData {
  /**
   * The ID of the thread.
   */
  Job* job;

  /**
   * The time the thread started (for reference when printing)
   */
  int time;
} ThreadData;

void* run(void* arg) {
  ThreadData data = *((ThreadData*)arg); // make a copy on the stack
  free(arg);

  pthread_mutex_lock(&pendingMutex);
  // We don't check for NULL but "run" should never be called without placing process in "pendingStart"
  Processor* previous = NULL;
  Processor* nowRunning = pendingStart;
  while (nowRunning->id != data.id) {
    previous = nowRunning;
    nowRunning = nowRunning->next;
  }

  // From pending from queue since it is now running
  if (previous == NULL) {
    pendingStart = pendingStart->next;
  } else {
    pendingStart->next = pendingStart->next->next;
  }
  pthread_mutex_unlock(&pendingMutex);

  // We can now also remove the process from the jobs queue
  pthread_mutex_lock(&jobsMutex);
  Job* targetJob = jobs.first;
  jobs.first = jobs.first->next;
  pthread_mutex_unlock(&jobsMutex);

  nowRunning->endTime = data.time + targetJob->duration;

  // Now we can push into the running queue
  pthread_mutex_lock(&runningMutex);
  running = insert(running, nowRunning);
  pthread_mutex_unlock(&runningMutex);

  pthread_mutex_lock(&userMutex);
  User* user = findUserOrAppend(&users, targetJob->name);
  user->endTime = max(nowRunning->endTime, user->endTime); // the max is very important
  pthread_mutex_unlock(&userMutex);

  // Sleep first
  printf("Thread %d sleeping for %d\n", data.id, duration);
  sleep(duration);

  // Now print out the thread information
  printf("%d\tCPU %d %c\n", data.time, data.id, targetJob->process);

  // Free job now that we're done with it
  free(targetJob);

  return 0;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid # of arguments. Expected one argument.\n");
    return 1;
  }

  int n = str2int(argv[argc - 1]);
  Processor* idleQueue = NULL;
  for (int i = 0; i < n; i++) {
    idleQueue = appendQueue(idleQueue, createProcessor(i + 1));
  }

  processStdin(&jobs);

  printf("Time\tJob\n");

  int time = 0;
  // While there are still jobs to be run and processors running
  while (jobs.first != NULL || running != NULL || pendingStart != NULL) {
    int numCPUsFinished = 0;
    while (running != NULL && running->endTime <= time) {
      // Dequeue from the processing queue
      pthread_mutex_lock(&runningMutex);
      Processor* nowIdle = running;
      running = deque(running);
      pthread_mutex_unlock(&runningMutex);

      printf("Joining %d @ %d\n", nowIdle->id, time);
      pthread_join(*(nowIdle->thread), NULL);
      nowIdle->thread = NULL;

      // Now we can enqueue the finished processor in the idle queue
      idleQueue = appendQueue(idleQueue, nowIdle);
      numCPUsFinished++;
    }

    int numJobsAdded = 0;
    while (jobs.first != NULL && jobs.first->arrival <= time && idleQueue != NULL) {
      Processor* nowPending = idleQueue;
      idleQueue = deque(idleQueue);

      // First let's add it to the pending queue
      // We do this *before* we start the thread
      pthread_mutex_lock(&pendingMutex);
      pendingStart = appendQueue(pendingStart, nowPending);
      pthread_mutex_unlock(&pendingMutex);

      printf("Now running %d @ %d\n", nowPending->id, time);
      pthread_t* thread = malloc(sizeof(pthread_t));
      ThreadData *arg = malloc(sizeof(ThreadData));
      arg->id = nowPending->id;
      arg->time = time;
      pthread_create(thread, NULL, &run, arg); // note that we pass the start time to each thread
      nowPending->thread = thread;

      numJobsAdded++;
    }

    // If numCPUsFinished > numJobsAdded we need to print out the processors that are now idling
    // Since we are using a queue, the processors that just finished will the last processors to be
    // used (and will be at the end of the queue).
    // The following function recursively goes to the end of the queue and print out
    // n = numCPUsFinished - numJobsAdded lines of text containing something like "10 CPU 2 IDLE"
    printIdleProcessors(idleQueue, time, numCPUsFinished - numJobsAdded);

    time++;
  }

  printf("\n");
  printSummary(&users);

  pthread_mutex_destroy(&jobsMutex);
  freeJobs(jobs.first);
  freeProcessors(idleQueue);
}
