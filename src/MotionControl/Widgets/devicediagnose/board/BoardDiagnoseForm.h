// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGETS_DEVICEDIAGNOSE_BOARD_BOARDDIAGNOSEFORM_H__
#define WIDGETS_DEVICEDIAGNOSE_BOARD_BOARDDIAGNOSEFORM_H__

#include "Widget/diagnose/DeviceDiagnoseWidget.h"

namespace Ui {
class BoardDiagnoseForm;
}

class BoardDiagnoseForm : public widget::DeviceDiagnoseWidget {
  Q_OBJECT

 public:
  explicit BoardDiagnoseForm(QWidget *parent = NULL);
  virtual ~BoardDiagnoseForm();

  void setCurrentBoard(int board_index);

 public slots:
  virtual void Update();

 private slots:
  void onOutputControl(int current_id, bool on);
  void onDAControl(int current_id, float value);

 private:
  int board_index_;
  Ui::BoardDiagnoseForm *ui_;

}; // class BoardDiagnoseForm

#endif // WIDGETS_DEVICEDIAGNOSE_BOARD_BOARDDIAGNOSEFORM_H__
