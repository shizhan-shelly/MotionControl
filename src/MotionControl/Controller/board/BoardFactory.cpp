// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/controller/board/BoardFactory.h"

#include "MotionControl/controller/board/FCB1200PCBoard.h"
#include "MotionControl/controller/board/FCB1200PCExpBoard.h"
#include "MotionControl/controller/board/FCBIOBoard.h"
#include "MotionControl/controller/board/FCBPanelBoard.h"
#include "MotionControl/controller/board/OneCutV21Board.h"
#include "MotionControl/Cutter.h"

AbstractBoard *BoardFactory::CreateBoard(int board_index) {
  BoardItem board_item;
  board_item.group_ = board_index;
  if (board_index == 0) {
    board_item.model_ = "ONECUTV21";
    board_item.addr_ = "";
  } else {
    Cutter *cutter = Cutter::GetInstance();
    QVector<BoardItem> board_items =
        cutter->GetExtendedBoardModel()->GetExtendedBoard();

    board_item = board_items[board_index - 1];
  }
  return CreateBoard(board_item);
}

AbstractBoard *BoardFactory::CreateBoard(const BoardItem &board_infor) {
  AbstractBoard *board = NULL;
  if (board_infor.model_.compare("FCB1200PC") == 0) {
    board = new FCB1200PCBoard();
    board->initializeBoard(board_infor);
  } else if (board_infor.model_.compare("FCB1200PC_EXP") == 0) {
    board = new FCB1200PCEXPBoard();
    board->initializeBoard(board_infor);
  } else if (board_infor.model_.compare("FCB_IO") == 0) {
    board = new FCBIOBoard();
    board->initializeBoard(board_infor);
  } else if (board_infor.model_.compare("FCB_PANEL") == 0) {
    board = new FCBPanelBoard();
    board->initializeBoard(board_infor);
  } else if (board_infor.model_.compare("ONECUTV21") == 0) {
    board = new OneCutV21Board();
    board->initializeBoard(board_infor);
  }
  return board;
}
