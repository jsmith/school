//
// Created by Jacob Smith on 2020-05-09.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "lib.h"

typedef struct Processor {
  int id;
  /**
   * The start time of a job plus the duration. This value is garbage when in the idle stack.
   */
  int endTime;
  /**
   * Represents the next value in the queue/stack.
   */
  struct Processor* next;
} Processor;

Processor* createProcessor(int id) {
  Processor* processor = (Processor*)malloc(sizeof(Processor));
  processor->next = NULL;
  processor->endTime = -1;
  processor->id = id;
  return processor;
}

void freeProcessors(Processor* processor) {
  if (processor == NULL) {
    return;
  }

  freeProcessors(processor->next);
  free(processor);
}

/**
 * Insert into the priority queue by "endTime". The soonest "endTime" is at the start of the queue.
 */
Processor* insert(Processor* queue, Processor* processor) {
  if (queue == NULL) {
    return processor;
  }

  Processor* previous = NULL;
  Processor* current = queue;
  while (current != NULL && current->endTime < processor->endTime) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    // if it goes at the end
    previous->next = processor;
  } else if (previous == NULL) {
    // if it goes at the start
    processor->next = current;
    queue = processor;
  } else {
    // else if it goes in the middle
    previous->next = processor;
    processor->next = current;
  }

  return queue;
}

/**
 * Append the processor to the end of the queue
 */
Processor* appendIdle(Processor* queue, Processor* processor) {
  if (queue == NULL) {
    return processor;
  }

  while (queue->next != NULL) {
    queue = queue->next;
  }

  queue->next = processor;
  return queue;
}

/**
 * Print now idling processors. A recursive function to print out the processors now idling.
 * Basically what this does is print out the remaining n processors.0
 */
int printIdleProcessors(Processor* queue, int time, int n) {
  if (n <= 0) {
    return n;
  }

  if (queue == NULL) {
    return n;
  }

  n = printIdleProcessors(queue->next, time, n);
  if (n <= 0) {
    return n;
  }

  printf("%d\tCPU %d IDLE\n", time, queue->id);
  return n - 1;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid # of arguments. Expected one argument.\n");
    return 1;
  }

  int n = str2int(argv[argc - 1]);
  Processor* idleQueue = NULL;
  for (int i = 0; i < n; i++) {
    idleQueue = appendIdle(idleQueue, createProcessor(i + 1));
  }

  JobQueue jobs = { .first = NULL };
  int result = processStdin(&jobs);
  if (result != 0) {
    return result;
  }

  printf("Time\tJob\n");

  Processor* running = NULL;

  UserQueue users = { .first = NULL };
  int time = 0;
  // While there are still jobs to be run and processors running
  while (jobs.first != NULL || running != NULL) {
    int numCPUsFinished = 0;
    while (running != NULL && running->endTime <= time) {
      // Dequeue from the processing queue
      Processor* nowIdle = running;
      running = running->next;
      nowIdle->next = NULL; // important since stack/queue are sharing "next" pointers

      // Now we can enqueue the finished processor in the idle queue
      idleQueue = appendIdle(idleQueue, nowIdle);
      numCPUsFinished++;
    }

    int numJobsAdded = 0;
    while (jobs.first != NULL && jobs.first->arrival <= time && idleQueue != NULL) {
      Processor* nowRunning = idleQueue;
      idleQueue = idleQueue->next;
      nowRunning->next = NULL; // important since stack/queue sharing "next" pointers
      nowRunning->endTime = time + jobs.first->duration;

      // Now we can push into the processing queue
      running = insert(running, nowRunning);

      User* user = findUserOrAppend(&users, jobs.first->name);
      user->endTime = max(nowRunning->endTime, user->endTime); // the max is very important

      // print out the job we just ran
      printf("%d\tCPU %d %c\n", time, nowRunning->id, jobs.first->process);

      // We can now also remove the process from the jobs queue
      Job* temp = jobs.first;
      jobs.first = jobs.first->next;
      free(temp); // free now since we are done with it
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

  freeJobs(jobs.first);
  freeProcessors(idleQueue);
}
