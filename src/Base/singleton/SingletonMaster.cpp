// Copyright 2008 Fangling Software Co., Ltd. All Rights Reserved.
// Author: thinkfly@gmail.com (Yiyuan Zhong)

#include "base/singleton/SingletonMaster.h"

void SingletonMaster::Activate() {
  master_.manager_.RunAsMaster();
  master_.singleton_mutex_ = master_.manager_.singleton_mutex();
  master_.singleton_instances_ = master_.manager_.singleton_instances();
  master_.activated_ = true;
}

SingletonMaster SingletonMaster::master_;
