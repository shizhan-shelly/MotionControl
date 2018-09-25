// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_DIALOG_BASEDIALOG_H__
#define WIDGET_DIALOG_BASEDIALOG_H__

#include <QtGui/QDialog.h>

namespace Ui {
class BaseDialog;
}

namespace widget {

class BaseDialog : public QDialog {
  Q_OBJECT

 public:
  explicit BaseDialog(QWidget *parent = NULL);
  virtual ~BaseDialog();

 private:
  Ui::BaseDialog *ui_;

}; // class BaseDialog

} // namespace widget

#endif // WIDGET_DIALOG_BASEDIALOG_H__
