// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SortCircles.h"

#include <math.h>

void SortCircles::Sort(QVector<QPointF> &circles) {
  ResetFirstCircle(circles);
  for (int i = 0; i < circles.count() - 1; i++) {
    double min_distance = Distance(circles[i], circles[i + 1]);
    int index = i + 1;
    for (int j = i + 2; j < circles.count(); j++) {
      double dis = Distance(circles[i], circles[j]);
      if (dis < min_distance) {
        min_distance = dis;
        index = j;
      }
    }
    if (index != i + 1) {
      Swap(circles[index], circles[i + 1]);
    }
  }
}

double SortCircles::Distance(const QPointF &pos1, const QPointF &pos2) {
  double x0 = pos1.x();
  double y0 = pos1.y();
  double x1 = pos2.x();
  double y1 = pos2.y();
  return sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));
}

void SortCircles::Swap(QPointF &circle1, QPointF &circle2) {
  QPointF im_circle = circle1;
  circle1 = circle2;
  circle2 = im_circle;
}

void SortCircles::ResetFirstCircle(QVector<QPointF> &circles) {
  double max_dis = 0;
  int index = 0;
  for (int i = 0; i < circles.count(); i++) {
    double dis = Distance(circles[i], QPointF(0, 0));
    if (dis > max_dis) {
      max_dis = dis;
      index = i;
    }
  }
  if (index != 0) {
    Swap(circles[index], circles[0]);
  }
}
