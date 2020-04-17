// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_ICUTIOV23BOARD_H__
#define CONTROLLER_BOARD_ICUTIOV23BOARD_H__

#include "MotionControl/controller/board/AbstractBoard.h"

class ICutIOV23Board : public AbstractBoard {
 public:
  ICutIOV23Board() {}
  ~ICutIOV23Board() {}

  virtual int GetBoardInputSize() const {
    return 20;
  }

  virtual int GetBoardOutputSize() const {
    return 32;
  }

  virtual int GetBoardADSize() const {
    return 2;
  }

  virtual int GetBoardDASize() const {
    return 4;
  }

  virtual QStringList GetSerialPortList() const {

  }

}; // class ICutIOV23Board

#endif // CONTROLLER_BOARD_ICUTIOV23BOARD_H__
