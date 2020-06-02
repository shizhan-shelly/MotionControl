// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_FCBPANELBOARD_H__
#define CONTROLLER_BOARD_FCBPANELBOARD_H__

#include "MotionControl/controller/board/AbstractBoard.h"

class FCBPanelBoard : public AbstractBoard {
 public:
  FCBPanelBoard() {}
  ~FCBPanelBoard() {}

  virtual int GetBoardInputSize() const {
    return 21;
  }

  virtual int GetBoardOutputSize() const {
    return 23;
  }

  virtual int GetBoardADSize() const {
    return 6;
  }

  virtual int GetBoardDASize() const {
    return 0;
  }

  virtual QStringList GetSerialPortList() const {
    QStringList serial_port = QStringList() << "" << "";
    return serial_port;
  }

}; // class FCBPanelBoard

#endif // CONTROLLER_BOARD_FCBPANELBOARD_H__
