// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ModbusTCPSet.h"

#include "ui_ModbusTCPSet.h"

ModbusTCPSet::ModbusTCPSet(QWidget *parent)
    : ::widget::BaseWidget(parent) {

  ui_ = new Ui::ModbusTCPSetForm;
  ui_->setupUi(this);
}

ModbusTCPSet::~ModbusTCPSet() {
  delete ui_;
}

void ModbusTCPSet::InitialWidget() {
  QStringList device_model_list;
  device_model_list << "F1650" << "LH270A";
  ui_->device_model_->addItems(device_model_list);
}

QString ModbusTCPSet::device_model() const {
  return ui_->device_model_->currentText();
}

QString ModbusTCPSet::ip_address() const {
  return ui_->ip_address_->text();
}

int ModbusTCPSet::slave_id() const {
  return atoi(ui_->slave_id_->text().toStdString().c_str());
}

int ModbusTCPSet::port_number() const {
  return atoi(ui_->port_number_->text().toStdString().c_str());
}
