#include <pthread.h>
#include <stdio.h>
#include <stdio.h>

static pthread_mutex_t M_1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t M_2 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t M_3 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t DONE = PTHREAD_MUTEX_INITIALIZER;
static queue_t* Q_1 = NULL:
static queue_t* Q_2 = NULL:
static queue_t* Q_3 = NULL:

void* lower() {
  while (1) {
    // Busy wait since we can't use semphores
    // I'm assuming I can use is_empty not in my critical sections
    // If this is actually an error, the solution would be to make sure all my is_empty checks
    // are using their associated mutexes
    if (is_empty(Q_1)) continue;
    pthread_mutex_lock(M_1);
    char c = dequeue(Q_1);
    pthread_mutex_unlock(M_1);
    if (c < 97 && c != '\n') c = c + 32;
    pthread_mutex_lock(M_2);
    enqueue(Q_2, c);
    pthread_mutex_unlock(M_2);
    // Use the newline to determine whether this thread is done its work
    if (c == '\n') break;
  }
}

void* add() {
  while (!done) {
    if (is_empty(Q_2)) continue;
    pthread_mutex_lock(M_2)
    char c = dequeue(Q_2);
    pthread_mutex_unlock(M_2);
    if (c != '\n') c = c + 5;
    pthread_mutex_lock(M_3);
    enqueue(Q_3, c);
    pthread_mutex_unlock(M_3);
    if (c == '\n') break;
  }
}

void* bounds_check() {
  while (1) {
    if (is_empty(Q_2)) continue;
    pthread_mutex_lock(M_2)
    char c = dequeue(Q_2);
    pthread_mutex_unlock(M_2);
    if (c > 122 && c != '\n') c = c – 26;
    printf("%c", c); // finally print
    if (c == '\n') break;
  }

  // Signal that we are done!
  pthread_mutex_unlock(&DONE);
}

int main() {
  Q_1 = init_queue();
  Q_2 = init_queue();
  Q_3 = init_queue();

  // Lock this initally.
  pthread_mutex_lock(&DONE);

  pthread_t t1;
  pthread_t t2;
  pthread_t t3;
  pthread_create(&t1, NULL, &lower, NULL);
  pthread_create(&t2, NULL, &add, NULL);
  pthread_create(&t3, NULL, &bounds_check, NULL);

  char c;
  while (1) {
    scanf("%c", &c);

    // newline means we are done_input! yay!
    if (c == '\n') {
      break;
    }

    pthread_mutex_lock(&M_1);
    enqueue(Q_1, c);
    pthread_mutex_unlock(&M_1);
  }

  // Now wait for the last thread to signal
  pthread_mutex_lock(&DONE);

  // Cleanup time!
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);

  pthread_mutex_destroy(&M_1);
  pthread_mutex_destroy(&M_2);
  pthread_mutex_destroy(&M_3);
}