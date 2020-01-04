// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_MONITOR_IOMONITORITEM_H__
#define WIDGET_MONITOR_IOMONITORITEM_H__

#include <QtGui/QFocusEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWidget>

namespace Ui {
class IOMonitorItem;
}

namespace widget {

class IOMonitorItem : public QWidget {
  Q_OBJECT

 public:
  explicit IOMonitorItem(QWidget *parent = NULL);
  virtual ~IOMonitorItem();

  void setup(const QString &description, int index);
  void Update(bool status);

 signals:
  void selected(int current_index);
  void stateChanged(int current_index, bool on);

 protected:
  void focusInEvent(QFocusEvent *event);
  void focusOutEvent(QFocusEvent *event);
  void mousePressEvent(QMouseEvent *event);

 private slots:
  void OnStateChanged(bool on);

 private:
  bool selected_;
  int index_;
  Ui::IOMonitorItem *ui_;

};

} // namespace widget

#endif // WIDGET_MONITOR_IOMONITORITEM_H__
