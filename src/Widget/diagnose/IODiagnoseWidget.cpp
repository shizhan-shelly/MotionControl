// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../diagnose/IODiagnoseWidget.h"

#include <assert.h>

#include <QtGui/QGridLayout>
#include <QtGui/QSpacerItem>

#include "../monitor/IOMonitorItem.h"

namespace widget {

IODiagnoseWidget::IODiagnoseWidget(QWidget *parent)
    : DeviceDiagnoseWidget(parent) {

  layout_ = new QGridLayout;
  layout_->setContentsMargins(0, 0, 0, 0);
  layout_->setSpacing(0);
  setLayout(layout_);
}

IODiagnoseWidget::~IODiagnoseWidget() {
  clearItem();
}

void IODiagnoseWidget::SetClickable(bool clickable) {
  for (int i = 0; i < monitor_items_.size(); i++) {
    for (int j = 0; j < monitor_items_[i].size(); j++) {
    }
  }
}

void IODiagnoseWidget::Update(const QVector<unsigned char> &status) {
  for (int i = 0; i < monitor_items_.size(); i++) {
    for (int j = 0; j < monitor_items_[i].size(); j++) {
      int index = i == 0 ? j : monitor_items_[i - 1].size() * i + j;
      assert(index < status.size());
      monitor_items_[i][j]->Update(status[index] != 0);
    }
  }
}

void IODiagnoseWidget::setupPanel(const QVector<QVector<QString> > &infor) {
  assert(!infor.empty());
  clearItem();
  for (int i = 0; i < infor.size(); ++i) {
    QVector<IOMonitorItem *> column;
    for (int j = 0; j < infor[i].size(); ++j) {
      IOMonitorItem *monitor_item = new IOMonitorItem(this);
      int index = i == 0 ? j : infor[i - 1].size() * i + j;
      monitor_item->setup(infor[i][j], index);
      column.push_back(monitor_item);
      connect(column.last(), SIGNAL(selected(int)),
          this, SIGNAL(selected(int)));

      connect(column.last(), SIGNAL(stateChanged(int, bool)),
          this, SIGNAL(stateChanged(int, bool)));

    }
    monitor_items_.push_back(column);
  }
  initialWidget();
}

void IODiagnoseWidget::initialWidget() {
  for (int i = 0; i < monitor_items_.size(); i++) {
    for (int j = 0; j < monitor_items_[i].size(); j++) {
      layout_->addWidget(monitor_items_[i][j], j, i);
    }
    layout_->setColumnStretch(i, 1);
  }
  layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding),
      layout_->rowCount(), 0, 1, 1);

  layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum),
      0, layout_->columnCount(), 1, 1);

}

void IODiagnoseWidget::clearItem() {
  monitor_items_.clear();
  QLayoutItem *item_widget = NULL;
  for (int i = 0; i < layout_->rowCount(); i++) {
    for (int j = 0; j < layout_->columnCount(); j++) {
      item_widget = layout_->itemAtPosition(i, j);
      if (item_widget) {
        if (item_widget->widget()) {
          item_widget->widget()->hide();
        }
        layout_->removeItem(item_widget);
        delete item_widget;
        item_widget = NULL;
      }
    }
  }
}

} // namespace widget
