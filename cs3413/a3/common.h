//
// Created by Jacob Smith on 2020-05-16.
//

#ifndef A2_COMMON_H
#define A2_COMMON_H

#include "list.h"

#define NAME_BUFFER_SIZE 50
#define NUM_SLICES 3

typedef struct Job {
  /**
   * The name of the user.
   */
  char name[NAME_BUFFER_SIZE];
  /**
   * The name of the process.
   */
  char process;
  int arrival;
  /**
   * The remaining duration of the job.
   */
  int duration;
  /**
   * The amount of time remaining on the slice.
   */
  int sliceRemaining;
  int priority;
  /**
   * Remaining slices. Each job gets NUM_SLICES on each queue before being demoted.
   */
  int slicesRemaining;
  struct Job* next;
  int currentQueue;
} Job;

typedef struct {
  Job* first;
} JobQueue;

typedef struct User {
  /**
   * The name of the user.
   */
  char name[NAME_BUFFER_SIZE];
  /**
   * The end time of the last process.
   */
  int endTime;
  struct User* next;
} User;

typedef struct UserQueue {
  struct User* first;
} UserQueue;

typedef enum {
  /**
   * Prioritize based on nothing (ie. disabled priority and just append).
   */
  None,
  /**
   * Prioritize based on priority value.
   */
  Priority,
  /**
   * Prioritize based on duration remaining.
   */
  Duration
} JobPriority;

int str2int(char *s);
void processStdin(JobQueue* jobs, JobPriority priority);
void freeJobs(Job* job);
Job* deque(JobQueue* queue);
void printSummary(UserQueue* users);
User* findUserOrAppend(UserQueue* queue, char* name);
void insert(JobQueue* jobs, Job* newJob, JobPriority priority);
StringArray* split(char* target, char c);

#endif //A2_COMMON_H
