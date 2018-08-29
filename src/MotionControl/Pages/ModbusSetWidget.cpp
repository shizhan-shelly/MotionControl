// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ModbusSetWidget.h"

#include "ui_ModbusSetWidget.h"

ModbusSetWidget::ModbusSetWidget(QWidget *parent)
    : ::widget::BaseWidget(parent) {

  ui_ = new Ui::ModbusSetWidgetForm;
  ui_->setupUi(this);
}

ModbusSetWidget::~ModbusSetWidget() {
  delete ui_;
}

void ModbusSetWidget::InitialWidget() {
  QStringList device_model_list;
  device_model_list << "F1650";
  ui_->device_model_->addItems(device_model_list);

  QStringList com_port_list;
  com_port_list << "COM1" << "COM2" << "COM3" << "COM4";
  ui_->com_port_->addItems(com_port_list);

  QStringList baud_rate_list;
  baud_rate_list << "9600" << "19200" << "15200";
  ui_->baud_rate_->addItems(baud_rate_list);

  QStringList parity_list;
  parity_list << "9600" << "19200" << "15200";
  ui_->parity_->addItems(parity_list);
}
