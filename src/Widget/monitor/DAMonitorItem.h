// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_MONITOR_DAMONITORITEM_H__
#define WIDGET_MONITOR_DAMONITORITEM_H__

#include <QtGui/QWidget>

namespace Ui {
class DAMonitorItem;
}

namespace widget {

class DAMonitorItem : public QWidget {
  Q_OBJECT

 public:
  explicit DAMonitorItem(QWidget *parent = NULL);
  virtual ~DAMonitorItem();

  void setup(const QString &description, int index);
  void Update(double voltage);

 signals:
  void control(int index, float value);

 private slots:
  void onControl(int value);
  void onCalibrate();

 private:
  int index_;
  Ui::DAMonitorItem *ui_;

}; // class DAMonitorItem

} // namespace widget

#endif // WIDGET_MONITOR_DAMONITORITEM_H__
