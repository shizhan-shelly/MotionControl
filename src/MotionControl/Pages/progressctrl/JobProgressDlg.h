// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PAGES_PROGRESSCTRL_JOBPROGRESSDLG_H__
#define PAGES_PROGRESSCTRL_JOBPROGRESSDLG_H__

#include <QtCore/QTimer>

#include "Widget/dialog/BaseDialog.h"

class ProgressCtrl;

class JobProgressDlg : public ::widget::BaseDialog {
  Q_OBJECT

 public:
  explicit JobProgressDlg(QWidget *parent = NULL);
  virtual ~JobProgressDlg();

  void StartProgress();

 public slots:
  void OnTimer();

 private:
  int entry_;
  QTimer start_timer_;
  ProgressCtrl *progress_ctrl_;

}; // class JobProgressDlg

#endif // PAGES_PROGRESSCTRL_JOBPROGRESSDLG_H__
