// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_IOBOARDMANAGER_H__
#define CONTROLLER_IOBOARDMANAGER_H__

#include "base/singleton/Singleton.h"

#include <map>

#include "MotionControl/Controller/DeviceDefine.h"

class AbstractBoard;

class IOBoardManager : public Singleton {
  DECLARE_SINGLETON(IOBoardManager)

 public:
  void InitializeBoard();

  void SaveBoardInfor();

  bool CheckInputItem(const ConfigItem &item);
  bool CheckOutputItem(const ConfigItem &item);
  bool CheckADItem(const ADItem &item);
  bool CheckDAItem(const DAItem &item);

 private:
  std::map<int, AbstractBoard *> board_items_;

  IOBoardManager();
  ~IOBoardManager();

  void ClearBoard();

}; // class IOBoardManager

#endif // CONTROLLER_IOBOARDMANAGER_H__
