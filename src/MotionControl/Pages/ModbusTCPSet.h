// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PAGES_MODBUSTCPSET_H__
#define PAGES_MODBUSTCPSET_H__

#include "Widget/basewidget/BaseWidget.h"

namespace Ui {
  class ModbusTCPSetForm;
}

class ModbusTCPSet : public ::widget::BaseWidget {
  Q_OBJECT

 public:
  explicit ModbusTCPSet(QWidget *parent = NULL);
  ~ModbusTCPSet();

  void InitialWidget();

  QString device_model() const;

  QString ip_address() const;

  int slave_id() const;

  int port_number() const;

 private:
  Ui::ModbusTCPSetForm *ui_;

}; // class ModbusTCPSet

#endif // PAGES_MODBUSTCPSET_H__
