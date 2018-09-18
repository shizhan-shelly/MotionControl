// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "RTUClientHandler.h"

#include "../../../Modbus/modbus.h"

RTUClientHandler::RTUClientHandler(const std::string &device_name, int baud,
                                   char parity, int data_bit, int stop_bit,
                                   int slave_id) : ClientHandler(slave_id) {

  ctx_ = modbus_new_rtu(device_name.c_str(), baud, parity, data_bit, stop_bit);
  modbus_set_slave(ctx_, slave_id_);
}

RTUClientHandler::~RTUClientHandler() {}

bool RTUClientHandler::Connect() {
  int rc = modbus_connect(ctx_);
  if (rc == -1) {
    //modbus_free(ctx_);
    return false;
  }
  return true;
}
