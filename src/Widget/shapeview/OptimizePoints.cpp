// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "OptimizePoints.h"

#include <assert.h>
#include <math.h>

void OptimizePoints::Simplify(QVector<QPointF> &points,
                              double dis) {

  assert(points.count() > 1);
  for (QVector<QPointF>::iterator p = points.begin(); p < points.end() - 1; p++) {
    for (QVector<QPointF>::iterator q = p + 1; q < points.end(); q++) {
      if (Distance(*p, *q) >= dis) {
        p = q - 1;
        break;
	  } else {
		  q = points.erase(q) - 1;
	  }
	}
  }
}

double OptimizePoints::Distance(const QPointF &pos1, const QPointF &pos2) {
  double x0 = pos1.x();
  double y0 = pos1.y();
  double x1 = pos2.x();
  double y1 = pos2.y();
  return sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));
}
