#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define BUFFER_SIZE 10
#define M 1 // consumer
#define N 2 // producer

sem_t mutex;
int count = 0;
char buffer[BUFFER_SIZE];
char* upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


void* consume(void* _) {
  // printf("Consumer starting!\n");
  // Consumer
  while (true) {
    while (count == 0);
    sem_wait(&mutex);
    count--;
    char consumed = buffer[count];
    sem_post(&mutex);
    // printf("Got %c\n", consumed);
    printf("%c\n", consumed);
    sleep(M);
  }

  return 0;
}

int main() {
  sem_init(&mutex, 0, 1);

  pthread_t consumer;
  pthread_create(&consumer, NULL, &consume, NULL);

  // printf("Producer starting!\n");
  // Producer
  while (true) {
    while (count == BUFFER_SIZE);
    sem_wait(&mutex);
    buffer[count] = upper[count % 26];
    // printf("Put %c\n", buffer[count]);
    count++;
    sem_post(&mutex);
    sleep(N);
  }

  pthread_join(consumer, NULL);
}

#pragma GCC diagnostic pop