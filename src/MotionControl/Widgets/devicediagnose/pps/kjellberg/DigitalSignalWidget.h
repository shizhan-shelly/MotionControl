// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_KJELLBERG_DIGITALSIGNALWIDGET_H__
#define CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_KJELLBERG_DIGITALSIGNALWIDGET_H__

#include "cutter/widget/devicediagnose/board/IODiagnoseWidget.h"

namespace cutter {

class DigitalSignalWidget : public IODiagnoseWidget {
  Q_OBJECT

 public:
  explicit DigitalSignalWidget(QWidget *parent = NULL);
  virtual ~DigitalSignalWidget();

  void setCurrentStation(int station_id);
  void Update();

 private:
  int station_id_;

};

} // namespace cutter

#endif // CUTTER_WIDGET_DEVICEDIAGNOSE_PPS_KJELLBERG_DIGITALSIGNALWIDGET_H__
