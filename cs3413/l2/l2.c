#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

// Note this ignores -1 pids
int main() {
  int pid1 = 0; // child pid
  int p1[2]; // child 1 pipe file descriptors

  int pid2 = 0;
  int p2[2];

  int pid3 = 0;
  int p3[2];

  pipe(p1);
  pipe(p2);
  pipe(p3);

  printf("Creating p1!\n");
  pid1 = fork();
  bool is1 = pid1 == 0;
  bool isParent = pid1 > 0;

  if (isParent) {
    printf("Creating p2!\n");
    pid2 = fork();
  }

  bool is2 = isParent && pid2 == 0;
  isParent = isParent && pid2 > 0;
  if (isParent) {
    printf("Creating p3!\n");
    pid3 = fork();
  }

  bool is3 = isParent && pid3 == 0;
  isParent = isParent && pid3 > 0;

  int k;
  if (is1) {
    printf("I'm the first!\n");
    while (true) {
      read(pipe_r, &k, sizeof(k));
      printf("GOT %d\n", k);
      if (k == 0) {
        break;
      }
      
    }
  } else if (is2) {
    printf("I'm the second!\n");
  } else if (is3) {
    printf("I'm the third!\n");
  } else {
    printf("I'm the parent!\n");
    while (scanf("%d", &k) == 1) {
      printf("read number: %d\n", k);
      write(pipe_w, &k, sizeof(k));
    }

    printf("Waiting for 3 child processes!\n");
    wait(&pid1);
    wait(&pid2);
    wait(&pid3);
  }

  close(p1);
  close(p2);
  close(p3);
}
