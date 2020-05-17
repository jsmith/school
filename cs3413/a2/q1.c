//
// Created by Jacob Smith on 2020-05-16.
// CS 3413
// Assignment 2
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "common.h"
#define MAX_LINE_LENGTH 1000
#define MAX_CIPHERS 1000
#define CHAR_MIN 32
#define CHAR_MAX 126
#define WRITE 1
#define READ 0

// the file descriptors
static int SIZE = -1; // this is super important since when were manipulating strings we might create the \0 char
static int* FD = NULL;
const static char NUM_CHARS = CHAR_MAX - CHAR_MIN + 1; // Add 1 since bounds are inclusive

typedef struct Cipher {
  int cipher_id; // incrementing ID starting at 0
  char value;
  pthread_t* thread;
  struct Cipher* next;
} Cipher;

// Since the c mod operator actually implements remainder
// I created this function from a source online
int mod(int a, int b) {
  int result = a % b;
  if (result < 0) {
    result += b;
  }

  return result;
}

int get_size(const char* s) {
  int size = 0;
  for (; s[size] != '\0'; size++);
  return size;
}

int read_pipe(int* fd, char* s, int length) {
  return read(fd[READ], s, length);
}

int write_pipe(int* fd, char* s, int length) {
  return write(fd[WRITE], s, length);
}

void free_ciphers(Cipher* cipher) {
  if (cipher == NULL) {
    return;
  }

  free_ciphers(cipher->next);
  pthread_join(*(cipher->thread), NULL);
  free(cipher->thread);
  free(cipher);
}

void* perform_cipher(void* arg) {
  Cipher* cipher = (Cipher*)arg;
  // we multiply 2 since each pipe has two file descriptors
  int* input = FD + cipher->cipher_id * 2;
  int* output = input + 2; // add two to find the output file descriptor

  char line[MAX_LINE_LENGTH];
  while (1) {
    read_pipe(input, line, MAX_LINE_LENGTH);

    for (int j = 0; j < SIZE; j++) {
      line[j] = mod(line[j] + cipher->value, NUM_CHARS); // NOLINT(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
    }

    write_pipe(output, line, SIZE + 1);

    // Terminate if an empty string is encountered
    if (SIZE == 0) {
      break;
    }
  }

  return 0;
}

int main(int argc, char** argv) {
  if (argc < 2 || argc > (MAX_CIPHERS + 1)) {
    printf("Invalid # of arguments. Expected 0 < CIPHERS <= %d.\n", MAX_CIPHERS);
    return 1;
  }

  FD = malloc(argc * 2 * sizeof(int)); // use argc since it's the # of ciphers + 1
  for (int i = 0; i < argc * 2; i += 2) {
    pipe(FD + i);
  }

  Cipher* root = NULL;
  Cipher* current = NULL;
  for (int i = 1; i < argc; i++) {
    Cipher* cipher = malloc(sizeof(Cipher));
    int value = str2int(argv[i]);
    if (value < -128 || value > 127) {
      printf("%d is not within the range of -128 to 127", value);
      return 1;
    }

    cipher->cipher_id = i - 1;
    cipher->value = (char)value;
    cipher->next = NULL;
    cipher->thread = malloc(sizeof(pthread_t));
    pthread_create(cipher->thread, NULL, perform_cipher, (void*)cipher);

    if (current == NULL) {
      root = cipher;
    } else {
      current->next = cipher;
    }

    current = cipher;
  }

  // freopen("../q1_input_simple_ish.txt", "r", stdin); // Only use for testing

  char line[MAX_LINE_LENGTH];
  int* output = FD;
  int* input = FD + argc * 2 - 2;
  while (1) {
    char* result = fgets(line, sizeof(line), stdin);
    if (result == NULL) {
      // This may seem a bit weird but an empty string is how I indicate to my threads to terminate
      // Thus, I create an empty string, push it through the ciphers which each push it to the next cipher
      // and then each cipher thread terminates
      line[0] = '\0';
    }

    // remove the trailing newline
    line[strcspn(line, "\n")] = '\0';

    SIZE = get_size(line);
    for (int j = 0; j < SIZE; j++) {
      line[j] = line[j] - CHAR_MIN; // NOLINT(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
    }

    write_pipe(output, line, SIZE + 1);
    read_pipe(input, line, SIZE + 1);

    for (int j = 0; j < SIZE; j++) {
      line[j] = line[j] + CHAR_MIN; // NOLINT(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
    }

    // If the line is an empty string... terminate!
    if (SIZE == 0) {
      break;
    }

    printf("%s\n", line);
  }

  free_ciphers(root);

  for (int i = 0; i < argc * 2; i++) {
    close(FD[i]);
  }

  free(FD);
}