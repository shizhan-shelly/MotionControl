// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MONITOR_PPS_LIUHE_LH270AMONITORWIDGET_H__
#define MONITOR_PPS_LIUHE_LH270AMONITORWIDGET_H__

#include <QtGui/QWidget>

namespace Ui {
class LH270AMonitorWidget;
}

namespace cutter {

class LH270AMonitorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit LH270AMonitorWidget(QWidget *parent = NULL);
  virtual ~LH270AMonitorWidget();

  void setCurrentStation(int station_id);
  void Update();

 private slots:
  void onStateCode();
  void onFaultCode();

 private:
  int station_id_;
  Ui::LH270AMonitorWidget *ui_;

}; // class LH270AMonitorWidget

} // namespace cutter

#endif // MONITOR_PPS_LIUHE_LH270AMONITORWIDGET_H__
