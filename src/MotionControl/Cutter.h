// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_H__
#define CUTTER_H__

#include "base/singleton/Singleton.h"
#include "MotionControl/Communication/Modbus/MasterClient.h"

class KerfTableModel;

class Cutter : public Singleton {
  DECLARE_SINGLETON(Cutter)

 public:
  MasterClient *modbus_client();

  void InitModbusClient();

  bool StartupModbusConnect();

  KerfTableModel *GetKerfTableModel() const {
    return kerf_table_model_;
  }

  void InitKerfTableModel();

 private:
  Cutter();
  ~Cutter();

  MasterClient modbus_client_;
  ClientHandlerManager client_manager_;
  KerfTableModel *kerf_table_model_;

}; //class Cutter

#endif // CUTTER_H__
