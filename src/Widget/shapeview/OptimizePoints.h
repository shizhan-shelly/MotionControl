// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_OPTIMIZEPOINTS_H__
#define CHARGEWIDGET_OPTIMIZEPOINTS_H__

#include <QtCore/QPointF>
#include <QtCore/QVector>

/**
 * class OptimizePoints design an optimize method to reduce points on outline.
 * After optimizing, any two points within specific distance will be merged
 * into one point and the sum should be reduced to a certain extent.
 */
class OptimizePoints {
 public:
  /**
   * FunctionName: Simplify()
   * Description:
   * Thhis function will simplify a number of points from user to delete one of
   * any two points with short gap.
   * @param [out]: points, points on the outline from user are simplified.
   * @param [in]: dis, specific shortest distance between any two points.
   * Unit: mm.
   */
  static void Simplify(QVector<QPointF> &points, double dis);

 private:
  static double Distance(const QPointF &pos1, const QPointF &pos2);

}; // class OptimizePoints

#endif // CHARGEWIDGET_OPTIMIZEPOINTS_H__
