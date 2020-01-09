// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_IOBOARDMANAGER_H__
#define CONTROLLER_BOARD_IOBOARDMANAGER_H__

#include "base/singleton/Singleton.h"

#include <map>

#include "MotionControl/Controller/DeviceDefine.h"

class AbstractBoard;

class IOBoardManager : public Singleton {
  DECLARE_SINGLETON(IOBoardManager)

 public:
  void InitializeBoard();

  void SaveBoardInfor();

  void LoadDeviceConfig();

  std::map<int, AbstractBoard *> GetBoard() const;

  bool CheckInputItem(const ConfigItem &item);
  bool CheckOutputItem(const ConfigItem &item);
  bool CheckADItem(const ADItem &item);
  bool CheckDAItem(const DAItem &item);

 private:
  std::map<int, AbstractBoard *> board_items_;

  IOBoardManager();
  ~IOBoardManager();

  void ClearBoard();

  AbstractBoard *CreateBoard(int board_index);

  AbstractBoard *CreateBoard(const BoardItem &board_infor);

}; // class IOBoardManager

#endif // CONTROLLER_BOARD_IOBOARDMANAGER_H__
