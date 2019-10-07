// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_HYPER_POWERMAXDIAGNOSE_H__
#define CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_HYPER_POWERMAXDIAGNOSE_H__

#include <QWidget>

namespace Ui {
class PowermaxDiagnose;
}

namespace cutter {

class PowermaxDiagnose : public QWidget {
  Q_OBJECT

 public:
  explicit PowermaxDiagnose(QWidget *parent = NULL);
  ~PowermaxDiagnose();

  void setCurrentStation(int station_id);

  void Update();

 private slots:
  void onGasTest();

 private:
  int station_id_;
  Ui::PowermaxDiagnose *ui_;

  void initialDiagnoseWidget();

}; // class PowermaxDiagnose

} // namespace cutter

#endif // CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_HYPER_POWERMAXDIAGNOSE_H__
