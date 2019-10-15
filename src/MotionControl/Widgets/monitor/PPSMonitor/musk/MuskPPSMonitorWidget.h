// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_IOMONITORWIDGET_MUSKPPSMONITORWIDGET_H__
#define CUTTER_WIDGET_IOMONITORWIDGET_MUSKPPSMONITORWIDGET_H__

#include <QWidget>

namespace Ui {
  class MuskPPSMonitorWidget;
}

namespace cutter {

class MuskPPSMonitorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit MuskPPSMonitorWidget(QWidget *parent = NULL);
  ~MuskPPSMonitorWidget();

  void setCurrentStation(int station_index);
  void Update();

 private slots:
  void onCutCurrentAdd();
  void onCutCurrentSub();

 private:
  int station_index_;
  Ui::MuskPPSMonitorWidget *ui_;

}; // class MuskPPSMonitorWidget

} // namespace cutter

#endif // CUTTER_WIDGET_IOMONITORWIDGET_MUSKPPSMONITORWIDGET_H__
