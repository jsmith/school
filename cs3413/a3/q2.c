#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "common.h"
#include "list.h"
#include "cv.h"

static bool debug = false;

typedef struct Car {
  char name[NAME_BUFFER_SIZE];
  char direction;
  int arrival;
  int duration;
  pthread_t* thread;
  struct Car* next;
} Car;

typedef struct CarQueue {
  Car* first;
} CarQueue;

void append(CarQueue* queue, Car* car) {
  if (queue->first == NULL) {
    queue->first = car;
    return;
  }

  Car* current = queue->first;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = car;
}

/**
 * Processes cars from stdin and adds them to the queue.
 * @param cars The cars.
 */
void processStdinQ2(CarQueue* cars) {
  if (debug) freopen("../input_q2_complex.txt", "r", stdin); // Only use for testing

  char inputLine[100];
  fgets(inputLine, sizeof(inputLine), stdin); // eat up the first line of the input
  while (fgets(inputLine, sizeof(inputLine), stdin) != NULL) {
    inputLine[strcspn(inputLine, "\n")] = '\0'; // remove the trailing newline
    StringArray* words = split(inputLine, '\t');
    if (words->used != 4) {
      printf("Parsed the incorrect # of words in the line: %d\n", words->used);
      exit(1);
    }

    Car* car = (Car*)malloc(sizeof(Car));
    car->next = NULL;
    // This is important since the name value could be temporary (and actually is in my implementation)=
    strcpy(car->name, words->array[0]);
    car->direction = words->array[1][0];
    car->arrival = str2int(words->array[2]);
    car->duration = str2int(words->array[3]);
    car->thread = NULL;

    append(cars, car);
    freeStringArray(words);
  }
}

static CV* waiting;
static CV* driving;
// How many drivers have finished
static int finishedCount = 0;
// How many drivers are driving
// This is important since a car going the opposite direction can only go after all of the cars
// have arrived
static int drivingCount = 0;
// The current direction. Initialized to NULL
static char currentDirection = '\0';
// The algorithm takes it one step at a time
// ie. we increment the current time by one each iteration
static int currentTime = 0;
// The time the last car left
// This is important since only a single car can leave at each iteration
static int lastLeftTime = -1;
// The time the car that just left is going to arrive
// Since cars *can't* pass we need this to determine when the current car will be arriving
static int lastArrivedTime = -1;
// The lock we use to ensure we don't encounter any race conditions
static sem_t* lock;

int max(int a, int b) {
  if (a > b) return a;
  else return b;
}

void* drive(void* arg) {
  Car* car = (Car*)arg;
  if (debug) printf("%s is waiting\n", car->name);
  while (1) {
    cv_wait(waiting);

    // We lock this section using a semaphore to ensure no weird issues occur
    sem_wait(lock);
    if (
        currentTime < car->arrival ||
        lastLeftTime == currentTime ||
        (drivingCount > 0 && currentDirection != car->direction)
    ) {
      sem_post(lock);
      continue;
    }

    if (debug) printf("%s has started at %d [%d]\n", car->name, currentTime, lastLeftTime);
    drivingCount++;
    lastLeftTime = currentTime;
    sem_post(lock);
    break;
  }

  // The logic to print out the direction only when we've changed directions
  if (currentDirection != car->direction) {
    currentDirection = car->direction;
    if (car->direction == 'N') {
      printf("Direction: North\n");
    } else {
      printf("Direction: South\n");
    }
  }

  // The arrive time at the other side of the bridge
  int arriveTime = lastArrivedTime = max(lastArrivedTime + 1, currentTime + car->duration);
  while (1) {
    cv_wait(driving);

    if (currentTime < arriveTime) {
      continue;
    }


    if (debug) printf("%s has ended at %d\n", car->name, currentTime);
    else printf("%s\n", car->name);
    sem_wait(lock);
    drivingCount--;
    finishedCount++;
    sem_post(lock);
    break;
  }

  return 0;
}

int main() {
  CarQueue cars = { .first = NULL };
  processStdinQ2(&cars);

  waiting = cv_init();
  driving = cv_init();

  if (cars.first == NULL) {
    printf("No input detected. PLEASE give me some cars!\n");
    return 1;
  }

  sem_unlink("/lock");
  lock = sem_open("/lock", O_CREAT, 0644, 1);

  Car* car = cars.first;
  int nCars = 0;
  while (car != NULL) {
    sem_unlink(car->name);
    car->thread = malloc(sizeof(pthread_t));
    pthread_create(car->thread, NULL, &drive, (void*)car);
    car = car->next;
    nCars++;
  }

  // Make sure all of the cars are waiting
  // Very important as we don't want to leave any cars out
  while (waiting->waiters != nCars);

  while (1) {
    int nDrivers = driving->waiters;
    if (debug) printf("[%s] Notifying %d drivers at %d!\n", __TIME__, nDrivers, currentTime);
    int nFinished = finishedCount;
    cv_notify_all(driving);
    while ((finishedCount - nFinished) + driving->waiters < nDrivers);

    nDrivers = driving->waiters;
    int nWaiters = waiting->waiters;
    if (debug) printf("[%s] Notifying %d waiters at %d!\n", __TIME__, nWaiters, currentTime);
    cv_notify_all(waiting);
    while ((driving->waiters - nDrivers) + waiting->waiters < nWaiters);

    if (waiting->waiters == 0 && driving->waiters == 0) break;
    currentTime++;
  }

  car = cars.first;
  while (car != NULL) {
    Car* nextCar = car->next;
    pthread_join(*(car->thread), NULL);
    free(car->thread);
    free(car);
    car = nextCar;
  }

  cv_close(waiting);
  cv_close(driving);
  sem_close(lock);
}
