//
// Created by Jacob Smith on 2020-05-09.
//
#include <stdio.h>
#include <string.h>
#include "common.h"

int main() {
  JobQueue jobs = { .first = NULL };
//  freopen("../input.txt", "r", stdin); // Only use for testing

  int result = processStdin(&jobs);
  if (result != 0) {
    return result;
  }

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
  printSummary(&users);

  freeJobs(jobs.first);
  freeUsers(users.first);
}
