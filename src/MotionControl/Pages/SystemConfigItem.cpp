// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SystemConfigItem.h"

#include <assert.h>

SystemConfigItem::SystemConfigItem() {}

SystemConfigItem::~SystemConfigItem() {}

void SystemConfigItem::Append(const std::string &item) {
  item_element_.push_back(item);
}

std::string SystemConfigItem::GetItemElement(int column) const {
  assert(column < item_element_.size());
  return item_element_[column];
}
