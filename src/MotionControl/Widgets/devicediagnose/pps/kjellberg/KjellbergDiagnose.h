// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_KJELLBERG_KJELLBERGDIAGNOSE_H__
#define CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_KJELLBERG_KJELLBERGDIAGNOSE_H__

#include <QWidget>

namespace Ui {
class KjellbergDiagnose;
}

namespace cutter {

class KjellbergDiagnose : public QWidget {
  Q_OBJECT

 public:
  explicit KjellbergDiagnose(QWidget *parent = NULL);
  ~KjellbergDiagnose();

  void setCurrentStation(int station_id);

  void Update();

 signals:
  void notify();

 private slots:
  void onPPSQueryDeviceInfor();
  void onPPSQueryParameter();
  void onPPSTransmitParamLong();
  void onPPSTransmitParamShort();
  void onPPSRemoteOff();
  void onPGCQueryDeviceInfor();
  void onPGCQueryParameter();
  void onPGCTransmitParameter();

  void onEditPGCParameter();
  void onEditPPSParameter();

  void onPPSErrorCodeShow();
  void onPPSStatusCodeShow();
  void onPPSWarningCodeShow();
  void onPGCErrorCodeShow();
  void onPGCStatusCodeShow();

  void onDigitalInput();
  void onDigitalSignals();

 private:
  int station_id_;
  Ui::KjellbergDiagnose *ui_;

  void initialDiagnoseWidget();

}; // class KjellbergDiagnose

} // namespace cutter

#endif // CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_KJELLBERG_KJELLBERGDIAGNOSE_H__
