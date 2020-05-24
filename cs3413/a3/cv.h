//
// Created by Jacob Smith on 2020-05-23.
//

#ifndef A2_CV_H
#define A2_CV_H

#include <semaphore.h>

typedef struct CV {
  int waiters;
  sem_t* mutex;
  sem_t* s;
} CV;

CV* cv_init();
void cv_wait(CV* cv);
void cv_notify_all(CV* cv);
void cv_close(CV* cv);

#endif //A2_CV_H
