// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../listwidget/IconListWidget.h"

namespace widget {

IconListWidget::IconListWidget(QWidget *parent) : BaseListWidget(parent) {
  setViewMode(QListView::IconMode);
}

IconListWidget::~IconListWidget() {}

} // namespace widget
