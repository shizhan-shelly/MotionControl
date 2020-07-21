// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_HYPER_HPRDIAGNOSE_H__
#define CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_HYPER_HPRDIAGNOSE_H__

#include <QWidget>

namespace Ui {
class HPRDiagnose;
}

namespace cutter {

class HPRDiagnose : public QWidget {
  Q_OBJECT

 public:
  explicit HPRDiagnose(QWidget *parent = NULL);
  ~HPRDiagnose();

  void setCurrentStation(int station_id);

  void Update();

 signals:
  void notify();

 private slots:
  void onPreflowGasTest();
  void onCutflowGasTest();
  void onManualPumpCtrl();
  void onSystemReset();
  void onSetParameter();
  void onErrorCode();
  void onClearRecord();

 private:
  int station_id_;
  Ui::HPRDiagnose *ui_;

  void initialDiagnoseWidget();

}; // class HPRDiagnose

} // namespace cutter

#endif // CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_HYPER_HPRDIAGNOSE_H__
