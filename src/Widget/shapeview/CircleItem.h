// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_CIRCLEITEM_H__
#define CHARGEWIDGET_CIRCLEITEM_H__

#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>
#include <QtGui/QPainterPath>

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

/**
 * Class CircleItem designs a custom item for drawing a circle with
 * specfic radius and center position on a graphics view.
 */
class CircleItem : public QGraphicsItem {
 public:
  CircleItem();
  ~CircleItem();

  /**
   * FunctionName: setupCircle()
   * Description:
   * This function sets the circle's radius.
   * @param [in]: radius, circle's radius. Unit: mm.
   */
  void setupCircle(double radius);

  /**
   * FunctionName: setCircleColor()
   * Description:
   * This function sets the color of circumference.
   * @param [in]: circle_color, circumference's color.
   */
  void setCircleColor(const QColor &circle_color);

  /**
   * FunctionName: getCircleInfo()
   * Description:
   * This function gets the circle item's radius.
   * @return: circle's radius.
   */
  double getRadius() const;

  /**
   * FunctionName: boundingRect()
   * Description:
   * This function defines the outer bounds of the item as a rectangle.
   * @return: the item's bounding rectangle region.
   */
  QRectF boundingRect() const;

  /**
   * FunctionName: paint()
   * Description:
   * This function paints a CircleItem object in local coordinates.
   * @param [in]: painter, provide the item's painting implementation.
   * @param [in]: option, provides style options for the item.
   * @param [in]: widget, If provided, it points to the widget that is being
   * painted on; otherwise, it is 0.
   */
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = NULL);

  /**
   * FunctionName: shape()
   * Description:
   * This function sets the item's accurate shape for collision detection.
   * @return: the shape of this item as a QPainterPath in local coordinates.
   */
  QPainterPath shape() const;

 private:
  double radius_;
  QColor color_;

}; // class CircleItem

#endif  // CHARGEWIDGET_CIRCLEITEM_H__
