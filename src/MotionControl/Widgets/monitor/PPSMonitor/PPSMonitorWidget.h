// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_IOMONITORWIDGET_PPSMONITORWIDGET_H__
#define CUTTER_WIDGET_IOMONITORWIDGET_PPSMONITORWIDGET_H__

#include <QtGui/QWidget>

namespace Ui {
  class PPSMonitorWidget;
}

namespace cutter {

class PPSMonitorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit PPSMonitorWidget(QWidget *parent = NULL);
  ~PPSMonitorWidget();

 public slots:
  void setCurrentStation(int station_index);

 protected:
  virtual void Update();

 private:
  int station_index_;
  Ui::PPSMonitorWidget *ui_;

  void initialMonitorWidget();

}; // class PPSMonitorWidget

} // namespace cutter

#endif // CUTTER_WIDGET_IOMONITORWIDGET_PPSMONITORWIDGET_H__
