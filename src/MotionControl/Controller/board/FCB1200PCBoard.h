// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_FCB1200PCBOARD_H__
#define CONTROLLER_BOARD_FCB1200PCBOARD_H__

#include "MotionControl/controller/board/AbstractBoard.h"

class FCB1200PCBoard : public AbstractBoard {
 public:
  FCB1200PCBoard() {}
  ~FCB1200PCBoard() {}

  virtual int GetBoardInputSize() const {
    return 48;
  }

  virtual int GetBoardOutputSize() const {
    return 24;
  }

  virtual int GetBoardADSize() const {
    return 0;
  }

  virtual int GetBoardDASize() const {
    return 0;
  }

}; // class FCB1200PCBoard

#endif // CONTROLLER_BOARD_FCB1200PCBOARD_H__
