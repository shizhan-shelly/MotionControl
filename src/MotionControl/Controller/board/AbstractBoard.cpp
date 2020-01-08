// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/controller/board/AbstractBoard.h"

AbstractBoard::AbstractBoard() {}

AbstractBoard::~AbstractBoard() {}

void AbstractBoard::initializeBoard(BoardItem board_infor) {
  input_.clear();
  for (int i = 0; i < GetBoardInputSize(); i++) {
    ConfigItem item;
    item.group = QString("%1").arg(board_infor.group_);
    item.index = QString("%1").arg(i + 1);
    item.name = QString("PhyIn%1").arg(i + 1);
    item.no_nc = "NC";
    input_.insert(std::make_pair(i + 1, item));
  }
  output_.clear();
  for (int i = 0; i < GetBoardOutputSize(); i++) {
    ConfigItem item;
    item.group = QString("%1").arg(board_infor.group_);
    item.index = QString("%1").arg(i + 1);
    item.name = QString("PhyOut%1").arg(i + 1);
    item.no_nc = "NC";
    output_.insert(std::make_pair(i + 1, item));
  }
  ad_.clear();
  for (int i = 0; i < GetBoardADSize(); i++) {
    ADItem item;
    item.group = QString("%1").arg(board_infor.group_);
    item.index = QString("%1").arg(i + 1);
    item.name = QString("PhyAD%1").arg(i + 1);
    ad_.insert(std::make_pair(i + 1, item));
  }
  da_.clear();
  for (int i = 0; i < GetBoardDASize(); i++) {
    DAItem item;
    item.group = QString("%1").arg(board_infor.group_);
    item.index = QString("%1").arg(i + 1);
    item.name = QString("PhyDA%1").arg(i + 1);
    item.threshold = 0;
    da_.insert(std::make_pair(i + 1, item));
  }
}

bool AbstractBoard::GetPhyInput(int phy_index, ConfigItem &item) const {
  std::map<int, ConfigItem>::const_iterator it = input_.find(phy_index);
  if (it == input_.end()) {
    return false;
  }
  item = it->second;
  return true;
}

bool AbstractBoard::GetPhyOutput(int phy_index, ConfigItem &item) const {
  std::map<int, ConfigItem>::const_iterator it = output_.find(phy_index);
  if (it == output_.end()) {
    return false;
  }
  item = it->second;
  return true;
}

bool AbstractBoard::GetPhyAD(int phy_index, ADItem &item) const {
  std::map<int, ADItem>::const_iterator it = ad_.find(phy_index);
  if (it == ad_.end()) {
    return false;
  }
  item = it->second;
  return true;
}

bool AbstractBoard::GetPhyDA(int phy_index, DAItem &item) const {
  std::map<int, DAItem>::const_iterator it = da_.find(phy_index);
  if (it == da_.end()) {
    return false;
  }
  item = it->second;
  return true;
}

bool AbstractBoard::SetPhyInput(int phy_index, const ConfigItem &item) {
  std::map<int, ConfigItem>::iterator it = input_.find(phy_index);
  if (it == input_.end()) {
    return false;
  }
  if (!it->second.name.isEmpty() && it->second.name.compare(item.name) != 0) {
    return false;
  }
  it->second = item;
  return true;
}

bool AbstractBoard::SetPhyOutput(int phy_index, const ConfigItem &item) {
  std::map<int, ConfigItem>::iterator it = output_.find(phy_index);
  if (it == output_.end()) {
    return false;
  }
  if (!it->second.name.isEmpty() && it->second.name.compare(item.name) != 0) {
    return false;
  }
  it->second = item;
  return true;
}

bool AbstractBoard::SetPhyAD(int phy_index, const ADItem &item) {
  std::map<int, ADItem>::iterator it = ad_.find(phy_index);
  if (it == ad_.end()) {
    return false;
  }
  if (!it->second.name.isEmpty() && it->second.name.compare(item.name) != 0) {
    return false;
  }
  it->second = item;
  return true;
}

bool AbstractBoard::SetPhyDA(int phy_index, const DAItem &item) {
  std::map<int, DAItem>::iterator it = da_.find(phy_index);
  if (it == da_.end()) {
    return false;
  }
  if (!it->second.name.isEmpty() && it->second.name.compare(item.name) != 0) {
    return false;
  }
  it->second = item;
  return true;
}
