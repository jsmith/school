#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"
#include <pthread.h>
#define TIME_QUANTUM 2

// TODO ensure we correctly handle the arrival time of incoming jobs

static UserQueue users = { .first = NULL };
static JobQueue incoming = { .first = NULL };
static JobQueue queue0 = { .first = NULL };
static JobQueue queue1 = { .first = NULL };
static JobQueue queue2 = { .first = NULL };
static JobQueue queue3 = { .first = NULL };
static bool debug = false;

/**
User	  Process	Arrival	Duration	  Priority
Jim	    A	      2	      5	          4
Mary	  B	      2	      3	          7
Sue	    D	      5	      5	          2
Mary	  C	      6	      4	          1
 */

void* run() {
  int time = 0;
  Job* running = NULL;
  bool isRunning = false;

  while (true) {
    // For this time iteration, insert all of the jobs that have arrived in queue0 based on their
    // priority
    while (incoming.first != NULL && incoming.first->arrival <= time) {
      Job* newJob = deque(&incoming);
      // Make sure to do this right away since the output *must* be in order of arrival
      // I lost marks for this in a1
      if (debug) printf("%d\t%c [arrived, duration -> %d, priority -> %d]\n", time, newJob->process, newJob->duration, newJob->priority);
      findUserOrAppend(&users, newJob->name);
      newJob->sliceRemaining = TIME_QUANTUM; // Init for first time
      newJob->slicesRemaining = 1; // init to 1 for queue0
      insert(&queue0, newJob, Priority);
    }

    // Ok so always decrement these first
    // They will always be > 0 at this point
    if (running != NULL) {
      running->sliceRemaining--;
      running->duration--;
    }

    // If neither of them are finished continue to the next iteration
    if (
        running != NULL &&
        running->sliceRemaining > 0 &&
        running->duration > 0 &&
        // Implement preemption here
        // If we receive a job that is higher priority we want to grab that job
        // If the queue0 is empty or if the highest priority value in queue0 is greater or equal
        // to the currently running job then *don't* interrupt
        // Else we make it grab a new job
        (queue0.first == NULL || queue0.first->priority >= running->priority)
    ) {
      // Don't forget to increment the time.
      time += 1;
      continue;
    }

    // This logic must go before we find a new job
    // The job we put back in the queue might be the next job we take out of the queue
    if (running != NULL && running->duration == 0) {
      if (debug) printf("%d\t%c [finished]\n", time, running->process);
      User* user = findUserOrAppend(&users, running->name);
      user->endTime = time;
      free(running);
    } else if (running != NULL) {
      // This means the running process has finished its slice but is *not* finished
      // Or it means the running process has been kicked out by a higher priority process
      // Sooo we gotta queue it back up

      // Check if it's finished its slice
      if (running->sliceRemaining == 0) {
        // If so decrement the remaining slices
        running->slicesRemaining--;

        // First, check if we need to demote the job
        // Demote if there are no more slices to run
        if (running->slicesRemaining == 0) {
          // Reset the # slices
          running->slicesRemaining = NUM_SLICES;

          // Do the demotion
          running->currentQueue++;

          // Make sure to wrap back around the queue since there are only 4 queues
          // We go from the 3rd queue back to the first queue (not the zeroth queue)
          if (running->currentQueue == 4) {
            running->currentQueue = 1;
          }
        }
      } else {
        // else do nothing
        // do not decrement or reset slicesRemaining and do not change the queue
      }

      if (debug) printf("%d\t%c [move -> %d, remaining -> %d, slice -> %d]\n", time, running->process, running->currentQueue, running->duration, running->sliceRemaining);

      if (running->currentQueue == 0) {
        insert(&queue0, running, Priority);
      } else if (running->currentQueue == 1) {
        insert(&queue1, running, None);
      } else if (running->currentQueue == 2) {
        insert(&queue2, running, Duration);
      } else {
        insert(&queue3, running, None);
      }
    }

    // The queue where the new job came from
    Job* newJob = NULL;
    if (queue0.first != NULL) {
      // Based on priority
      newJob = deque(&queue0);
      newJob->slicesRemaining = 1; // init slices remaining to 1
      newJob->currentQueue = 0;
    } else if (queue1.first != NULL) {
      // Round robin
      newJob = deque(&queue1);
      newJob->currentQueue = 1;
    } else if (queue2.first != NULL) {
      // Based on duration remaining
      newJob = deque(&queue2);
      newJob->currentQueue = 2;
    }  else if (queue3.first != NULL) {
      // Round robin
      newJob = deque(&queue3);
      newJob->currentQueue = 3;
    }  else {
      // Ok... so there is nothing in the queues
      // If there are still more jobs left then just continue to the next iteration
      // otherwise we've processed all jobs
      if (incoming.first) {
        if (isRunning) {
          isRunning = false;
          printf("%d\tIDLE\n", time);
        }

        // Make sure to increment!!
        time += 1;
        running = NULL;
        continue;
      } else {
        printf("%d\tIDLE\n", time);
        break;
      }
    }

    // If we've made it this far we have a new job to run
    // So we *know* that we are now running
    isRunning = true;

    // This is important. When we get a new job, reset the slice remaining time
    // Only reset iff it's zero
    // Sometimes we need to context switch due to preemption and we don't want to reset the
    // sliceRemaining in this situation
    if (newJob->sliceRemaining <= 0) {
      newJob->sliceRemaining = TIME_QUANTUM;
    }

    // Finally, print out the job information for the new job
    if (debug) printf("%d\t%c [start, from -> %d]\n", time, newJob->process, newJob->currentQueue);
    else printf("%d\t%c\n", time, newJob->process);

    running = newJob;
    time += 1;
  }

  return 0;
}

int main() {
  pthread_t cpu;
  processStdin(&incoming, None);

  printf("Time\tJob\n");
  pthread_create(&cpu, NULL, &run, NULL);
  pthread_join(cpu, NULL);

  printf("\n");
  printSummary(&users);
}
