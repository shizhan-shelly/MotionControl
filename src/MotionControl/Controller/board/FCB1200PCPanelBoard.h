// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_FCB1200PCPANELBOARD_H__
#define CONTROLLER_BOARD_FCB1200PCPANELBOARD_H__

#include "MotionControl/controller/board/AbstractBoard.h"

class FCB1200PCPanelBoard : public AbstractBoard {
 public:
  FCB1200PCPanelBoard() {}
  ~FCB1200PCPanelBoard() {}

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

}; // class FCB1200PCPanelBoard

#endif // CONTROLLER_BOARD_FCB1200PCPANELBOARD_H__
