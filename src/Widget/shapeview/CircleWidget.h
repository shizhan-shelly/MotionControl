// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_CIRCLEWIDGET_H__
#define CHARGEWIDGET_CIRCLEWIDGET_H__

#include <QtCore/QPointF>
#include <QtCore/QVector>
#include <QtGui/QColor>
#include <QtGui/QWidget>

class CircleWidget : public QWidget {
  Q_OBJECT

 public:
  CircleWidget(QWidget *parent = NULL);
  ~CircleWidget();
  void clearAll();

 public slots:
  void onPunched(QPointF &pos, double radius);

 protected:
  void paintEvent(QPaintEvent *event);

 private:
  QVector<QPointF> position_;
  QVector<double> radius_;
  static const QColor PROC_COLOR_;

}; // class CircleWidget

#endif // CHARGEWIDGET_CIRCLEWIDGET_H__
