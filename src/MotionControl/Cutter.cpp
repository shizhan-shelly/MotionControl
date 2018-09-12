// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Cutter.h"

#include "MotionControl/Communication/Modbus/RTUClientHandler.h"

Cutter::Cutter() {}

Cutter::~Cutter() {}

MasterClient *Cutter::modbus_client() {
  return &modbus_client_;
}

bool Cutter::StartupModbusClient() {
  ClientHandler *client_handler_ = new RTUClientHandler("COM1", 19200, 'E', 8, 1, 1);
  client_manager_.RegisterClientHandler(client_handler_);
  modbus_client_.SetClientHandlerManager(&client_manager_);
  return modbus_client_.SetupConnect();
}
