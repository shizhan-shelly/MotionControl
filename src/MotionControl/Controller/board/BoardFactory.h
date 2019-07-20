// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_BOARD_BOARDFACTORY_H__
#define CONTROLLER_BOARD_BOARDFACTORY_H__

class AbstractBoard;
struct BoardItem;

class BoardFactory {
 public:
  static AbstractBoard *CreateBoard(int board_index);

  static AbstractBoard *CreateBoard(const BoardItem &board_infor);

}; // class BoardFactory

#endif // CONTROLLER_BOARD_BOARDFACTORY_H__
