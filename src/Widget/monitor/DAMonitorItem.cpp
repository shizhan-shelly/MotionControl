// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "DAMonitorItem.h"

#include <assert.h>

#include "ui_DAMonitorItem.h"

namespace widget {

DAMonitorItem::DAMonitorItem(QWidget *parent) : QWidget(parent)
                                              , index_(0) {

  ui_ = new Ui::DAMonitorItem;
  ui_->setupUi(this);

  connect(ui_->control_, SIGNAL(valueChanged(int)),
      this, SLOT(onControl(int)));

}

DAMonitorItem::~DAMonitorItem() {
  delete ui_;
}

void DAMonitorItem::setup(const QString &description, int index) {
  assert(!description.isEmpty());
  ui_->description_->setText(description);
  index_ = index;
}

void DAMonitorItem::Update(double voltage) {
  ui_->voltage_->setText(QString("%1").arg(voltage, 0, 'f', 2));
}

void DAMonitorItem::onControl(int value) {
  emit control(index_, value);
}

} // namespace widget
