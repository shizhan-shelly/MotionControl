// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_DIAGNOSE_ADDIAGNOSEWIDGET_H__
#define WIDGET_DIAGNOSE_ADDIAGNOSEWIDGET_H__

#include "../diagnose/DeviceDiagnoseWidget.h"

class QGridLayout;

namespace widget {

class ADMonitorItem;

class ADDiagnoseWidget : public DeviceDiagnoseWidget {
  Q_OBJECT

 public:
  explicit ADDiagnoseWidget(QWidget *parent = NULL);
  virtual ~ADDiagnoseWidget();

  void setupPanel(const QVector<QString> &infor);
  void Update(const QVector<double> &ad);

 protected:
  QVector<ADMonitorItem *> monitor_items_;

 private:
  QGridLayout *layout_;

  void initialWidget();
  void clearItem();

}; // class ADDiagnoseWidget

} // namespace widget

#endif // WIDGET_DIAGNOSE_ADDIAGNOSEWIDGET_H__
