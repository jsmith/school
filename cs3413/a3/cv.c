//
// Created by Jacob Smith on 2020-05-23.
//
#include "cv.h"
#include <stdlib.h>

CV* cv_init() {
  CV* cv = malloc(sizeof(CV));
  sem_unlink("/cv/mutex");
  sem_unlink("/cv/s");
  cv->mutex = sem_open("/cv/mutex", O_CREAT, 0644, 1);
  cv->s = sem_open("/cv/s", O_CREAT, 0644, 0);
  return cv;
}

void cv_wait(CV* cv) {
  sem_wait(cv->mutex);
  cv->waiters++;
  sem_post(cv->mutex);
  sem_wait(cv->s);
}

void cv_notify_all(CV* cv) {
  sem_wait(cv->mutex);
  while (cv->waiters > 0) {
    cv->waiters--;
    sem_post(cv->s);
  }
  sem_post(cv->mutex);
}

void cv_close(CV* cv) {
  sem_close(cv->mutex);
  sem_close(cv->s);
  free(cv);
}
