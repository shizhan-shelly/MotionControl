// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MONITOR_PPS_LIUHE_LIUHEMONITORWIDGET_H__
#define MONITOR_PPS_LIUHE_LIUHEMONITORWIDGET_H__

#include <QtGui/QWidget>

namespace Ui {
class LiuheMonitorWidget;
}

namespace cutter {

class LiuheMonitorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit LiuheMonitorWidget(QWidget *parent = NULL);
  virtual ~LiuheMonitorWidget();

  void setCurrentStation(int station_id);

  void Update();

 private:
  int station_id_;
  Ui::LiuheMonitorWidget *ui_;

}; // class LiuheMonitorWidget

} // namespace cutter

#endif // MONITOR_PPS_LIUHE_LIUHEMONITORWIDGET_H__
