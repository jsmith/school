#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  int data;
  struct node *next;
} Node;

typedef struct Queue {
  Node *head;
  Node *tail;
} Queue;

Queue* InitBuf() {
  Queue* queue = (Queue *) malloc(sizeof(Queue));
  queue->head = NULL;
  queue->tail = NULL;
  return queue;
}

void AddBuf(Queue* queue, int value) {
  Node* node = (Node *) malloc(sizeof(Node));
  node->data = value;
  node->next = NULL;
  if (queue->tail == NULL) {
    queue->head = node;
  } else {
    queue->tail->next = node;
  }
  queue->tail = node;
}

void RemoveBuf(Queue* queue) {
  if (queue->head == NULL) {
    return;  
  }
  Node* head = queue->head;
  queue->head = queue->head->next;
  free(head);
}

int main() {
  // printf() displays the string inside quotation
  printf("Hello, World!");

  Queue* queue = InitBuf();
  AddBuf(queue, 5);
  printf("%i", queue->head->data);
  return 0;
}
