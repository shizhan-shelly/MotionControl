// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_MONITOR_ADMONITORITEM_H__
#define WIDGET_MONITOR_ADMONITORITEM_H__

#include <QtGui/QWidget>

namespace Ui {
class ADMonitorItem;
}

namespace widget {

class ADMonitorItem : public QWidget {
  Q_OBJECT

 public:
  explicit ADMonitorItem(QWidget *parent = NULL);
  virtual ~ADMonitorItem();

  void setup(const QString &description);
  void Update(double voltage);

 private:
  Ui::ADMonitorItem *ui_;

}; // class ADMonitorItem

} // namespace widget

#endif // WIDGET_MONITOR_ADMONITORITEM_H__
