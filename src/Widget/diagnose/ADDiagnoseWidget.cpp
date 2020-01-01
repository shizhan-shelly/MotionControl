// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../diagnose/ADDiagnoseWidget.h"

#include <assert.h>

#include <QtGui/QGridLayout>
#include <QtGui/QSpacerItem>

#include "../monitor/ADMonitorItem.h"

namespace widget {

ADDiagnoseWidget::ADDiagnoseWidget(QWidget *parent)
    : DeviceDiagnoseWidget(parent) {

  layout_ = new QGridLayout;
  layout_->setContentsMargins(0, 0, 0, 0);
  layout_->setSpacing(0);
  setLayout(layout_);
}

ADDiagnoseWidget::~ADDiagnoseWidget() {
  clearItem();
}

void ADDiagnoseWidget::Update(const QVector<double> &ad) {
  assert(monitor_items_.size() <= ad.size());
  for (int i = 0; i < monitor_items_.size(); i++) {
    monitor_items_[i]->Update(ad[i]);
  }
}

void ADDiagnoseWidget::setupPanel(const QVector<QString> &infor) {
  assert(!infor.empty());
  clearItem();
  for (int i = 0; i < infor.size(); ++i) {
    ADMonitorItem *item = new ADMonitorItem(this);
    item->setup(infor[i]);
    monitor_items_.push_back(item);
  }
  initialWidget();
}

void ADDiagnoseWidget::initialWidget() {
  static const int MAX_ROW_CNT = 4;
  for (int i = 0; i < monitor_items_.size(); i++) {
    layout_->addWidget(monitor_items_[i], i % MAX_ROW_CNT, i / MAX_ROW_CNT);
  }
  layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding),
      layout_->rowCount(), 0, 1, 1);

  layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum),
      0, layout_->columnCount(), 1, 1);

}

void ADDiagnoseWidget::clearItem() {
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
