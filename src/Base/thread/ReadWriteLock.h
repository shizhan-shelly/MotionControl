// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

/*
 * Read-write lock is a "share reading and exclusive writing" lock. It allows
 * multiple readers to access data simultaneously, or only one writer to access
 * data exclusively, but not both.
 *
 * That is to say the writer can safely modify data before it unlocks the
 * read-write lock, until then can other accessors get unblocked. If there are
 * already readers accessing data, all writers should block.
 *
 * Non recursive, writer first.
 *
 */

#ifndef BASE_THREAD_READWRITELOCK_H__
#define BASE_THREAD_READWRITELOCK_H__

namespace internal {
class ReadWriteLockContext;
} // namespace internal

class ReadWriteLock {
public:
  ReadWriteLock();
  ~ReadWriteLock();

  void ReaderLock();
  void WriterLock();
  bool TryReaderLock();
  bool TryWriterLock();
  void Unlock();

 private:
  explicit ReadWriteLock(const ReadWriteLock &);
  ReadWriteLock &operator = (const ReadWriteLock &);

  internal::ReadWriteLockContext *rw_lock_;

}; // class ReadWriteLock

#endif // BASE_THREAD_READWRITELOCK_H__