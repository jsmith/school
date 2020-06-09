#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <stdbool.h>

#define PAGE_SIZE 4096 // 2^12
#define PAGE_TABLE_SIZE 1048576 // 2^20
#define DEBUG 1

/*
1) For a4 q2, are the logical addresses given in binary or in decimal (and do we print the physical
addresses in binary or decimal)?

The address is given as an unsigned int (decimal) and you should print your output as an unsigned
int (decimal). I have posted a sample file to the assignment that contains addresses from 0 - 2^32.
I would *remind* students that computers represent data as binary internally regardless of how
*you* view it. So, if you read an int, then internally this is stored as a binary number. So, you
can immediately perform the actions on that number you want as if it were a binary number (using
bit shifting or masking) or a decimal number (using multiplication, division or modulo). When you
print the number then again it is stored internally as binary but you can print it as a decimal.
This means you do not need to worry about converting from decimal to binary and back :)
*/

/*
For this question you are to use the Least Recently Used (LRU) page replacement
policy. Since you do NOT have to worry about writing to the page you DO NOT
need to save the page when you replace it!
 */

typedef struct Page {
  struct Frame* frame;
  bool valid;
} Page;

Page PAGE_TABLE[PAGE_TABLE_SIZE];

typedef struct Frame {
  int frame_number;
  int page_number;
  struct Frame* next;
  struct Frame* previous;
} Frame;

typedef struct FrameStack {
  Frame* top; // most recently used
  Frame* bottom; // least recently used
  int size;
  int frame_limit;
} FrameStack;

Frame* create_frame(int frame_number) {
  Frame* frame = malloc(sizeof(Frame));
  frame->frame_number = frame_number;
  frame->page_number = -1; // We set this after creation
  frame->next = NULL;
  frame->previous = NULL;
  return frame;
}

Frame* push(FrameStack* stack, Frame* frame) {
  if (stack->top == NULL) {
    stack->top = frame;
    stack->bottom = frame;
  } else {
    frame->next = stack->top;
    frame->next->previous = frame;
    stack->top = frame;
  }
  stack->size++;
  return frame;
}

void extract(FrameStack* stack, Frame* frame) {
  if (frame->previous == NULL) {
    stack->top = frame->next;
  } else {
    frame->previous->next = frame->next;
  }

  if (frame->next == NULL) {
    stack->bottom = frame->previous;
  } else {
    frame->next->previous = frame->previous;
  }

  stack->size--;
}

void print_stack(FrameStack* stack) {
  printf("[");
  Frame* current = stack->top;
  while (current != NULL) {
    printf("%d", current->frame_number);

    if (current->next) {
      printf(", ");
    }

    current = current->next;
  }
  printf("]\n");
}

unsigned int get_physical_address(Page* page_table, FrameStack* stack, unsigned int logical_address, int* page_faults) {
  int page_offset = (int)(logical_address % PAGE_SIZE);
  int page_number = (int)(logical_address / PAGE_SIZE);
  if (DEBUG) printf("Logical address %u -> (%d, %d)\n", logical_address, page_number, page_offset);


  Frame* frame;
  if (page_table[page_number].valid) {
    // Yay!! A hit!
    frame = page_table[page_number].frame;
    if (DEBUG) printf("Hit! Page %d is in frame %d!\n", page_number, frame->frame_number);
    extract(stack, frame); // extract it from wherever it is in the stack
  } else {
    // Miss :(

    // Increment the page fault count
    (*page_faults)++;

    if (stack->size < stack->frame_limit) {
      // We still have space left in the physical address space without having to swap out a page
      frame = create_frame(stack->size);
      if (DEBUG) printf("Miss! Placing %d is in newly created frame %d!\n", page_number, frame->frame_number);
    } else {
      // No room left. We need to swap out a page first.
      // Extract the frame to use from this bottom!
      // This is the least recently used frame :)
      frame = stack->bottom;
      if (DEBUG) printf("Miss! Frame %d is the LRU! Swapping out page %d and swapping in %d!\n", frame->frame_number, frame->page_number, page_number);
      extract(stack, frame); // remove the frame from the bottom of the stack
      page_table[frame->page_number].valid = false;
    }

    frame->page_number = page_number;
    page_table[page_number].valid = true;
    page_table[page_number].frame = frame;
  }

  push(stack, frame); // Put the frame it back on top as it's the MRUs
  if (DEBUG) printf("Stack -> ");
  if (DEBUG) print_stack(stack);
  return (page_table[page_number].frame->frame_number * PAGE_SIZE) + page_offset;
}

void free_frames(Frame* frame) {
  if (frame == NULL) {
    return;
  }

  free_frames(frame->next);
  frame->next = NULL;
  frame->previous = NULL;
  free(frame);
}

int main(int argc, char** argv) {
  // if (DEBUG) freopen("../input_q2_simple.txt", "r", stdin); // Only use for testing

  if (argc != 2) {
    printf("Expected a single argument to specify the # of frames!\n");
    return 1;
  }


  int n = str2int(argv[1]);

  for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
    PAGE_TABLE[i].valid = false;
    PAGE_TABLE[i].frame = NULL;
  }

  FrameStack stack = { .size = 0, .top = NULL, .bottom = NULL, .frame_limit = n };
  int page_faults = 0;
  char *line = NULL;
  size_t line_size;
  while (getline(&line, &line_size, stdin) != -1) {
    char *ptr;
    unsigned int logical_address = strtoul(line, &ptr, 10);
    unsigned int physical_address = get_physical_address(PAGE_TABLE, &stack, logical_address, &page_faults);
    printf("%u -> %u\n", logical_address, physical_address);
  }

  printf("\nSummary\n");
  printf("Page Faults: %d\n", page_faults);

  free_frames(stack.top);
}
