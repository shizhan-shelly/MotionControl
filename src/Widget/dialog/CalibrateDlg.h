// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_DIALOG_CALIBRATEDLG_H__
#define WIDGET_DIALOG_CALIBRATEDLG_H__

#include "../dialog/BaseDialog.h"

namespace widget {

class CalibrateWidget;

class CalibrateDlg : public ::widget::BaseDialog {
 public:
  explicit CalibrateDlg(QWidget *parent = NULL);
  virtual ~CalibrateDlg();

  double factor() const;

  double base() const;

 private:
  CalibrateWidget *widget_;

}; // class CalibrateDlg

} // namespace widget

#endif // WIDGET_DIALOG_CALIBRATEDLG_H__
