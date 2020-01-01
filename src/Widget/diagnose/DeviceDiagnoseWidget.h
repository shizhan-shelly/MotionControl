// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_DIAGNOSE_DEVICEDIAGNOSEWIDGET_H__
#define WIDGET_DIAGNOSE_DEVICEDIAGNOSEWIDGET_H__

#include "../basewidget/BaseWidget.h"

namespace widget {

class DeviceDiagnoseWidget : public BaseWidget {
  Q_OBJECT

 public:
  explicit DeviceDiagnoseWidget(QWidget *parent = NULL);
  virtual ~DeviceDiagnoseWidget();

 public slots:
  virtual void Update();

};

} // namespace widget

#endif // WIDGET_DIAGNOSE_DEVICEDIAGNOSEWIDGET_H__
