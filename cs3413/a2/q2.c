#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-msc30-c"
//
// Created by Jacob Smith on 2020-05-16.
// CS 3413
// Assignment 2
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "common.h"
#define TICKET_SELLERS 10

typedef struct {
  int* array;
  int used;
  int size;
} IntArray;

typedef struct Seller {
  pthread_t* thread;
  int tickets_sold;
  int seller_id;
  struct Seller* next;
} Seller;

static IntArray* TICKETS = NULL;
static int NUM_DAYS = -1;
static int NUM_TICKETS = -1;
// Used to quickly check if there are still any tickets to sell
// Once this is zero ticket sellers can stop selling
static int NUM_TICKETS_REMAINING = -1;
// global value to get next customer ID
static int CUSTOMER_ID = 1;
// lock to make sure there are no race conditions when accessing + mutating CUSTOMER_ID
static pthread_mutex_t CUSTOMER_ID_MUTEX = PTHREAD_MUTEX_INITIALIZER;
// lock to ensure that there are no race conditions when accessing + mutating NUM_TICKETS_REMAINING and TICKETS
static pthread_mutex_t TICKETS_MUTEX = PTHREAD_MUTEX_INITIALIZER;

IntArray* init_int_array(int initialSize) {
  IntArray *a = malloc(sizeof *a);
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
  return a;
}

void append_int_array(IntArray *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int*)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void free_int_array(IntArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

/* Function to decide the number of tickets a customer wants from 1 to 10 */
int how_many_tickets() {
  return rand() % 10 + 1;
}

/* Function to decide the day of tickets a customer wants from 1 to days */
int what_day_tickets(int days) {
  return rand() % days + 1;
}

/* Function to sleep for a random interval from 1 to 10 seconds */
void wait_for_customer() {
  sleep(rand() % 10 + 1);
}

void* sell_tickets(void* arg) {
  if (NUM_TICKETS == -1 || NUM_DAYS == -1 || NUM_TICKETS_REMAINING == -1 || TICKETS == NULL) {
    printf("Please initialize globals!!");
    return 0;
  }

  // The arg *must* be a seller pointer
  // We need to access the "seller_id" and update the # of tickets sold
  Seller* seller = (Seller*) arg;
  while (1) {
    // Check before and after sleeping
    if (NUM_TICKETS_REMAINING == 0) {
      break;
    }

    wait_for_customer();

    // Check before and after sleeping
    if (NUM_TICKETS_REMAINING == 0) {
      break;
    }

    pthread_mutex_lock(&CUSTOMER_ID_MUTEX);
    int customer_id = CUSTOMER_ID++;
    pthread_mutex_unlock(&CUSTOMER_ID_MUTEX);
    int day = what_day_tickets(NUM_DAYS);
    int dayIndex = day - 1;
    int tickets_to_buy = how_many_tickets();
    pthread_mutex_lock(&TICKETS_MUTEX);
    int remaining_tickets = TICKETS->array[dayIndex] - tickets_to_buy;
    if (remaining_tickets >= 0) {
      TICKETS->array[dayIndex] = remaining_tickets;
      NUM_TICKETS_REMAINING -= tickets_to_buy;
    }
    pthread_mutex_unlock(&TICKETS_MUTEX);

    if (remaining_tickets >= 0) {
      seller->tickets_sold += tickets_to_buy;
      printf("Customer %d is sold %d tickets by Seller %d\n", customer_id, tickets_to_buy, seller->seller_id);
    } else {
      printf("Customer %d is not going to the festival!\n", customer_id);
    }

  }

  return 0;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("Invalid number of arguments. Expected 2 arguments.");
    return 1;
  }

  NUM_DAYS = str2int(argv[1]);
  NUM_TICKETS = str2int(argv[2]);
  NUM_TICKETS_REMAINING = NUM_DAYS * NUM_TICKETS;

  TICKETS = init_int_array(NUM_DAYS);
  for (int i = 0; i < NUM_DAYS; i++) {
    append_int_array(TICKETS, NUM_TICKETS);
  }

  Seller* sellers = NULL;
  Seller* previous = NULL;
  for (int i = 0; i < TICKET_SELLERS; i++) {
    Seller* seller = malloc(sizeof(Seller));
    seller->seller_id = i + 1;
    seller->tickets_sold = 0;
    seller->next = NULL;
    seller->thread = malloc(sizeof(pthread_t));
    pthread_create(seller->thread, NULL, sell_tickets, (void*)seller);

    if (previous == NULL) {
      sellers = seller;
    } else {
      previous->next = seller;
    }

    previous = seller;
  }

  int max = -1;
  int max_seller_id = -1;
  Seller* next = sellers;
  while (next != NULL) {
    Seller* seller = next;
    next = seller->next;

    pthread_join(*(seller->thread), NULL);
    if (seller->tickets_sold > max) {
      max = seller->tickets_sold;
      max_seller_id = seller->seller_id;
    }

    free(seller->thread);
    free(seller);
  }

  if (max <= 0) {
    printf("No tickets sold! Check your inputs :)\n");
  } else {
    printf("Top seller is %d having sold %d tickets in total.\n", max_seller_id, max);
  }

  free_int_array(TICKETS);
  pthread_mutex_destroy(&CUSTOMER_ID_MUTEX);
  pthread_mutex_destroy(&TICKETS_MUTEX);
}

#pragma clang diagnostic pop