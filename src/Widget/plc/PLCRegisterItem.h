// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_PLC_PLCREGISTERITEM_H__
#define WIDGET_PLC_PLCREGISTERITEM_H__

#include <QtGui/QWidget>

typedef enum _PLCRegisterType {
  Bit16, // short
  Bit32, // int, float
  Bit64 // double

} PLCRegisterType;

class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;

namespace widget {

class PLCRegisterItem : public QWidget {
  Q_OBJECT

 public:
  PLCRegisterItem(QWidget *parent = NULL,
      const QString &variable_name = "",
      const QString &default_value = "",
      PLCRegisterType reg_type = Bit16,
      bool read_only = true);

  ~PLCRegisterItem();

  void Update(const QString &value);

 signals:
  void valueChanged(const QString &variable_name,
      const QString &value);

 private slots:
  void onSend();

 private:
  PLCRegisterType reg_type_;
  QHBoxLayout *layout_;
  QLabel *register_;
  QLineEdit *value_;
  QPushButton *send_;

}; // class PLCRegisterItem

} // namespace widget

#endif // WIDGET_PLC_PLCREGISTERITEM_H__
