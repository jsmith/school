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

void processStdin(JobQueue* jobs) {
  // freopen("../input_complex.txt", "r", stdin); // Only use for testing

  char inputLine[100];
  fgets(inputLine, sizeof(inputLine), stdin); // eat up the first line of the input
  while (fgets(inputLine, sizeof(inputLine), stdin) != NULL) {
    inputLine[strcspn(inputLine, "\n")] = '\0'; // remove the trailing newline
    StringArray* words = split(inputLine, '\t');
    if (words->used != 4) {
      printf("Parsed the incorrect # of lines: %d", words->used);
      exit(1);
    }

    char* name = words->array[0];
    char process = words->array[1][0];
    int arrival = str2int(words->array[2]);
    int duration = str2int(words->array[3]);

    Job* job = createJob(name, process, arrival, duration);
    append(jobs, job);
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

Processor* createProcessor(int id) {
  Processor* processor = (Processor*)malloc(sizeof(Processor));
  processor->next = NULL;
  processor->endTime = -1;
  processor->thread = NULL;
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
Processor* appendQueue(Processor* queue, Processor* processor) {
  if (queue == NULL) {
    return processor;
  }

  Processor* current = queue;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = processor;
  return queue;
}

Processor* deque(Processor* queue) {
  // Dequeue from the processing queue
  Processor* front = queue;
  queue = queue->next;
  front->next = NULL; // important since stack/queue are sharing "next" pointers
  return queue;
}
