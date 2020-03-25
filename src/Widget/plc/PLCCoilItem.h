// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_PLC_PLCCOILITEM_H__
#define WIDGET_PLC_PLCCOILITEM_H__

#include <QtGui/QWidget.h>

namespace Ui {
class PLCCoilItem;
}

namespace widget {

class PLCCoilItem : public QWidget {
  Q_OBJECT

 public:
  PLCCoilItem(QWidget *parent = NULL,
      const QString &variable_name = "",
      bool default_status = false);

  ~PLCCoilItem();

  void Update(bool current);

 signals:
  void coilControl(const QString &variable_name, bool on);

 private slots:
  void onControl();

 private:
  bool on_;
  QString variable_name_;
  Ui::PLCCoilItem *ui_;

}; // class PLCCoilItem 

} // namespace widget

#endif // WIDGET_PLC_PLCCOILITEM_H__
