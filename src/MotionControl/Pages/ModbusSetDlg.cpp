// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Pages/ModbusSetDlg.h"

#include "MotionControl/Pages/ModbusRTUSet.h"
#include "MotionControl/Pages/ModbusTCPSet.h"

ModbusSetDlg::ModbusSetDlg(QWidget *parent) : widget::BaseDialog(parent)
                                            , rtu_set_(NULL)
                                            , tcp_set_(NULL) {

  rtu_set_ = new ModbusRTUSet(this);
  rtu_set_->InitialWidget();
  tcp_set_ = new ModbusTCPSet(this);
  tcp_set_->InitialWidget();
  ui_->stack_widget_->addWidget(rtu_set_);
  ui_->stack_widget_->addWidget(tcp_set_);
}

ModbusSetDlg::~ModbusSetDlg() {
  delete rtu_set_;
  delete tcp_set_;
}

void ModbusSetDlg::SetModbusProtocol(ModbusProtocol type) {
  switch(type) {
   case ASCII:
   case RTU:
    ui_->stack_widget_->setCurrentWidget(rtu_set_);
    break;
   case TCP:
    ui_->stack_widget_->setCurrentWidget(tcp_set_);
    break;
   default:
    break;
  }
}
