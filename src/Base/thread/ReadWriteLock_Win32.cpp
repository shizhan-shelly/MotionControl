// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#ifdef WIN32

#include "base/thread/ReadWriteLock.h"

#include <Windows.h>

namespace internal {

class ReadWriteLockContext {
 public:
  ReadWriteLockContext() : access_(0), reader_queue_(0), writer_queue_(0) {
    mutex_ = CreateEvent(NULL, FALSE, TRUE, NULL);
    reader_wait_ = CreateSemaphore(NULL, 0, MAXLONG, NULL);
    writer_wait_ = CreateSemaphore(NULL, 0, MAXLONG, NULL);
  }

  ~ReadWriteLockContext() {
    CloseHandle(writer_wait_);
    CloseHandle(reader_wait_);
    CloseHandle(mutex_);
  }

  int access_;
  int reader_queue_;
  int writer_queue_;
  HANDLE mutex_;
  HANDLE reader_wait_;
  HANDLE writer_wait_;

}; // class ReadWriteLockContext

}

ReadWriteLock::ReadWriteLock() : rw_lock_(new internal::ReadWriteLockContext) {
}

ReadWriteLock::~ReadWriteLock() {
  delete rw_lock_;
}

void ReadWriteLock::ReaderLock() {
  WaitForSingleObject(rw_lock_->mutex_, INFINITE);

  bool access_pending = (rw_lock_->access_ < 0 || rw_lock_->writer_queue_ > 0);
  if (access_pending) {
    ++rw_lock_->reader_queue_;
  } else {
    ++rw_lock_->access_;
  }
  SetEvent(rw_lock_->mutex_);

  if (access_pending) {
    WaitForSingleObject(rw_lock_->reader_wait_, INFINITE);
  }
}

void ReadWriteLock::WriterLock() {
  WaitForSingleObject(rw_lock_->mutex_, INFINITE);

  bool access_pending = (rw_lock_->access_ != 0);
  if (access_pending) {
    ++rw_lock_->writer_queue_;
  } else {
    --rw_lock_->access_;
  }
  SetEvent(rw_lock_->mutex_);

  if (access_pending) {
    WaitForSingleObject(rw_lock_->writer_wait_, INFINITE);
  }
}

bool ReadWriteLock::TryReaderLock() {
  bool access_granted = false;
  WaitForSingleObject(rw_lock_->mutex_, INFINITE);

  if (rw_lock_->access_ >= 0 && rw_lock_->writer_queue_ == 0) {
    ++rw_lock_->access_;
    access_granted = true;
  }
  SetEvent(rw_lock_->mutex_);

  return access_granted;
}

bool ReadWriteLock::TryWriterLock() {
  bool access_granted = false;
  WaitForSingleObject(rw_lock_->mutex_, INFINITE);

  if (rw_lock_->access_ == 0) {
    --rw_lock_->access_;
    access_granted = true;
  }
  SetEvent(rw_lock_->mutex_);

  return access_granted;
}

void ReadWriteLock::Unlock() {
  WaitForSingleObject(rw_lock_->mutex_, INFINITE);

  if (rw_lock_->access_ > 0) {
    --rw_lock_->access_;
  } else {
    ++rw_lock_->access_;
  }

  HANDLE fortune = NULL;
  LONG cookies = 0;

  if (rw_lock_->access_ == 0) {
    if (rw_lock_->writer_queue_ > 0) {
      --rw_lock_->access_;
      --rw_lock_->writer_queue_;
      fortune = rw_lock_->writer_wait_;
      cookies = 1;
    } else if (rw_lock_->reader_queue_ > 0) {
      rw_lock_->access_ = rw_lock_->reader_queue_;
      rw_lock_->reader_queue_ = 0;
      fortune = rw_lock_->reader_wait_;
      cookies = rw_lock_->access_;
    }
  }

  if (fortune != NULL) {
    ReleaseSemaphore(fortune, cookies, NULL);
  }

  SetEvent(rw_lock_->mutex_);
}

#endif // WIN32
