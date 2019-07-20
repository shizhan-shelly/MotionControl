// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_FCB1200PCEXPBOARD_H__
#define CONTROLLER_BOARD_FCB1200PCEXPBOARD_H__

#include "MotionControl/controller/board/AbstractBoard.h"

class FCB1200PCEXPBoard : public AbstractBoard {
 public:
  FCB1200PCEXPBoard() {}
  ~FCB1200PCEXPBoard() {}

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

}; // class FCB1200PCEXPBoard

#endif // CONTROLLER_BOARD_FCB1200PCEXPBOARD_H__
