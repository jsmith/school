//
// Created by Jacob Smith on 2020-05-09.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "lib.h"

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

  JobQueue jobs = { .first = NULL };
  processStdin(&jobs);

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
      running = deque(running);

      // Now we can enqueue the finished processor in the idle queue
      idleQueue = appendQueue(idleQueue, nowIdle);
      numCPUsFinished++;
    }

    int numJobsAdded = 0;
    while (jobs.first != NULL && jobs.first->arrival <= time && idleQueue != NULL) {
      Processor* nowRunning = idleQueue;
      idleQueue = deque(idleQueue);
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
