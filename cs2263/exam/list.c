#include <stdlib.h>
#include "list.h"

Node *constructLinkedList(int *vals, int n) {
    if (n <= 0) {
        return NULL;
    }

    Node *head = constructNode(vals[0]), *curr = head;
    head->val = vals[0];

    for (int i = 1; i < n; i++) {
        Node *next = constructNode(vals[i]);
        curr->next = next;
        curr = next;
    }

    return head;
}

void destructLinkedList(Node *node) {
    if (node == NULL) {
        return;
    }

    destructLinkedList(node->next);
    destructNode(node);
}

Node *constructNode(int val) {
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->val = val;
    return node;
}

void destructNode(Node *node) {
    free(node);
}

void join(Node *one, Node *two) {
    while (one->next != NULL) {
        one = one->next;
    }

    one->next = two;
}

Node *reverse(Node *list) {
    if (list == NULL) {
        return NULL;
    }

    Node *head;
    if (list->next == NULL) {
        head = list;
    } else {
        head = reverse(list->next);
        list->next->next = list;
        list->next = NULL;
    }

    return head;
}

Node *delete(Node *head, int index) {
    int i = 0;
    Node *prev = NULL, *curr = head;
    while (curr->next != NULL) {
        if (i == index) {
            if (prev == NULL) {
                head = curr->next;
                free(curr);
            } else {
                prev->next = curr->next;
                free(curr);
            }
            break;
        }

        prev = curr; curr = curr->next;
        i++;
    }

    return head;
}

Node *pushNode(Node *head, int val) {
    Node *curr = head, *node = constructNode(val);


    if (head == NULL) {
        return node;
    }

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = node;

    return head;
}

int equalLinkedList(Node *head, int *expected) {
    int i = 0;
    while (head != NULL) {
        if (head->val != expected[i]) {
            return 0;
        }
        head = head->next;
        i++;
    }

    return 1;
}


List *constructList(int *vals, int n) {
    List *l = malloc(sizeof(List));
    l->list = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        l->list[i] = vals[i];
    }
    l->length = n;
    return l;
}

void destructList(List *l) {
    free(l->list);
    free(l);
}

int searchHelper(List *l, int val, int s, int e) {
    if (s > e) {
        return -1;
    }

    int c = (s + e) / 2;
    if (l->list[c] == val) {
        return c;
    } else if (l->list[c] < val) {
        return searchHelper(l, val, c + 1, e);
    } else {
        return searchHelper(l, val, s, c - 1);
    }
}

int search(List *l, int val) {
    return searchHelper(l, val, 0, l->length - 1);
}

void sortHelper(List *l, int lo, int hi) {
    if (lo > hi) {
        return;
    }

    int pivot = l->list[lo];
    int pi = lo;
    for (int i = lo + 1; i <= hi; i++) {
        if (l->list[i] < pivot) {
            l->list[pi] = l->list[i];
            l->list[i] = l->list[pi + 1];
            pi++;
        }
    }
    l->list[pi] = pivot;

    sortHelper(l, lo, pi - 1);
    sortHelper(l, pi + 1, hi);
}

void sort(List *l) {
    sortHelper(l, 0, l->length - 1);
}

void push(List *l, int val) {
    int *list = malloc(sizeof(int) * l->length + 1);
    for (int i = 0; i < l->length; i++) {
        list[i] = l->list[i];
    }
    list[l->length] = val;
    free(l->list);
    l->list = list;
    l->length++;
}

int pop(List *l) {
    int *list = malloc(sizeof(int) * l->length - 1);
    for (int i = 0; i < l->length - 1; i++) {
        list[i] = l->list[i];
    }
    int val = l->list[l->length - 1];
    free(l->list);
    l->list = list;
    l->length--;
    return val;
}
