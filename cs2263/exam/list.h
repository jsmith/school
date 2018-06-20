#ifndef LINKED_H
#define LINKED_H


typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    int *list;
    int length;
} List;

Node *constructNode(int val);
void destructNode(Node *node);
Node *constructLinkedList(int *vals, int n);
void destructLinkedList(Node *node);
void join(Node *one, Node *two);
Node *reverse(Node *list);
Node *delete(Node *head, int index);
Node *pushNode(Node *head, int val);
int equalLinkedList(Node *head, int* expected);

List *constructList(int *vals, int n);
void destructList(List *l);
int search(List *l, int val);
void sort(List *l);
void push(List *l, int val);
int pop(List *l);

#endif