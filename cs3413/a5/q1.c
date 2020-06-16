#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SECTORS 100000

int DEBUG = 0;

// TODO requests arrive in-order, correct?
// TODO generate input file using Python

typedef struct Request {
  unsigned int time;
  unsigned int sector;
  struct Request* next;
} Request;

typedef struct IOQueue {
  Request* head;
  Request* tail;
} IOQueue;

/**
 * Removes the next request from the queue. If the algorithm is SSTF we find the closest request otherwise we just
 * remove the first request.
 *
 * @param queue The queue.
 * @param algorithm 'T', 'C', or 'F'
 * @return The removed request.
 */
Request* process(IOQueue* queue, char algorithm, unsigned int head) {
  Request* to_remove = NULL;
  Request* to_remove_previous = NULL;

  if (algorithm == 'T') {
    Request* previous = NULL;
    Request* current = queue->head;
    unsigned int min = -1;
    while (current != NULL) {

      unsigned int distance;
      if (current->sector > head) {
        distance = current->sector - head;
      } else {
        distance = head - current->sector;
      }

      // Find the request that is the closest to the head.
      if (distance < min || min == -1) {
        to_remove = current;
        to_remove_previous = previous;
        min = distance;
      }

      previous = current;
      current = current->next;
    }
  } else {
    to_remove = queue->head;
  }

  if (to_remove == NULL) {
    printf("to_remove is NULL. This shouldn't happen...\n");
    exit(1);
  }

  if (to_remove_previous == NULL) {
    queue->head = to_remove->next;
  } else {
    to_remove_previous->next = to_remove->next;
  }

  if (queue->tail == to_remove) {
    queue->tail = to_remove_previous;
  }

  to_remove->next = NULL;

  return to_remove;
}

/**
 * Insert into the queue using the specified algorithm.
 *
 * @param queue The IO queue.
 * @param request The IO request.
 * @param algorithm 'T', 'C', or 'F'
 */
void insert(IOQueue* queue, Request* request, char algorithm, unsigned int head) {
  Request* previous = NULL;
  if (algorithm == 'F' || algorithm == 'T') {
    // Insert at the end for these algorithms
    previous = queue->tail;
  } else {
    Request* current = queue->head;
    // This can_insert value is to ensure that we go in a circle
    // Imaging a queue that looks like this: [5, 6, 8, 1, 3], a head of 4 and a new request seeking position 2.
    // Initially, we can't insert since the head is 4 and we are seeking 2 (ie. can_insert is false) but once we reach
    // the value 1 can_insert is now true. Once we reach the value 3 we break and insert the new request.
    int can_insert = request->sector >= head;
    while (current != NULL) {
      if (!can_insert) {
        // We can only *after* we've reached a sector that is less than the current head position
        can_insert = current->sector < head;
      }

      if (can_insert) {
        // Break if we found a sector greater than the requested sector. For example, if we are inserting the value
        // 2 and reach the value 3.
        // OR if the values suddenly switch to being less than the head value
        // In our example above, if we are trying to insert the value 9 and we reach the value 1 we would break
        if (
            current->sector > request->sector ||
            (current->sector < head && request->sector > head)
         ) break;
      }

      previous = current;
      current = current->next;
    }
  }

  if (previous == NULL) {
    request->next = queue->head;
    queue->head = request;
  } else {
    request->next = previous->next;
    previous->next = request;
  }

  if (request->next == NULL) {
    queue->tail = request;
  }
}

int main(int argc, char** argv) {
  // freopen("../input_q1_simple.txt", "r", stdin); // Only use for testing

  if (argc != 4) {
    printf("Expected a 3 arguments! Please try again!\n");
    return 1;
  }

  char algorithm;
  if (strcmp(argv[1], "T") == 0) {
    algorithm = 'T';
  } else if (strcmp(argv[1], "F") == 0) {
    algorithm = 'F';
  } else if (strcmp(argv[1], "C") == 0) {
    algorithm = 'C';
  } else {
    printf("Please select a valid algorithm: %s", argv[1]);
    return 1;
  }

  char* s = NULL;
  unsigned int head = (unsigned int)strtol(argv[2], &s, 10);

  char direction;
  if (strcmp(argv[3], "a") == 0) {
    direction = 'a';
  } else if (strcmp(argv[3], "d") == 0) {
    direction = 'd';
  } else {
    printf("Please select a valid order: %s", argv[3]);
    return 1;
  }

  char *line = NULL;
  size_t line_size;
  IOQueue incoming = { .head = NULL };
  char *ptr;
  while (getline(&line, &line_size, stdin) != -1) {
    Request* request = malloc(sizeof(Request));
    request->next = NULL;
    request->sector = strtoul(line, &ptr, 10);
    if (request->sector >= SECTORS) {
      printf("The request with the following sector is outside the bounds: %d", request->sector);
      free(request);
      continue;
    }

    request->time = strtoul(ptr, &ptr, 10);
    insert(&incoming, request, 'F', 0); // append to the end of the queue
  }

  unsigned long total_movement = 0;
  unsigned long time = 0;
  IOQueue waiting = { .head = NULL };
  while (incoming.head != NULL || waiting.head != NULL) {
    // Check of processes that have arrived
    while (incoming.head != NULL && incoming.head->time <= time) {
      Request* request = process(&incoming, 'F', 0);
      insert(&waiting, request, algorithm, head);
    }

    // Check if there is actually any requests waiting at this moment
    if (waiting.head == NULL) {
      time += 1;
      continue;
    }

    Request* request = process(&waiting, algorithm, head);
    unsigned int distance;
    char new_direction;
    if (request->sector > head) {
      distance = request->sector - head;
      new_direction = 'a';
    } else {
      distance = head - request->sector;
      new_direction = 'd';
    }

    unsigned int saved_head = head;
    head = request->sector;
    free(request);

    int reverse_direction = direction != new_direction;
    unsigned int access_time = (distance / 15) + (reverse_direction ? 3 : 0);
    if (DEBUG) printf("Processing request #%d from #%d at %lus (dur -> %d, dis -> %d, rev -> %d)\n", request->sector, saved_head, time, access_time, distance, reverse_direction);

    direction = new_direction;
    // printf("Moving -> %d, Time -> %d\n", distance, access_time);
    total_movement += distance;
    time += access_time;
  }

  printf("Summary\n");
  printf("Total head movement -> %lu\n", total_movement);
  printf("Total time -> %lu\n", time);
}
