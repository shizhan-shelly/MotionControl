// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#include "base/singleton/SingletonSlave.h"

void SingletonSlave::Activate(const SingletonMaster *master) {
  slave_.manager_.RunAsSlave(master);
  slave_.activated_ = true;
}

SingletonSlave SingletonSlave::slave_;
