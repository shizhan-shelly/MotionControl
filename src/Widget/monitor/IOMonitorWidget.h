// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_MONITOR_IOMONITORWIDGET_H__
#define WIDGET_MONITOR_IOMONITORWIDGET_H__

#include <QtGui/QWidget>

class QGridLayout;

namespace widget {

class IOMonitorItem;

class IOMonitorWidget : public QWidget {
  Q_OBJECT

 public:
  explicit IOMonitorWidget(QWidget *parent = NULL);
  virtual ~IOMonitorWidget();

  void setupPanel(const QVector<QVector<QString> > &infor);
  void Update(const std::vector<unsigned char> &input);

 signals:
  void selected(int current_index);

 private:
  void initialWidget();
  void clearItem();

  QGridLayout *layout_;
  QVector<QVector<IOMonitorItem *> > monitor_items_;

};

} // namespace widget

#endif // WIDGET_MONITOR_IOMONITORWIDGET_H__
