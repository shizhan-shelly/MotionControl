// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Controller/board/IOConfigObserver.h"

#include "MotionControl/Controller/board/AbstractBoard.h"
#include "MotionControl/Controller/board/IOBoardManager.h"

IOConfigObserver::IOConfigObserver() {}

IOConfigObserver::~IOConfigObserver() {}

std::vector<int> IOConfigObserver::GetConfigurableGroup() const {
  std::vector<int> group;
  for (int i = 0; i < BOARD_SIZE; i++) {
    group.push_back(i);
  }
  return group;
}

std::vector<int> IOConfigObserver::GetConfigurableIndex(
    int group,
    int io_type) const {

  int cnt = 0;
  std::map<int, AbstractBoard *> boards = IOBoardManager::GetInstance()->GetBoard();
  std::map<int, AbstractBoard *>::iterator it = boards.find(group);
  AbstractBoard *board = it != boards.end() ? it->second : NULL;
  if (board) {
    switch (io_type) {
     case 0:
      cnt = board->GetBoardInputSize();
      break;
     case 1:
      cnt = board->GetBoardOutputSize();
      break;
     case 2:
      cnt = board->GetBoardADSize();
      break;
     case 3:
      cnt = board->GetBoardDASize();
      break;
     default:
      break;
    }
  }
  std::vector<int> index;
  for (int i = 0; i <= cnt; i++) {
    index.push_back(i);
  }
  return index;
}

QStringList IOConfigObserver::GetConfigurableSerialPort(int group) const {
  QStringList serial_port_list;
  std::map<int, AbstractBoard *> boards = IOBoardManager::GetInstance()->GetBoard();
  std::map<int, AbstractBoard *>::iterator it = boards.find(group);
  AbstractBoard *board = it != boards.end() ? it->second : NULL;
  if (board) {
    serial_port_list = board->GetSerialPortList();
  }
  return serial_port_list;
}

QStringList IOConfigObserver::TransformQStringList(
    const std::vector<int> &items) {

  QStringList list;
  for (size_t i = 0; i < items.size(); i++) {
    list << QString("%1").arg(items[i]);
  }
  return list;
}
