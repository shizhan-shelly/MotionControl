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
  for (size_t i = 0; i < input.size(); i++) {
    for (size_t j = 0; j < 8; j++) {
      bool status = input[i] & (0x01 << j);
      monitor_items_[i][j]->Update(status);
    }
  }
}

void IOMonitorWidget::setupPanel(const QVector<QVector<QString> > &infor) {
  assert(!infor.empty());
  clearItem();
  for (int i = 0; i < infor.size(); ++i) {
    QVector<IOMonitorItem *> column;
    for (int j = 0; j < infor[i].size(); ++j) {
      column.push_back(new IOMonitorItem(this));
      connect(column.last(), SIGNAL(selected(int)),
          this, SIGNAL(selected(int)));

      column.last()->setup(infor[i][j], i * 8 + j);
    }
    monitor_items_.push_back(column);
  }
  initialWidget();
}

void IOMonitorWidget::initialWidget() {
  for (int i = 0; i < monitor_items_.size(); i++) {
    for (int j = 0; j < monitor_items_[i].size(); j++) {
      layout_->addWidget(monitor_items_[i][j], j, i);
    }
    layout_->setColumnStretch(i, 1);
  }
  layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding),
      8, 0);

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
