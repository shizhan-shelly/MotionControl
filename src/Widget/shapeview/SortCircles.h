// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_SORTCIRCLES_H__
#define CHARGEWIDGET_SORTCIRCLES_H__

#include <QtCore/QPointF>
#include <QtCore/QVector>

/**
 * Class SortCircles can be used to reset the storage sequence of circles
 * provided from user in a way of seeking shortest distance between any two
 * circles.
 */
class SortCircles {
 public:
  /**
   * FunctionName: Sort()
   * Description:
   * This function will sort several circles in a specical way of shortest
   * path.
   * @param [out]: circles, original circles' information provided from user.
   * The first circle is the circle of farthest distance with original point.
   */
  static void Sort(QVector<QPointF> &circles);

 private:
  /// calculate the diistance between two circles' center.
  static double Distance(const QPointF &pos1, const QPointF &pos2);

  /// Exchange the two circle items' storage sequence.
  static void Swap(QPointF &circle1, QPointF &circle2);

  /// Find the circle which has maxmum distance from (0, 0), and insert it into
  /// the first position of vector.
  static void ResetFirstCircle(QVector<QPointF> &circles);

}; // class SortCircles

#endif // CHARGEWIDGET_SORTCIRCLES_H__
