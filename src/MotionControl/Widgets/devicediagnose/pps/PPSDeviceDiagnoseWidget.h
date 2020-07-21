// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_PPSDEVICEDIAGNOSEWIDGET_H__
#define CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_PPSDEVICEDIAGNOSEWIDGET_H__

#include <QWidget>

namespace Ui {
class PPSDeviceDiagnoseWidget;
}

namespace cutter {

class PPSDeviceDiagnoseWidget : public QWidget {
  Q_OBJECT

 public:
  explicit PPSDeviceDiagnoseWidget(QWidget *parent = NULL);
  ~PPSDeviceDiagnoseWidget();

 public slots:
  void Update();

 protected:
  virtual void showEvent(QShowEvent *event);

 private slots:
  void onStationIndex(int index);
  void onNotify();

 private:
  int station_id_;
  Ui::PPSDeviceDiagnoseWidget *ui_;

  void initialDiagnoseWidget();

}; // class PPSDeviceDiagnoseWidget

} // namespace cutter

#endif // CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_PPSDEVICEDIAGNOSEWIDGET_H__
