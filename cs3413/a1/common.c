//
// Created by Jacob Smith on 2020-05-09.
//
#include "common.h"
#include "list.h"
#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void freeJobs(Job* job) {
  if (job == NULL) {
    return;
  }

  freeJobs(job->next);
  free(job);
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

int processStdin(JobQueue* jobs) {
    freopen("../input.txt", "r", stdin); // Only use for testing

  char inputLine[100];
  fgets(inputLine, sizeof(inputLine), stdin); // eat up the first line of the input
  while (fgets(inputLine, sizeof(inputLine), stdin) != NULL) {
    inputLine[strcspn(inputLine, "\n")] = '\0'; // remove the trailing newline
    StringArray* words = split(inputLine, '\t');
    if (words->used != 4) {
      printf("Parsed the incorrect # of lines: %d", words->used);
      return 1;
    }

    char* name = words->array[0];
    char process = words->array[1][0];
    int arrival = str2int(words->array[2]);
    int duration = str2int(words->array[3]);

    Job* job = createJob(name, process, arrival, duration);
    append(jobs, job);
    freeStringArray(words);
  }

  return 0;
}

User* createUser(char* name) {
  User* user = (User*)malloc(sizeof(User));
  strcpy(user->name, name);
  user->next = NULL;
  user->endTime = -1;
  return user;
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

void printSummary(UserQueue* users) {
  printf("Summary\n");
  User* user = users->first;
  while (user != NULL) {
    printf("%s\t%d\n", user->name, user->endTime);
    user = user->next;
  }
}