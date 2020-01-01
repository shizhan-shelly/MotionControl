// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ADMonitorItem.h"

#include <assert.h>

#include "ui_ADMonitorItem.h"

namespace widget {

ADMonitorItem::ADMonitorItem(QWidget *parent) : QWidget(parent) {
  ui_ = new Ui::ADMonitorItem;
  ui_->setupUi(this);
}

ADMonitorItem::~ADMonitorItem() {
  delete ui_;
}

void ADMonitorItem::setup(const QString &description) {
  assert(!description.isEmpty());
  ui_->description_->setText(description);
}

void ADMonitorItem::Update(double voltage) {
  ui_->voltage_->setText(QString("%1").arg(voltage, 0, 'f', 2));
}

} // namespace widget
