//
// Created by Jacob Smith on 2020-05-09.
//
#include <pthread.h>

#ifndef A1_COMMON_H
#define A1_COMMON_H

typedef struct Job {
  /**
   * The name of the user. Maximum 10 digits so I don't have to deal with memory.
   */
  char name[10];
  /**
   * The name of the process.
   */
  char process;
  int arrival;
  int duration;
  struct Job* next;
} Job;

typedef struct {
  Job* first;
} JobQueue;

/**
 * Create a list of jobs from stdin.
 * @param queue Where to place the jobs.
 */
void processStdin(JobQueue* jobs);
void freeJobs(Job* job);

typedef struct User {
  /**
   * The name of the user. Maximum 10 digits so I don't have to deal with memory.
   */
  char name[10];
  /**
   * The end time of the last process.
   */
  int endTime;
  struct User* next;
} User;

typedef struct UserQueue {
  struct User* first;
} UserQueue;

void freeUsers(User* user);
User* findUserOrAppend(UserQueue* queue, char* name);
void printSummary(UserQueue* users);

typedef struct Processor {
  int id;
  /**
   * The start time of a job plus the duration. This value is garbage when in the idle stack.
   */
  int endTime;
  pthread_t* thread;
  /**
   * Represents the next value in the queue/stack.
   */
  struct Processor* next;
} Processor;

Processor* createProcessor(int id);
void freeProcessors(Processor* processor);


/**
 * Inserts into the priority queue based on "endTime" (in ascending order).
 * @param queue The queue.
 * @param processor The processor to insert.
 * @return The new queue.
 */
Processor* insert(Processor* queue, Processor* processor);

/**
 * Append to the end of the queue.
 * @param queue The queue.
 * @param processor The processor.
 * @return The new queue.
 */
Processor* appendQueue(Processor* queue, Processor* processor);

/**
 * Remove from the front of the queue.
 * @param queue The queue.
 * @return The new queue.
 */
Processor* deque(Processor* queue);

/**
 * Print now idling processors. A recursive function to print out the processors now idling.
 * Basically what this does is print out the remaining n processors.0
 */
int printIdleProcessors(Processor* queue, int time, int n);

#endif
