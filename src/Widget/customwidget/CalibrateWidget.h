// Copyright 2020 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_CUSTOMWIDGET_CALIBRATEWIDGET_H__
#define WIDGET_CUSTOMWIDGET_CALIBRATEWIDGET_H__

#include <QWidget>

namespace Ui {
class CalibrateWidget;
}

namespace widget {

class CalibrateWidget : public QWidget {
  Q_OBJECT

 public:
  explicit CalibrateWidget(QWidget *parent = NULL);
  virtual ~CalibrateWidget();

  double factor() const {
    return factor_;
  }
  double base() const {
    return base_;
  }

 private slots:
  void onCalculate();

 private:
  double factor_;
  double base_;
  Ui::CalibrateWidget *ui_;

}; // CalibrateWidget

} // namespace widget

#endif // WIDGET_CUSTOMWIDGET_CALIBRATEWIDGET_H__
