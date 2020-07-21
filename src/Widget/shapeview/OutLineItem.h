// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CHARGEWIDGET_OUTLINEITEM_H__
#define CHARGEWIDGET_OUTLINEITEM_H__

#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QVector>
#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>
#include <QtGui/QPainterPath>

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

/**
 * Class OutLineItem designs a custom item for drawing a polygon outline shape
 * with specific point arrays on a graphics view.
 */
class OutLineItem : public QGraphicsItem {
 public:
  OutLineItem();
  ~OutLineItem();

  /**
   * FunctionName: initialPoints()
   * Description:
   * This function initials the points which constitute a polygon outline.
   * @param [in]: points, starting point or ending point of a polygonline.
   * Unit: (mm, mm).
   */
  void initialPoints(const QVector<QPointF> &points);

  /**
   * FunctionName: setLineColor()
   * Description:
   * This function sets the color of polygonline.
   * @param [in]: line_color, polygonline's color.
   */
  void setLineColor(const QColor &line_color);

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
   * This function paints a OutLineItem object in local coordinates.
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
  QVector<QPointF> points_;
  QColor color_;

}; // class OutLineItem

#endif  // CHARGEWIDGET_OUTLINEITEM_H__
