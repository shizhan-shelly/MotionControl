// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_MONITOR_INPUTMONITORWIDGET_H__
#define WIDGET_MONITOR_INPUTMONITORWIDGET_H__

#include <QWidget>

class InputMonitorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit InputMonitorWidget(QWidget *parent = NULL);
  virtual ~InputMonitorWidget();

  void SetupPanel(const QVector<QVector<QString> > &infor);
  void Update(const std::vector<unsigned char> &input);

 private:

};

#endif // WIDGET_MONITOR_INPUTMONITORWIDGET_H__
