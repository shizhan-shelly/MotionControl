// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_IOCONFIGOBSERVER_H__
#define CONTROLLER_BOARD_IOCONFIGOBSERVER_H__

#include "base/singleton/Singleton.h"

#include <vector>
#include <QStringList>

class IOConfigObserver : public Singleton {
  DECLARE_SINGLETON(IOConfigObserver)

 public:
  std::vector<int> GetConfigurableGroup() const;

  // io_type: 0, input; 1, output; 2, AD; 3, DA
  std::vector<int> GetConfigurableIndex(int group, int io_type) const;

  QStringList GetConfigurableSerialPort(int group) const;

  static QStringList TransformQStringList(const std::vector<int> &items);

 private:
  IOConfigObserver();
  ~IOConfigObserver();

}; // class IOConfigObserver

#endif // CONTROLLER_BOARD_IOCONFIGOBSERVER_H__
