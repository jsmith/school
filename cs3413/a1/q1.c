//
// Created by Jacob Smith on 2020-05-09.
//
#include <stdio.h>
#include <string.h>
#include "common.h"

int main() {
  JobQueue jobs = { .first = NULL };
  processStdin(&jobs);

  printf("Time\tJob\n");

  int time = 0;
  UserQueue users = { .first = NULL };
  Job* current = jobs.first;
  while (current != NULL) {
    if (time < current->arrival) {
      if (time != 0) {
        printf("%d\tIDLE\n", time);
      }

      time = current->arrival;
    }

    printf("%d\t%c\n", time, current->process);
    time = time + current->duration;

    User* user = findUserOrAppend(&users, current->name);
    user->endTime = time;
    current = current->next;
  }
  printf("%d\tIDLE\n", time);

  printf("\n");
  printSummary(&users);

  freeJobs(jobs.first);
  freeUsers(users.first);
}
