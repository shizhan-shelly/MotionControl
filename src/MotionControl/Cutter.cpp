// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Cutter.h"

#include "MotionControl/Communication/Modbus/RTUClientHandler.h"

Cutter::Cutter() : client_handler_(NULL) {}

Cutter::~Cutter() {}

MasterClient *Cutter::modbus_client() {
  return &modbus_client_;
}

bool Cutter::StartupModbusClient() {
  if (client_handler_) {
    delete client_handler_;
    client_handler_ = NULL;
  }
  client_handler_ = new RTUClientHandler("COM1", 19200, 'E', 8, 1, 1);
  modbus_client_.SetMasterClientHandler(client_handler_);
  return modbus_client_.SetupConnect();
}
