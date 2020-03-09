#include <stdio.h>
#include "lib.h"
#define LENGTH 4
#define FIXED_PERIOD 2

typedef struct Job {
  char process;
  int value;
  int fallback;
  int arrival;
  int duration;
  struct Job* next;
} Job;

typedef struct {
  Job* first;
} Queue;

void append(Queue* runList, Job* newJob) {
  Job* previous = NULL;
  Job* job = runList->first;
  while (job != NULL) {
    if (newJob->value < job->value) {
        break;
    } else if (newJob->value == job->value && newJob->fallback < job->fallback) {
        break;
    }

    previous = job;
    job = job->next;
  }

  newJob->next = job;
  if (previous == NULL) {
    // printf("Previous is null. Initializing \"first\". %c\n", newJob->process);
    runList->first = newJob;
  } else {
    // printf("Previous is not null! %c\n", newJob->process);
    previous->next = newJob;
  }
}

// Return can be null
void run(Queue* runList, int* time) {
  Job* top = runList->first;

  if (top == NULL) {
    (*time)++;
    return;
  }

  runList->first = runList->first->next;
  int difference = min(FIXED_PERIOD, top->duration);
  printf("%d\t%c\n", *time, top->process);
  (*time) += difference;

  top->value = top->value - difference;
  if (top->value > 0) {
    append(runList, top);
  }
}

int main() {
  // TODO
//  CharArray* a = readFromStdin();
   char contents[] = "User	Process	Arrival	Duration\nJim	A	2	5\nMary	B	2	3\nSue	D	5	5\nMary	C	6	2\n";
  // char* contents = readFile("assets/a1-input.txt")->contents;
//  char* contents = a->array;


  StringArray* lines = split(contents, '\n');
  Job jobs[4];
  Queue queue;
  queue.first = NULL;
  Queue runList;
  runList.first = NULL;

  for (int i = 1; i < lines->used; i++) {
    StringArray* words = split(lines->array[i], '\t');
    // printf("%s\n", lines->array[i]);
    // printf("%d", words->used);

    char process = words->array[1][0];
    int arrival;
    int duration;
    str2int(&arrival, words->array[2], 10);
    str2int(&duration, words->array[3], 10);

    jobs[i - 1].process = process;
    jobs[i - 1].value = arrival;
    jobs[i - 1].fallback = duration;
    jobs[i - 1].arrival = arrival;
    jobs[i - 1].duration = duration;
    jobs[i - 1].next = NULL;

    // printf("Adding job to run list!\n");
    append(&queue, &jobs[i - 1]);
    freeStringArray(words);
  }

  printf("Time\tJob\n");
  int time = 0;

  while(queue.first != NULL || runList.first != NULL) {
    Job* first = queue.first;
    while (first != NULL && first->arrival <= time) {
      Job* temp = first;
      temp->value = temp->duration;
      first = temp->next;
      append(&runList, temp);
    }
    queue.first = first;

    run(&runList, &time);
  }

  freeStringArray(lines);
  // freeCharArray(a);
}
