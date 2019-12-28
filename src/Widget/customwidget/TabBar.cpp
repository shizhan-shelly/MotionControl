// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../customwidget/TabBar.h"

#include "assert.h"

namespace widget {

TabBar::TabBar(QWidget *parent) : QTabBar(parent) {}

TabBar::~TabBar() {}

void TabBar::initBar(const QMap<int, QString> &bar_infor) {
  assert(!bar_infor.empty());
  clearBar();
  QMap<int, QString>::const_iterator it = bar_infor.begin();
  for (; it != bar_infor.end(); it++) {
    insertTab(it.key(), it.value());
  }
}

void TabBar::clearBar() {
  for (int i = count(); i > 0; i--) {
    removeTab(i - 1);
  }
}

} // namespace widget
