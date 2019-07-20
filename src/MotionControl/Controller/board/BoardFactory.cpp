// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/controller/board/BoardFactory.h"

#include "MotionControl/controller/board/FCB1200PCBoard.h"
#include "MotionControl/controller/board/FCB1200PCExpBoard.h"
#include "MotionControl/controller/board/FCB1200PCPanelBoard.h"
#include "MotionControl/controller/board/LocalBoard.h"
#include "MotionControl/Cutter.h"

AbstractBoard *BoardFactory::CreateBoard(int board_index) {
  AbstractBoard *board = NULL;
  if (board_index == 0) {
    board = new LocalBoard();
  } else {
    BoardItem board_item;
    board_item.group_ = board_index;
    board = CreateBoard(board_item);
  }
  return board;
}

AbstractBoard *BoardFactory::CreateBoard(const BoardItem &board_infor) {
  AbstractBoard *board = NULL;
  if (board_infor.model_.compare("FCB1200PC") == 0) {
    board = new FCB1200PCBoard();
    board->initializeBoard(board_infor);
  } else if (board_infor.model_.compare("FCB1200PC_EXP") == 0) {
    board = new FCB1200PCEXPBoard();
    board->initializeBoard(board_infor);
  } else if (board_infor.model_.compare("FCB1200PC_PANEL") == 0) {
    board = new FCB1200PCPanelBoard();
    board->initializeBoard(board_infor);
  }
  return board;
}
