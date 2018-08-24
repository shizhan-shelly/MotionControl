// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_MODBUSTCPCLIENT_H__
#define MODBUS_MODBUSTCPCLIENT_H__

#include <string>

#include "MasterClient.h"

/**
 * ModbusTCPClient implement modbus TCP communication with ethernet port.
 */
class ModbusTCPClient : public MasterClient {
 public:
  ModbusTCPClient(const std::string &ip_address, int port, int slave_id);
  ~ModbusTCPClient();

  virtual bool Connect();

}; // class ModbusTCPClient

#endif // MODBUS_MODBUSTCPCLIENT_H__
