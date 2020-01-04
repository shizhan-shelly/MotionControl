// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_ONECUTV21BOARD_H__
#define CONTROLLER_BOARD_ONECUTV21BOARD_H__

#include "MotionControl/controller/board/AbstractBoard.h"

class OneCutV21Board : public AbstractBoard {
 public:
  OneCutV21Board() {}
  ~OneCutV21Board() {}

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

}; // class OneCutV21Board

#endif // CONTROLLER_BOARD_ONECUTV21BOARD_H__