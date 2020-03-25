// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_DIALOG_DEVICEDIAGNOSEDLG_H__
#define WIDGET_DIALOG_DEVICEDIAGNOSEDLG_H__

#include <QtCore/QTimer>

#include "../dialog/BaseDialog.h"

namespace widget {

class DeviceDiagnoseWidget;

class DeviceDiagnoseDlg : public ::widget::BaseDialog {
 public:
  explicit DeviceDiagnoseDlg(QWidget *parent = NULL);
  virtual ~DeviceDiagnoseDlg();

  void setDiagnoseWidget(DeviceDiagnoseWidget *widget);

 protected:
  void showEvent(QShowEvent *event);

 private:
  DeviceDiagnoseWidget *widget_;
  QTimer update_timer_;

}; // class DeviceDiagnoseDlg

} // namespace widget

#endif // WIDGET_DIALOG_DEVICEDIAGNOSEDLG_H__
