#include <stdio.h>
#include "lib.h"
#include <stdlib.h>
#include <string.h>

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

void append(JobQueue* runList, Job* newJob) {
  if (runList->first == NULL) {
      runList->first = newJob;
      return;
  }

  Job* current = runList->first;
  while (current->next != NULL) {
      current = current->next;
  }

  current->next = newJob;
}

User* createUser(char* name) {
  User* user = (User*)malloc(sizeof(User));
  strcpy(user->name, name);
  user->next = NULL;
  user->endTime = -1;
  return user;
}

Job* createJob(char* name, char process, int arrival, int duration) {
  Job* job = (Job*)malloc(sizeof(Job));
  job->next = NULL;
  strcpy(job->name, name);
  job->process = process;
  job->arrival = arrival;
  job->duration = duration;
  return  job;
}

User* findUserOrAppend(UserQueue* queue, char* name) {
  if (queue->first == NULL) {
    queue->first = createUser(name);
    return queue->first;
  }

  User* user = queue->first;
  while (user->next != NULL && strcmp(user->name, name) != 0) {
    user = user->next;
  }

  if (strcmp(user->name, name) == 0) {
    return user;
  }

  user->next = createUser(name);
  return user->next;
}

void freeUsers(User* user) {
  if (user == NULL) {
    return;
  }

  freeUsers(user->next);
  free(user);
}

void freeJobs(Job* job) {
  if (job == NULL) {
    return;
  }

  freeJobs(job->next);
  free(job);
}

/**
 * Assumptions:
 * 1. The input comes from stdin.
 * 2. Processes are identified by a *single* char.
 * 3. The maximum size of a user's name is 10 characters.
 */
int main() {
  // TODO
  //  CharArray* a = readFromStdin();
  char contents[] = "User	Process	Arrival	Duration\nJim	A	2	5\nMary	B	2	3\nSue	D	5	5\nMary	C	6	4\n";
  // char* contents = readFile("assets/a1-input.txt")->contents;
  //  char* contents = a->array;

  JobQueue jobs = { .first = NULL };

  StringArray* lines = split(contents, '\n');
  for (int i = 1; i < lines->used; i++) {
    StringArray* words = split(lines->array[i], '\t');

    char* name = words->array[0];
    char process = words->array[1][0];
    int arrival;
    int duration;
    StringToIntError error = str2int(&arrival, words->array[2], 10);
    if (error != STR2INT_SUCCESS) {
        printf("Error parsing arrival: %d", error);
        return 1;
    }


    error = str2int(&duration, words->array[3], 10);
    if (error != STR2INT_SUCCESS) {
        printf("Error parsing duration: %d", error);
        return 1;
    }

    Job* job = createJob(name, process, arrival, duration);
    append(&jobs, job);
    freeStringArray(words);
  }
  freeStringArray(lines);

  printf("Time\tJob\n");

  int time = 0;

  UserQueue users = { .first = NULL };
  Job* current = jobs.first;
  while (current != NULL) {
    if (time == 0) {
      printf("%d\t%c\n", current->arrival, current->process);
      time = current->arrival + current->duration;
    } else {
      printf("%d\t%c\n", time, current->process);
      time = time + current->duration;
    }

    User* user = findUserOrAppend(&users, current->name);
    user->endTime = time;
    current = current->next;
  }
  printf("%d\tIDLE\n", time);

  printf("\n");
  printf("Summary\n");
  User* user = users.first;
  while (user != NULL) {
    printf("%s\t%d\n", user->name, user->endTime);
    user = user->next;
  }

  freeJobs(jobs.first);
  freeStringArray(lines);
  freeUsers(users.first);
  // freeCharArray(a);
}
