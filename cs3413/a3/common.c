//
// Created by Jacob Smith on 2020-05-22.
//
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "common.h"
#include "list.h"

void insert(JobQueue* jobs, Job* newJob, JobPriority priority) {
  // If the queue is empty
  // It's easier to handle this case at the start
  Job* previous = NULL;
  Job* current = jobs->first;
  while (
    current != NULL && 
    (
      // Handle all three priority queues
      // The first really isn't a priority queue at all though
      (priority == None) ||
      // Priority queue where the highest priority (lowest value) goes first
      (priority == Priority && current->priority <= newJob->priority) ||
      // Priority queue where the smallest duration goes first
      (priority == Duration && current->duration <= newJob->duration)
    )
  ) {
    previous = current;
    current = current->next;
  }

  if (previous == NULL) {
    // Handles the case that the queue is empty
    // and if the new job goes at the start of the queue
    jobs->first = newJob;
    newJob->next = current;
  } else {
    // else if it goes in the middle or at the end
    previous->next = newJob;
    newJob->next = current;
  }
}

StringArray* split(char* target, char c) {
  StringArray* a = initStringArray(10);
  char* pch = strtok(target, &c);
  while (pch != NULL) {
    appendStringArray(a, pch);
    pch = strtok(NULL, &c);
  }

  return a;
}

void freeJobs(Job* job) {
  if (job == NULL) {
    return;
  }

  freeJobs(job->next);
  free(job);
}

Job* createJob(char* name, char process, int arrival, int duration, int priority) {
  Job* job = (Job*)malloc(sizeof(Job));
  job->next = NULL;
  // This is important since the name value could be temporary (and actually is in my implementation)=
  strcpy(job->name, name);
  job->process = process;
  job->arrival = arrival;
  job->duration = duration;
  job->sliceRemaining = -1;
  job->slicesRemaining = -1;
  job->priority = priority;
  job->currentQueue = -1;
  return  job;
}

/**
 * Processes jobs from stdin and adds them to the queue.
 * @param jobs The jobs
 * @param priority The priority to use.
 */
void processStdin(JobQueue* jobs, JobPriority priority) {
  // freopen("../input_q1.txt", "r", stdin); // Only use for testing

  char inputLine[100];
  fgets(inputLine, sizeof(inputLine), stdin); // eat up the first line of the input
  while (fgets(inputLine, sizeof(inputLine), stdin) != NULL) {
    inputLine[strcspn(inputLine, "\n")] = '\0'; // remove the trailing newline
    StringArray* words = split(inputLine, '\t');
    if (words->used != 5) {
      printf("Parsed the incorrect # of words in the line: %d", words->used);
      exit(1);
    }

    Job* job = createJob(
        words->array[0],
        words->array[1][0],
        str2int(words->array[2]),
        str2int(words->array[3]),
        str2int(words->array[4])
    );

    insert(jobs, job, priority);
    freeStringArray(words);
  }
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

int str2int(char *s) {
  char *end;
  if (s[0] == '\0' || isspace(s[0])) {
    printf("Unable to convert \"%s\" to a string\n", s);
    exit(1);
  }

  errno = 0;
  long l = strtol(s, &end, 10);
  if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX)) {
    printf("Overflow detected \"%s\"\n", s);
    exit(1);
  } else if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN)) {
    printf("Underflow detected \"%s\"\n", s);
    exit(1);
  } else if (*end != '\0') {
    printf("Unable to convert \"%s\" to a string\n", s);
    exit(1);
  }

  return (int)l;
}

Job* deque(JobQueue* queue) {
  // Dequeue from the processing queue
  Job* front = queue->first;
  if (front == NULL) {
    return NULL;
  }

  queue->first = front->next;
  // It is important that we remove this reference
  front->next = NULL;

  return front;
}
