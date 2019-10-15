// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MONITOR_PPS_HYPER_HYPERMONITORWIDGET_H__
#define MONITOR_PPS_HYPER_HYPERMONITORWIDGET_H__

#include <QtGui/QWidget>

namespace Ui {
class HyperMonitorWidget;
}

namespace cutter {

class HyperMonitorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit HyperMonitorWidget(QWidget *parent = NULL);
  virtual ~HyperMonitorWidget();

  void setCurrentStation(int station_id);

  void Update();

 private:
  int station_id_;
  Ui::HyperMonitorWidget *ui_;

}; // class HyperMonitorWidget

} // namespace cutter

#endif // MONITOR_PPS_HYPER_HYPERMONITORWIDGET_H__
