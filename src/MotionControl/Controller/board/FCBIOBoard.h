// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_FCBIOBOARD_H__
#define CONTROLLER_BOARD_FCBIOBOARD_H__

#include "MotionControl/controller/board/AbstractBoard.h"

class FCBIOBoard : public AbstractBoard {
 public:
  FCBIOBoard() {}
  ~FCBIOBoard() {}

  virtual int GetBoardInputSize() const {
    return 24;
  }

  virtual int GetBoardOutputSize() const {
    return 15;
  }

  virtual int GetBoardADSize() const {
    return 0;
  }

  virtual int GetBoardDASize() const {
    return 0;
  }

  virtual QStringList GetSerialPortList() const {
    QStringList serial_port = QStringList() << "" << "";
    return serial_port;
  }

}; // class FCBIOBoard

#endif // CONTROLLER_BOARD_FCBIOBOARD_H__
