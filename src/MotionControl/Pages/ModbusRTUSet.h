// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PAGES_MODBUSRTUSET_H__
#define PAGES_MODBUSRTUSET_H__

#include "Widget/basewidget/BaseWidget.h"

namespace Ui {
  class ModbusRTUSetForm;
}

class ModbusRTUSet : public ::widget::BaseWidget {
  Q_OBJECT

 public:
  explicit ModbusRTUSet(QWidget *parent = NULL);
  ~ModbusRTUSet();

  void InitialWidget();

  QString device_model() const;

  QString com_port() const;

  QString baud_rate() const;

  QString parity() const;

  int slave_id() const;

  int data_bits() const;

  int stop_bits() const;

 private:
  Ui::ModbusRTUSetForm *ui_;

}; // class ModbusRTUSet

#endif // PAGES_MODBUSRTUSET_H__
