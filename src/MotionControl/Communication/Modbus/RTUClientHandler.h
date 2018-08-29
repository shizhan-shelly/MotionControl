// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_RTUCLIENTHANDLER_H__
#define MODBUS_RTUCLIENTHANDLER_H__

#include <string>

#include "ClientHandler.h"

/**
 * RTUClientHandler implement modbus RTU communication with serial port.
 */
class RTUClientHandler : public ClientHandler {
 public:
  RTUClientHandler(const std::string &device_name, int baud = 9600,
                   char parity = 'E', int data_bit = 8, int stop_bit = 1,
                   int slave_id = 1);

  ~RTUClientHandler();

  virtual bool Connect();

}; // class RTUClientHandler

#endif // MODBUS_RTUCLIENTHANDLER_H__
