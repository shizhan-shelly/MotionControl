// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_ABSTRACTBOARD_H__
#define CONTROLLER_BOARD_ABSTRACTBOARD_H__

#include <map>
#include <QStringList>

#include "MotionControl/Controller/DeviceDefine.h"

class AbstractBoard {
 public:
  AbstractBoard();
  virtual ~AbstractBoard();

  void initializeBoard(BoardItem board_infor);

  virtual int GetBoardInputSize() const = 0;
  virtual int GetBoardOutputSize() const = 0;
  virtual int GetBoardADSize() const = 0;
  virtual int GetBoardDASize() const = 0;
  virtual QStringList GetSerialPortList() const = 0;

  bool GetPhyInput(int phy_index, ConfigItem &item) const;
  bool GetPhyOutput(int phy_index, ConfigItem &item) const;
  bool GetPhyAD(int phy_index, ADItem &item) const;
  bool GetPhyDA(int phy_index, DAItem &item) const;

  bool SetPhyInput(const ConfigItem &item);
  bool SetPhyOutput(const ConfigItem &item);
  bool SetPhyAD(const ADItem &item);
  bool SetPhyDA(const DAItem &item);

 private:
  std::map<int, ConfigItem> input_;
  std::map<int, ConfigItem> output_;
  std::map<int, ADItem> ad_;
  std::map<int, DAItem> da_;
  QStringList serial_port_;

}; // class AbstractBoard

#endif // CONTROLLER_BOARD_ABSTRACTBOARD_H__
