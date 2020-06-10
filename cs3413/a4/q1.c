#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "common.h"
#include "list.h"

#define DEBUG 0

typedef struct Allocation {
  int process;
  int start;
  int end;
  struct Allocation* next;
} Allocation;

typedef struct Memory {
  int size;
  Allocation* allocations;
} Memory;

/*
• First fit: Satisfy the request from the first available free memory block that is
large enough to accommodate the request.
• Best fit: Satisfy the request from the free memory block that is large enough to
service the request and small enough that it has the smallest fragmented block.
• Worst fit: Satisfy the request from the free memory block that is large enough to
service the request and creates the largest fragmented block.
 */
typedef enum Algorithm { FirstFit, BestFit, WorstFit } Algorithm;

int get_start(Allocation* allocation) {
  if (allocation == NULL) return 0;
  else return allocation->end;
}

int get_end(Allocation* allocation, int total_size) {
  if (allocation == NULL) return total_size;
  else return allocation->start;
}

void print_allocations(Allocation* allocation) {
  printf("[");
  while (allocation != NULL) {
    printf("%d -> %d", allocation->start, allocation->end);
    if (allocation->next != NULL) {
      printf(", ");
    }

    allocation = allocation->next;
  }
  printf("]\n");
}

/**
 *
 * @param memory The memory object.
 * @param algorithm The algorithm we are using.
 * @param requested_size The requested size.
 * @parram process The process that requested that memory.
 * @return 1 if we failed to satisfy the request else 0.
 */
int satisfy_request(Memory* memory, Algorithm algorithm, int requested_size, int process) {
  // print_allocations(memory->allocations);
  Allocation* saved_previous = NULL;
  int saved_block_size = -1;
  Allocation* previous = NULL;
  Allocation* current = memory->allocations;
  while (1) {
    int end = get_end(current, memory->size);
    int start = get_start(previous);
    int fragment_size = end - start;
    if (requested_size <= fragment_size) {
      // If -1 that means that we haven't saved anything yet
      if (saved_block_size == -1) {
        if (DEBUG) printf("Found an initial memory section: %d -> %d\n", start, end);
        saved_previous = previous;
        saved_block_size = fragment_size;
      }

      // Ok so now we know it fits, lets check our algorithm
      if (algorithm == FirstFit) {
        break;
      } else if (algorithm == BestFit) {
        // If best fit, check if the new section is smaller than the old section
        if (fragment_size < saved_block_size) {
          if (DEBUG) printf("Found a better memory section: %d -> %d\n", start, end);
          saved_previous = previous;
          saved_block_size = fragment_size;
        }
      } else if (algorithm == WorstFit) {
        // If worst fit, check if the new section is bigger than the old section
        if (fragment_size > saved_block_size) {
          if (DEBUG) printf("Found a worse memory section: %d -> %d\n", start, end);
          saved_previous = previous;
          saved_block_size = fragment_size;
        }
      } else {
        printf("Unknown algorithm: %d", algorithm);
        exit(1);
      }
    }

    if (current == NULL) {
      break;
    }

    previous = current;
    current = current->next;
  }

  // If this is still -1 that means we haven't found a block big enough to allocate the given
  // memory
  if (saved_block_size == -1) {
    return 1;
  }

  Allocation* allocation = malloc(sizeof(Allocation));
  allocation->next = NULL;
  allocation->process = process;

  allocation->start = get_start(saved_previous);
  allocation->end = allocation->start + requested_size;
  if (DEBUG) printf("Allocated memory block %d -> %d\n", allocation->start, allocation->end);

  if (saved_previous == NULL) {
    allocation->next = memory->allocations;
    memory->allocations = allocation;
  } else {
    allocation->next = saved_previous->next;
    saved_previous->next = allocation;
  }

  return 0;
}

/**
 * Find and remove the memory allocation using the process ID.
 * @param memory The memory struct.
 * @param process The process ID.
 * @return NULL if the memory allocation was not found else the memory allocation.
 */
Allocation* terminate_process(Memory* memory, int process) {
  Allocation* previous = NULL;
  Allocation* current = memory->allocations;

  while (current != NULL) {
    if (current->process != process) {
      previous = current;
      current = current->next;
      continue;
    }

    if (DEBUG) printf("Freed memory block %d -> %d\n", current->start, current->end);
    if (previous == NULL) {
      memory->allocations = current->next;
    } else {
      previous->next = current->next;
    }

    current->next = NULL;
    return current;
  }

  return NULL;
}

void free_allocations(Allocation* allocation) {
  if (allocation == NULL) {
    return;
  }

  free_allocations(allocation->next);
  allocation->next = NULL;
  free(allocation);
}

/*
What are the “Final smallest and largest fragmented memory sizes”
Fragments refer to the unallocated left over memory. So, it is the smallest and largest holes (i.e. free blocks) respectively.
*/

int main(int argc, char** argv) {
  // if (DEBUG) freopen("../input_q1_best_worst.txt", "r", stdin); // Only use for testing

  int f_flag = 0;
  int b_flag = 0;
  int w_flag = 0;
  char *s_value = NULL;
  int c;


  while ((c = getopt (argc, argv, "fbws:")) != -1)
    switch (c) {
      case 's':
        s_value = optarg;
        break;
      case 'f':
        f_flag = 1;
        break;
      case 'b':
        b_flag = 1;
        break;
      case 'w':
        w_flag = 1;
        break;
      case '?':
        if (optopt == 'c') printf("Option -%c requires an argument.\n", optopt);
        else printf("Unknown option `-%c'.\n", optopt);
        return 1;
      default:
        printf("Unknown getopt char: %c\n", c);
        return 1;
  }

  if (f_flag + b_flag + w_flag > 1) {
    printf("Please select only one algorithm!\n");
    return 1;
  }

  Algorithm algorithm;
  if (f_flag) {
    algorithm = FirstFit;
  } else if (b_flag) {
    algorithm = BestFit;
  } else if (w_flag) {
    algorithm = WorstFit;
  } else {
    printf("Please select one algorithm!\n");
    return 1;
  }

  if (s_value == NULL) {
    printf("Please provide total amount of memory using -s SIZE\n");
    return 1;
  }

  int size = str2int(s_value);
  int total_processes_created = 0;
  int total_allocated_memory = 0;
  int total_processes_terminated = 0;
  int total_freed_memory = 0;

  char *line = NULL;
  size_t line_size;
  Memory memory = { .size = size, .allocations = NULL };
  while (getline(&line, &line_size, stdin) != -1) {
    removeNewline(line); // remove the trailing newline
    if (*line == 'N') {
      // e.g. N1 500
      StringArray* arr = split(line, ' ');
      if (arr->used != 2) {
        printf("Expected 2 words, got %d: %s\n", arr->used, line);
        return 1;
      }

      if (strlen(arr->array[0]) == 1) {
        printf("You must specify a process number after N: \"%s\"\n", line);
        return 1;
      }

      int process = str2int(arr->array[0] + 1); // + 1 to ignore 'N'
      int requested_memory = str2int(arr->array[1]);
      if (DEBUG) printf("echo N%d %d\n", process, requested_memory);
      freeStringArray(arr);
      if (satisfy_request(&memory, algorithm, requested_memory, process) == 1) {
        printf("Process %d failed to allocate %d memory\n", process, requested_memory);
      } else {
        total_processes_created++;
        total_allocated_memory += requested_memory;
      }

    } else if (*line == 'T') {
      if (strlen(line) == 1) {
        printf("You must specify a process number after T\n");
        return 1;
      }

      int process = str2int(line + 1); // + 1 to ignore 'T'
      if (DEBUG) printf("echo T%d\n", process);
      Allocation* allocation = terminate_process(&memory, process);
      if (allocation == NULL) {
        printf("Process %d failed to free memory\n", process);
      } else {
        total_processes_terminated++;
        total_freed_memory += allocation->end - allocation->start;
        free(allocation);
      }

    } else if (*line == 'S') {
      if (DEBUG) printf("echo S\n");
      break;
    } else {
      printf("Unknown command: %c\n", *line);
      return 1;
    }
  }

  int final_memory_available = 0;
  int largest_memory_fragment = -1;
  int smallest_memory_fragment = memory.size;
  int start = 0;
  Allocation* current = memory.allocations;
  while (1) {
    int end = get_end(current, size);

    int fragment_size = end - start;
    final_memory_available += fragment_size;
    if (
        (smallest_memory_fragment == -1 || fragment_size < smallest_memory_fragment) &&
        fragment_size != 0
    ) {
      smallest_memory_fragment = fragment_size;
    }

    if (
        (largest_memory_fragment == -1 || fragment_size > largest_memory_fragment) &&
        fragment_size != 0
    ) {
      largest_memory_fragment = fragment_size;
    }

    if (current == NULL) {
      break;
    }

    start = current->end;
    current = current->next;
  }

  printf("Total Processes created %d, Total allocated memory %d, Total Processes\n", total_processes_created, total_allocated_memory);
  printf("terminated %d, Total freed memory %d, Final memory available %d, Final\n", total_processes_terminated, total_freed_memory, final_memory_available);
  printf("smallest and largest fragmented memory sizes are %d and %d respectively\n", smallest_memory_fragment, largest_memory_fragment);
}
