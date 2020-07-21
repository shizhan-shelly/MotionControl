// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "OutLineItem.h"

#include <QtGui/QGraphicsScene>
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionGraphicsItem>
#include <QtGui/QWidget>

OutLineItem::OutLineItem() {}

OutLineItem::~OutLineItem() {}

void OutLineItem::initialPoints(const QVector<QPointF> &points) {
  points_ = points;
}

void OutLineItem::setLineColor(const QColor &line_color) {
  color_ = line_color;
}

QRectF OutLineItem::boundingRect() const {
  return QPolygonF(points_).boundingRect();
}

void OutLineItem::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {

  QColor line_color = collidingItems().isEmpty() ? color_ : Qt::red;
  painter->setPen(QPen(QBrush(line_color), 0.5, Qt::SolidLine, Qt::RoundCap,
      Qt::RoundJoin));

  painter->drawPolygon(points_.begin(), points_.count());
}

QPainterPath OutLineItem::shape() const {
  QPainterPath path;
  path.addPolygon(QPolygonF(points_));
  path.closeSubpath();
  return path;
}
