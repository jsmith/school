// gcc -std=c99 -lpthread -g main.c
// scp jsmith21@fcslinux.cs.unb.ca:/home1/ugrads/jsmith21/cs3413/l1/main.c main.cs
#include <pthread.h>
#include <stdio.h>
#define MAX 100

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int COUNT = 0;

void* increment(void* _) {
  for (int i = 0; i < MAX; i++) {
    pthread_mutex_lock(&mutex);
    COUNT++;
    pthread_mutex_unlock(&mutex);
  }
}

void* decrement(void* _) {
  for (int i = 0; i < MAX; i++) {
    pthread_mutex_lock(&mutex);
    COUNT--;
    pthread_mutex_unlock(&mutex);
  }
}

int main() {
  pthread_t incrementer;
  pthread_t decrementer;
  pthread_create(&incrementer, NULL, &increment, NULL);
  pthread_create(&decrementer, NULL, &decrement, NULL);
  pthread_join(incrementer, NULL);
  pthread_join(decrementer, NULL);
  pthread_mutex_destroy(&mutex);
  printf("The final count is %d\n", COUNT);
}

