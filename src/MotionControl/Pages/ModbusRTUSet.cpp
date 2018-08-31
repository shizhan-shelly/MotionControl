// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ModbusRTUSet.h"

#include "ui_ModbusRTUSet.h"

ModbusRTUSet::ModbusRTUSet(QWidget *parent)
    : ::widget::BaseWidget(parent) {

  ui_ = new Ui::ModbusRTUSetForm;
  ui_->setupUi(this);
}

ModbusRTUSet::~ModbusRTUSet() {
  delete ui_;
}

void ModbusRTUSet::InitialWidget() {
  QStringList device_model_list;
  device_model_list << "F1650";
  ui_->device_model_->addItems(device_model_list);

  QStringList com_port_list;
  com_port_list << "COM1" << "COM2" << "COM3" << "COM4";
  ui_->com_port_->addItems(com_port_list);

  QStringList baud_rate_list;
  baud_rate_list << "9600" << "19200" << "115200";
  ui_->baud_rate_->addItems(baud_rate_list);

  QStringList parity_list;
  parity_list << "None" << "Odd" << "Even";
  ui_->parity_->addItems(parity_list);
}

QString ModbusRTUSet::device_model() const {
  return ui_->device_model_->currentText();
}

QString ModbusRTUSet::com_port() const {
  return ui_->com_port_->currentText();
}

QString ModbusRTUSet::baud_rate() const {
  return ui_->baud_rate_->currentText();
}

QString ModbusRTUSet::parity() const {
  return ui_->parity_->currentText();
}

int ModbusRTUSet::slave_id() const {
  return atoi(ui_->slave_id_->text().toStdString().c_str());
}

int ModbusRTUSet::data_bits() const {
  return atoi(ui_->data_bit_->text().toStdString().c_str());
}

int ModbusRTUSet::stop_bits() const {
  return atoi(ui_->stop_bit_->text().toStdString().c_str());
}
