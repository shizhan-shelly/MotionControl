// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUSSETWIDGET_H
#define MODBUSSETWIDGET_H

#include <QWidget>

namespace Ui {
  class ModbusSetWidgetForm;
}

class ModbusSetWidget : public QWidget {
  Q_OBJECT

 public:
  explicit ModbusSetWidget(QWidget *parent = NULL);
  ~ModbusSetWidget();

 private:
  Ui::ModbusSetWidgetForm *ui_;

}; // class ModbusSetWidget

#endif // MODBUSSETWIDGET_H
