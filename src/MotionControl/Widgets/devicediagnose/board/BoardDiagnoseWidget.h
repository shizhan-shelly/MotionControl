// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGETS_DEVICEDIAGNOSE_BOARD_BOARDDIAGNOSEWIDGET_H__
#define WIDGETS_DEVICEDIAGNOSE_BOARD_BOARDDIAGNOSEWIDGET_H__

#include "Widget/diagnose/DeviceDiagnoseWidget.h"

namespace Ui {
class BoardDiagnoseWidget;
}

class BoardDiagnoseWidget : public widget::DeviceDiagnoseWidget {
  Q_OBJECT

 public:
  explicit BoardDiagnoseWidget(QWidget *parent = NULL);
  virtual ~BoardDiagnoseWidget();

 public slots:
  virtual void Update();

 protected:
  virtual void showEvent(QShowEvent *event);

 private slots:
  void onSwitchBoard(int board_index);

 private:
  int board_index_;
  Ui::BoardDiagnoseWidget *ui_;

}; // class BoardDiagnoseWidget

#endif // WIDGETS_DEVICEDIAGNOSE_BOARD_BOARDDIAGNOSEWIDGET_H__
