// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "PLCCoilItem.h"

#include "ui_PLCCoilItem.h"

static const QString GREEN_BTN = "background: rgb(0, 255, 0)";
static const QString RED_BTN = "background: rgb(255, 0, 0)";

namespace widget {

PLCCoilItem::PLCCoilItem(QWidget *parent,
    const QString &variable_name,
    bool default_status) : QWidget(parent)
                         , on_(default_status)
                         , variable_name_(variable_name) {

  ui_ = new Ui::PLCCoilItem;
  ui_->setupUi(this);

  ui_->coil_->setText(variable_name_);
  ui_->button_->setStyleSheet(on_ ? GREEN_BTN : RED_BTN);

  connect(ui_->button_, SIGNAL(clicked()), this, SLOT(onControl()));
}

PLCCoilItem::~PLCCoilItem() {
  delete ui_;
}

void PLCCoilItem::Update(bool current) {
  on_ = current;
  ui_->button_->setStyleSheet(on_ ? GREEN_BTN : RED_BTN);
}

void PLCCoilItem::onControl() {
  emit coilControl(variable_name_, !on_);
}

} // namespace widget
