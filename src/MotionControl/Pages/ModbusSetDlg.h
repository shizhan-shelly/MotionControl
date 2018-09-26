// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PAGES_MODBUSSETDLG_H__
#define PAGES_MODBUSSETDLG_H__

#include "Widget/dialog/BaseDialog.h"

#include "MotionControl/Communication/Modbus/ModbusProtocol.h"

class ModbusRTUSet;
class ModbusTCPSet;

class ModbusSetDlg : public ::widget::BaseDialog {
 public:
  explicit ModbusSetDlg(QWidget *parent = NULL);
  ~ModbusSetDlg();

  void SetModbusProtocol(ModbusProtocol type);

 private:
  ModbusRTUSet *rtu_set_;
  ModbusTCPSet *tcp_set_;

}; // class ModbusSetDlg

#endif // PAGES_MODBUSSETDLG_H__
