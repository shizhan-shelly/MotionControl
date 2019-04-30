// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PAGES_PROGRESSCTRL_PROGRESSCTRL_H__
#define PAGES_PROGRESSCTRL_PROGRESSCTRL_H__

#include <QtGui/QWidget>

namespace Ui {
class ProgressCtrlForm;
}

class ProgressCtrl : public QWidget {
  Q_OBJECT

 public:
  explicit ProgressCtrl(QWidget *parent = NULL);
  virtual ~ProgressCtrl();

  void initProgress(const QString &prompt, int whole);

 public slots:
  void onProgress(int index);

 private:
  int entry_;
  QString prompt_;
  Ui::ProgressCtrlForm *ui_;

}; // class ProgressCtrl

#endif // PAGES_PROGRESSCTRL_PROGRESSCTRL_H__
