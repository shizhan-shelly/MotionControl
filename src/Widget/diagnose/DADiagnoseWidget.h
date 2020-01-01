// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_DIAGNOSE_DADIAGNOSEWIDGET_H__
#define WIDGET_DIAGNOSE_DADIAGNOSEWIDGET_H__

#include "../diagnose/DeviceDiagnoseWidget.h"

class QGridLayout;

namespace widget {

class DAMonitorItem;

class DADiagnoseWidget : public DeviceDiagnoseWidget {
  Q_OBJECT

 public:
  explicit DADiagnoseWidget(QWidget *parent = NULL);
  virtual ~DADiagnoseWidget();

  void setupPanel(const QVector<QString> &infor);
  void Update(const QVector<double> &da);

 signals:
  void control(int index, int value);

 private:
  QGridLayout *layout_;
  QVector<DAMonitorItem *> monitor_items_;

  void initialWidget();
  void clearItem();

}; // class DADiagnoseWidget

} // namespace widget

#endif // WIDGET_DIAGNOSE_DADIAGNOSEWIDGET_H__
