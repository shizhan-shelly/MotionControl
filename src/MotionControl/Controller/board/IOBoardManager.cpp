// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Controller/board/IOBoardManager.h"

#include "MotionControl/Controller/board/AbstractBoard.h"
#include "MotionControl/controller/board/FCB1200PCBoard.h"
#include "MotionControl/controller/board/FCB1200PCExpBoard.h"
#include "MotionControl/controller/board/FCBIOBoard.h"
#include "MotionControl/controller/board/FCBPanelBoard.h"
#include "MotionControl/controller/board/ICutIOV23Board.h"
#include "MotionControl/controller/board/OneCutV21Board.h"
#include "MotionControl/Cutter.h"

IOBoardManager::IOBoardManager() {}

IOBoardManager::~IOBoardManager() {
  ClearBoard();
}

void IOBoardManager::InitializeBoard() {
  ClearBoard();
  for (int i = 0; i < BOARD_SIZE; i++) {
    AbstractBoard *board_item = CreateBoard(i);
    if (board_item) {
      board_items_.insert(std::make_pair(i, board_item));
    }
  }
}

void IOBoardManager::ClearBoard() {
  std::map<int, AbstractBoard *>::iterator iter = board_items_.begin();
  for (; iter != board_items_.end(); ++iter) {
    if (iter->second) {
      delete iter->second;
      iter->second = NULL;
    }
  }
  board_items_.clear();
}

void IOBoardManager::SaveBoardInfor() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    std::map<int, AbstractBoard *>::const_iterator iter = board_items_.find(i);
    if (iter != board_items_.end()) {
      // input
      for (int j = 0; j < iter->second->GetBoardInputSize(); j++) {
        ConfigItem item;
        iter->second->GetPhyInput(j, item);
      }
      // output
      for (int j = 0; j < iter->second->GetBoardOutputSize(); j++) {
        ConfigItem item;
        iter->second->GetPhyOutput(j, item);
      }
      // AD
      for (int j = 0; j < iter->second->GetBoardADSize(); j++) {
        ADItem item;
        iter->second->GetPhyAD(j, item);
      }
      // DA
      for (int j = 0; j < iter->second->GetBoardDASize(); j++) {
        DAItem item;
        iter->second->GetPhyDA(j, item);
      }
    }
  }
}

AbstractBoard *IOBoardManager::CreateBoard(int board_index) {
  BoardItem board_item;
  board_item.group_ = board_index;
  if (board_index == 0) {
    board_item.model_ = "ONECUT_V2.1";
    board_item.addr_ = "";
  } else {
    Cutter *cutter = Cutter::GetInstance();
    QVector<BoardItem> board_items =
        cutter->GetExtendedBoardModel()->GetExtendedBoard();

    board_item = board_items[board_index - 1];
  }
  return CreateBoard(board_item);
}

AbstractBoard *IOBoardManager::CreateBoard(const BoardItem &board_infor) {
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
  } else if (board_infor.model_.compare("ONECUT_V2.1") == 0) {
    board = new OneCutV21Board();
    board->initializeBoard(board_infor);
  } else if (board_infor.model_.compare("ICUT_V2.3") == 0) {
    board = new ICutIOV23Board();
    board->initializeBoard(board_infor);
  }
  return board;
}

std::map<int, AbstractBoard *> IOBoardManager::GetBoard() const {
  return board_items_;
}

bool IOBoardManager::CheckInputItem(const ConfigItem &item) {
  int group = item.group.toInt();
  int index = item.index.toInt();
  std::map<int, AbstractBoard *>::const_iterator iter =
      board_items_.find(group);

  if (iter != board_items_.end()) {
    return iter->second->SetPhyInput(index, item);
  }
  return false;
}

bool IOBoardManager::CheckOutputItem(const ConfigItem &item) {
  int group = item.group.toInt();
  int index = item.index.toInt();
  std::map<int, AbstractBoard *>::const_iterator iter =
      board_items_.find(group);

  if (iter != board_items_.end()) {
    return iter->second->SetPhyOutput(index, item);
  }
  return false;
}

bool IOBoardManager::CheckADItem(const ADItem &item) {
  int group = item.group.toInt();
  int index = item.index.toInt();
  std::map<int, AbstractBoard *>::const_iterator iter =
      board_items_.find(group);

  if (iter != board_items_.end()) {
    return iter->second->SetPhyAD(index, item);
  }
  return false;
}

bool IOBoardManager::CheckDAItem(const DAItem &item) {
  int group = item.group.toInt();
  int index = item.index.toInt();
  std::map<int, AbstractBoard *>::const_iterator iter =
      board_items_.find(group);

  if (iter != board_items_.end()) {
    return iter->second->SetPhyDA(index, item);
  }
  return false;
}
