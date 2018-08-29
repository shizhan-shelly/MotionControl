// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_H__
#define CUTTER_H__

#include "base/singleton/Singleton.h"
#include "MotionControl/Communication/Modbus/MasterClient.h"

class ClientHandler;

class Cutter : public Singleton {
  DECLARE_SINGLETON(Cutter)

 public:
  MasterClient *modbus_client();

  bool StartupModbusClient();

 private:
  Cutter();
  ~Cutter();

  ClientHandler *client_handler_;
  MasterClient modbus_client_;

}; //class Cutter

#endif // CUTTER_H__
