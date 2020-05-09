//
// Created by Jacob Smith on 2020-05-09.
//

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

int processStdin(JobQueue* queue);
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

#endif
