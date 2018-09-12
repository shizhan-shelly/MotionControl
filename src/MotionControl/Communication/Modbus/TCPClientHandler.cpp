// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "TCPClientHandler.h"

#include "../../../Modbus/modbus.h"

TCPClientHandler::TCPClientHandler(const std::string &ip_address, int port,
                                   int slave_id) : ClientHandler() {

  ctx_ = modbus_new_tcp(ip_address.c_str(), port);
  modbus_set_slave(ctx_, slave_id);
  slave_id_ = slave_id;
}

TCPClientHandler::~TCPClientHandler() {}

bool TCPClientHandler::Connect() {
  int listen_rtn_ = modbus_tcp_listen(ctx_, 1);
  modbus_tcp_accept(ctx_, &listen_rtn_);
  return true;
}
