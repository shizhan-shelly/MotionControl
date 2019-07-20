// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_LOCALBOARD_H__
#define CONTROLLER_BOARD_LOCALBOARD_H__

#include "MotionControl/controller/board/AbstractBoard.h"

class LocalBoard : public AbstractBoard {
 public:
  LocalBoard() {}
  ~LocalBoard() {}

  virtual int GetBoardInputSize() const {
    return 64;
  }

  virtual int GetBoardOutputSize() const {
    return 64;
  }

  virtual int GetBoardADSize() const {
    return 8;
  }

  virtual int GetBoardDASize() const {
    return 8;
  }

}; // class LocalBoard

#endif // CONTROLLER_BOARD_LOCALBOARD_H__
