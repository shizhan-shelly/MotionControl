// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_LIUHE_LH270ADIAGNOSE_H__
#define CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_LIUHE_LH270ADIAGNOSE_H__

#include <QWidget>

class QButtonGroup;

namespace Ui {
class LH270ADiagnose;
}

namespace cutter {

class LH270ADiagnose : public QWidget {
  Q_OBJECT

 public:
  explicit LH270ADiagnose(QWidget *parent = NULL);
  ~LH270ADiagnose();

  void setCurrentStation(int station_id);

  void Update();

 signals:
  void notify();

 private slots:
  void onSwitchMonitor(int monitor_id);
  void onPPSOutputSwitch(int index);
  void onGCOutputSwitch(int index);
  void onResolve();
  void onConnect();
  void onDebugMode();
  void onRemoteMode();
  void onManualPumpMode();
  void onManualPumpOn();
  void onManualPumpOff();
  void onPreflowGasSet();
  void onCutflowGasSet();
  void onGasLeakTestMode();
  void onInletLeakTest();
  void onSystemLeakTest();
  void onProportionValvesCheck();
  void onSetting();

 private:
  int station_id_;
  QButtonGroup *diagnose_btn_group_;
  QButtonGroup *pps_output_btn_group_;
  QButtonGroup *gc_output_btn_group_;
  Ui::LH270ADiagnose *ui_;

  void initialDiagnoseWidget();
  void UpdatePPSInfors();
  void UpdatePPSRecords();
  void UpdatePPSInputs();
  void UpdatePPSOutputs();
  void UpdateGCInputs();
  void UpdateGCOutputs();

}; // class LH270ADiagnose

} // namespace cutter

#endif // CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_LIUHE_LH270ADIAGNOSE_H__
