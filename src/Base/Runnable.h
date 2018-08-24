// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef BASE_RUNNABLE_H__
#define BASE_RUNNABLE_H__

class Runnable {
 public:
   virtual ~Runnable() {}

  virtual void Run() = 0;

};

#endif // BASE_RUNNABLE_H__
