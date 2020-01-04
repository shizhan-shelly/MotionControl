// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../controller/IOBoardManager.h"

#include "../controller/board/AbstractBoard.h"
#include "../controller/board/BoardFactory.h"

IOBoardManager::IOBoardManager() {}

IOBoardManager::~IOBoardManager() {
  ClearBoard();
}

void IOBoardManager::InitializeBoard() {
  ClearBoard();
  for (int i = 0; i < BOARD_SIZE; i++) {
    AbstractBoard *board_item = BoardFactory::CreateBoard(i);
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
