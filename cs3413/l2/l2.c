#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#define WRITE 1
#define READ 0

int fd1[2];
int fd2[2];
int fd3[2];

int minValue = INT_MAX;
int maxValue = INT_MIN;
int averageValue = 0;

void* min() {
  int k;
  while (1) {
    read(fd1[READ], &k, sizeof(k));
    if (k == 0) {
      break;
    }

    if (k < minValue) {
      minValue = k;
    }
  }
  return 0;
}

void* max() {
  int k;
  while (1) {
    read(fd2[READ], &k, sizeof(k));
    if (k == 0) {
      break;
    }

    if (k > maxValue) {
      maxValue = k;
    }
  }
  return 0;
}

void* average() {
  int k;
  int sum = 0;
  int n = 0;
  while (1) {
    read(fd3[READ], &k, sizeof(k));
    if (k == 0) {
      break;
    }

    sum += k;
    n++;
  }

  averageValue = sum / n;
  return 0;
}

// Note this ignores -1 pids
int main() {
  pipe(fd1);
  pipe(fd2);
  pipe(fd3);

  pthread_t t1;
  pthread_t t2;
  pthread_t t3;

  printf("Creating 3 child threads!\n");
  pthread_create(&t1, NULL, &min, NULL);
  pthread_create(&t2, NULL, &max, NULL);
  pthread_create(&t3, NULL, &average, NULL);

  int k;
  while (scanf("%d", &k) == 1) {
    printf("read number: %d\n", k);
    write(fd1[WRITE], &k, sizeof(k));
    write(fd2[WRITE], &k, sizeof(k));
    write(fd3[WRITE], &k, sizeof(k));

    if (k == 0) {
      break;
    }
  }

  // If use piped in values and never specified 0 at the end
  // This wasn't specified in the assignment but I handle this situation just in case
  if (k != 0) {
    k = 0;
    write(fd1[WRITE], &k, sizeof(k));
    write(fd2[WRITE], &k, sizeof(k));
    write(fd3[WRITE], &k, sizeof(k));
  }


  printf("Waiting for 3 child threads!\n");
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);

  printf("\nResults\n");
  printf("The average value is %d\n", averageValue);
  printf("The minimum value is %d\n", minValue);
  printf("The maximum value is %d\n", maxValue);

  close(fd1[READ]);
  close(fd1[WRITE]);
  close(fd2[READ]);
  close(fd2[WRITE]);
  close(fd3[READ]);
  close(fd3[WRITE]);
}
