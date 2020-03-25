// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_DIAGNOSE_IODIAGNOSEWIDGET_H__
#define WIDGET_DIAGNOSE_IODIAGNOSEWIDGET_H__

#include "../diagnose/DeviceDiagnoseWidget.h"

class QGridLayout;

namespace widget {

class IOMonitorItem;

class IODiagnoseWidget : public DeviceDiagnoseWidget {
  Q_OBJECT

 public:
  explicit IODiagnoseWidget(QWidget *parent = NULL);
  virtual ~IODiagnoseWidget();

  void setupPanel(const QVector<QVector<QString> > &infor);
  void Update(const QVector<unsigned char> &status);
  void SetClickable(bool clickable);

 signals:
  void selected(int current_index);
  void stateChanged(int current_index, bool on);

 protected:
  QVector<QVector<IOMonitorItem *> > monitor_items_;

 private:
  QGridLayout *layout_;

  void initialWidget();
  void clearItem();

}; // class IODiagnoseWidget

} // namespace widget

#endif // WIDGET_DIAGNOSE_IODIAGNOSEWIDGET_H__
