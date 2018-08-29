// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PAGES_MODBUSSETWIDGET_H__
#define PAGES_MODBUSSETWIDGET_H__

#include "Widget/basewidget/BaseWidget.h"

namespace Ui {
  class ModbusSetWidgetForm;
}

class ModbusSetWidget : public ::widget::BaseWidget {
  Q_OBJECT

 public:
  explicit ModbusSetWidget(QWidget *parent = NULL);
  ~ModbusSetWidget();

  void InitialWidget();

 private:
  Ui::ModbusSetWidgetForm *ui_;

}; // class ModbusSetWidget

#endif // PAGES_MODBUSSETWIDGET_H__
