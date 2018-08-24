// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_MODBUSRTUCLIENT_H__
#define MODBUS_MODBUSRTUCLIENT_H__

#include <string>

#include "MasterClient.h"

/**
 * ModbusRTUClient implement modbus RTU communication with serial port.
 */
class ModbusRTUClient : public MasterClient {
 public:
  ModbusRTUClient(const std::string &device_name, int baud = 9600, char parity = 'E',
                  int data_bit = 8, int stop_bit = 1, int slave_id = 1);

  ~ModbusRTUClient();

  virtual bool Connect();

}; // class ModbusRTUClient

#endif // MODBUS_MODBUSRTUCLIENT_H__
