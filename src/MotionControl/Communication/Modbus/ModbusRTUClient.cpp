// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ModbusRTUClient.h"

#include "../../../Modbus/modbus.h"

ModbusRTUClient::ModbusRTUClient(const std::string &device_name, int baud,
                                 char parity, int data_bit, int stop_bit,
                                 int slave_id) : MasterClient() {

  ctx_ = modbus_new_rtu(device_name.c_str(), baud, parity, data_bit, stop_bit);
  modbus_set_slave(ctx_, slave_id);
}

ModbusRTUClient::~ModbusRTUClient() {}

bool ModbusRTUClient::Connect() {
  int rc = modbus_connect(ctx_);
  if (rc == -1) {
    modbus_free(ctx_);
    return false;
  }
  return true;
}
