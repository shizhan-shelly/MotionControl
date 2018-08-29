// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_TCPCLIENTHANDLER_H__
#define MODBUS_TCPCLIENTHANDLER_H__

#include <string>

#include "ClientHandler.h"

/**
 * TCPClientHandler implement modbus TCP communication with ethernet port.
 */
class TCPClientHandler : public ClientHandler {
 public:
  TCPClientHandler(const std::string &ip_address, int port, int slave_id);
  ~TCPClientHandler();

  virtual bool Connect();

}; // class TCPClientHandler

#endif // MODBUS_TCPCLIENTHANDLER_H__
