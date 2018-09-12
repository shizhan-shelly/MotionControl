// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifndef WIN32

#include "base/thread/ReadWriteLock.h"

#include <pthread.h>
#include <semaphore.h>

namespace internal {

class ReadWriteLockContext {
 public:
  ReadWriteLockContext() : access_(0), reader_queue_(0), writer_queue_(0) {
    pthread_mutex_init(&mutex_, NULL);
    sem_init(&reader_wait_, 0, 0);
    sem_init(&writer_wait_, 0, 0);
  }

  ~ReadWriteLockContext() {
    sem_destroy(&writer_wait_);
    sem_destroy(&reader_wait_);
    pthread_mutex_destroy(&mutex_);
  }

  int access_;
  int reader_queue_;
  int writer_queue_;
  pthread_mutex_t mutex_;
  sem_t reader_wait_;
  sem_t writer_wait_;

}; // class ReadWriteLockContext

}

ReadWriteLock::ReadWriteLock() : rw_lock_(new internal::ReadWriteLockContext) {
}

ReadWriteLock::~ReadWriteLock() {
  delete rw_lock_;
}

void ReadWriteLock::ReaderLock() {
  pthread_mutex_lock(&rw_lock_->mutex_);

  bool access_pending = (rw_lock_->access_ < 0 || rw_lock_->writer_queue_ > 0);
  if (access_pending) {
    ++rw_lock_->reader_queue_;
  } else {
    ++rw_lock_->access_;
  }
  pthread_mutex_unlock(&rw_lock_->mutex_);

  if (access_pending) {
    sem_wait(&rw_lock_->reader_wait_);
  }
}

void ReadWriteLock::WriterLock() {
  pthread_mutex_lock(&rw_lock_->mutex_);

  bool access_pending = (rw_lock_->access_ != 0);
  if (access_pending) {
    ++rw_lock_->writer_queue_;
  } else {
    --rw_lock_->access_;
  }
  pthread_mutex_unlock(&rw_lock_->mutex_);

  if (access_pending) {
    sem_wait(&rw_lock_->writer_wait_);
  }
}

bool ReadWriteLock::TryReaderLock() {
  bool access_granted = false;
  pthread_mutex_lock(&rw_lock_->mutex_);

  if (rw_lock_->access_ >= 0 && rw_lock_->writer_queue_ == 0) {
    ++rw_lock_->access_;
    access_granted = true;
  }
  pthread_mutex_unlock(&rw_lock_->mutex_);

  return access_granted;
}

bool ReadWriteLock::TryWriterLock() {
  bool access_granted = false;
  pthread_mutex_lock(&rw_lock_->mutex_);

  if (rw_lock_->access_ == 0) {
    --rw_lock_->access_;
    access_granted = true;
  }
  pthread_mutex_unlock(&rw_lock_->mutex_);

  return access_granted;
}

void ReadWriteLock::Unlock() {
  pthread_mutex_lock(&rw_lock_->mutex_);

  if (rw_lock_->access_ > 0) {
    --rw_lock_->access_;
  } else {
    ++rw_lock_->access_;
  }

  sem_t *fortune = NULL;
  int cookies = 0;

  if (rw_lock_->access_ == 0) {
    if (rw_lock_->writer_queue_ > 0) {
      --rw_lock_->access_;
      --rw_lock_->writer_queue_;
      fortune = &rw_lock_->writer_wait_;
      cookies = 1;
    } else if (rw_lock_->reader_queue_ > 0) {
      rw_lock_->access_ = rw_lock_->reader_queue_;
      rw_lock_->reader_queue_ = 0;
      fortune = &rw_lock_->reader_wait_;
      cookies = rw_lock_->access_;
    }
  }

  if (fortune != NULL) {
    while (cookies--) {
      sem_post(fortune);
    }
  }

  pthread_mutex_unlock(&rw_lock_->mutex_);
}

#endif // WIN32
