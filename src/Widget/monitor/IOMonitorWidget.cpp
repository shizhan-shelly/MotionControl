// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "IOMonitorWidget.h"

#include <assert.h>

#include <QtGui/QGridLayout>
#include <QtGui/QSpacerItem>

#include "IOMonitorItem.h"

namespace widget {

IOMonitorWidget::IOMonitorWidget(QWidget *parent)
    : QWidget(parent) {

  layout_ = new QGridLayout;
  layout_->setContentsMargins(0, 0, 0, 0);
  setLayout(layout_);
}

IOMonitorWidget::~IOMonitorWidget() {
  clearItem();
}

void IOMonitorWidget::Update(const std::vector<unsigned char> &input) {
  bool status[][8] = {false};
  for (size_t i = 0; i < input.size(); i++) {
    for (size_t j = 0; j < 8; j++) {
      status[i][j] = input[i] & (0x01 << j);
    }
  }
  //
}

void IOMonitorWidget::setupPanel(const QVector<QVector<QString> > &infor) {
  assert(!info.empty());
  clearItem();
  QVector<QPair<QString, int> >::const_iterator io_info = info.begin();
  while (io_info != info.end()) {
    monitor_items_.push_back(new IOMonitorItem(this));
    connect(monitor_items_.last(), SIGNAL(selected(int)),
        this, SIGNAL(selected(int)));

    monitor_items_.last()->setup(io_info->first, io_info->second);
    ++io_info;
  }
  initialWidget();
}

void IOMonitorWidget::initialWidget() {
}

void IOMonitorWidget::clearItem() {
  monitor_items_.clear();
  QLayoutItem *item_widget = NULL;
  for (int i = 0; i < layout_->rowCount(); i++) {
    for (int j = 0; j < layout_->columnCount(); j++) {
      item_widget = layout_->itemAtPosition(i, j);
      if (item_widget) {
        item_widget->widget()->hide();
        layout_->removeItem(item_widget);
        delete item_widget;
        item_widget = NULL;
      }
    }
  }
}

} // namespace widget
