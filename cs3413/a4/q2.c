#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <stdbool.h>

// TODO question doesn't make sense. Why is it saying to use a 2^20 page table??

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

#define PAGE_SIZE 4096 // 2^12
#define PAGE_TABLE 1048576 // 2^20

typedef struct Page {
  struct Frame* frame;
  bool valid;
} Page;

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
  int frames;
} FrameStack;

Frame* create_frame(int page_number, int frame_number) {
  Frame* frame = malloc(sizeof(Frame));
  frame->frame_number = frame_number;
  frame->page_number = page_number;
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
    stack->top = frame;
  }
  stack->size++;
  return frame;
}

Frame* extract(FrameStack* stack, Frame* frame) {
  if (frame->previous == NULL) {
    stack->top = frame->next;
  } else {
    frame->previous = frame->next;
  }

  if (frame->next == NULL) {
    stack->bottom = frame->previous;
  } else {
    frame->next->previous = frame->previous;
  }

  stack->size--;

  return frame;
}

int get_physical_address(Page* page_table, FrameStack* stack, unsigned int logical_address, int* page_faults) {
  int page_offset = (int)logical_address % PAGE_SIZE;
  int page_number = (int)logical_address / PAGE_SIZE;


  if (page_table[page_number].valid) {
    Frame* frame = page_table[page_number].frame;




    // Yay!! A hit!
    return (page_table[page_number].frame->frame_number * PAGE_SIZE) + page_offset;
  }

  // Miss :(
  // Increment the page fault count
  (*page_faults)++;

  Frame* frame;
  if (stack->size < stack->frames) {
    frame =
    // We still have space left in the physical address space without having to swap out a page
    frame = push(stack, page_number);
  } else {
    // No room left. We need to swap out a page first.

  }

  page_table[page_number].valid = true;
  page_table[page_number].frame = frame;

  return 0;
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
  if (argc != 2) {
    printf("Expected a single argument to specify the # of frames!\n");
  }

  int n = str2int(argv[1]);

  Page page_table[PAGE_TABLE];
  for (int i = 0; i < PAGE_TABLE; i++) {
    page_table[i].valid = false;
    page_table[i].frame = NULL;
  }

  FrameStack stack = { .size = 0, .top = NULL, .bottom = NULL, .frames = n };
  int page_faults = 0;
  char *line = NULL;
  size_t line_size;
  while (getline(&line, &line_size, stdin) != -1) {
    char *ptr;
    unsigned int logical_address = strtoul(line, &ptr, 10);
    int page_offset = (int)logical_address % PAGE_SIZE;

    printf("%d -> %d", logical_address, logical_address);
    // printf logical address -> physical address
  }

  printf("\nSummary\n");
  printf("Page Faults: %d", page_faults);

  free_frames(stack.top);
}
