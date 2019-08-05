// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MONITOR_PPS_HYPER_POWERMAXMONITORWIDGET_H__
#define MONITOR_PPS_HYPER_POWERMAXMONITORWIDGET_H__

#include <QtGui/QWidget>

namespace Ui {
class PowermaxMonitorWidget;
}

class PowermaxMonitorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit PowermaxMonitorWidget(QWidget *parent = NULL);
  virtual ~PowermaxMonitorWidget();

  void setCurrentStation(int station_id);
  void Update();

 private:
  int station_id_;
  Ui::PowermaxMonitorWidget *ui_;

}; // class PowermaxMonitorWidget

#endif // MONITOR_PPS_HYPER_POWERMAXMONITORWIDGET_H__
