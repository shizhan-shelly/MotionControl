// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ModbusTCPClient.h"

#include "../../../Modbus/modbus.h"

ModbusTCPClient::ModbusTCPClient(const std::string &ip_address, int port,
                                 int slave_id) : MasterClient() {

  ctx_ = modbus_new_tcp(ip_address.c_str(), port);
  modbus_set_slave(ctx_, slave_id);
}

ModbusTCPClient::~ModbusTCPClient() {}

bool ModbusTCPClient::Connect() {
  int listen_rtn_ = modbus_tcp_listen(ctx_, 1);
  modbus_tcp_accept(ctx_, &listen_rtn_);
  return true;
}
