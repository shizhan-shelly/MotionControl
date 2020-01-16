// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../diagnose/DADiagnoseWidget.h"

#include <assert.h>

#include <QtGui/QGridLayout>
#include <QtGui/QSpacerItem>

#include "../monitor/DAMonitorItem.h"

namespace widget {

DADiagnoseWidget::DADiagnoseWidget(QWidget *parent)
    : DeviceDiagnoseWidget(parent) {

  layout_ = new QGridLayout;
  layout_->setContentsMargins(0, 0, 0, 0);
  layout_->setSpacing(0);
  setLayout(layout_);
}

DADiagnoseWidget::~DADiagnoseWidget() {
  clearItem();
}

void DADiagnoseWidget::Update(const QVector<double> &da) {
  assert(monitor_items_.size() <= da.size());
  for (int i = 0; i < monitor_items_.size(); i++) {
    monitor_items_[i]->Update(da[i]);
  }
}

void DADiagnoseWidget::setupPanel(const QVector<QString> &infor) {
  assert(!infor.empty());
  clearItem();
  for (int i = 0; i < infor.size(); ++i) {
    DAMonitorItem *item = new DAMonitorItem(this);
    item->setup(infor[i], i);
    connect(item, SIGNAL(control(int, float)), this, SIGNAL(control(int, float)));
    monitor_items_.push_back(item);
  }
  initialWidget();
}

void DADiagnoseWidget::initialWidget() {
  static const int MAX_ROW_CNT = 4;
  for (int i = 0; i < monitor_items_.size(); i++) {
    layout_->addWidget(monitor_items_[i], i % MAX_ROW_CNT, i / MAX_ROW_CNT);
  }
  layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding),
      layout_->rowCount(), 0, 1, 1);

  layout_->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum),
      0, layout_->columnCount(), 1, 1);

}

void DADiagnoseWidget::clearItem() {
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
