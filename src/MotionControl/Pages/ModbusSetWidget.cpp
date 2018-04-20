// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ModbusSetWidget.h"

#include "ui_ModbusSetWidget.h"

ModbusSetWidget::ModbusSetWidget(QWidget *parent) : QWidget(parent) {
  ui_ = new Ui::ModbusSetWidgetForm;
  ui_->setupUi(this);
}

ModbusSetWidget::~ModbusSetWidget() {
  delete ui_;
}
