// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "CircleItem.h"

#include <QtGui/QPainter>
#include <QtGui/QStyleOptionGraphicsItem>
#include <QtGui/QWidget>

CircleItem::CircleItem() {
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
}

CircleItem::~CircleItem() {}

void CircleItem::setupCircle(double radius) {
  radius_ = radius;
}

void CircleItem::setCircleColor(const QColor &circle_color) {
  color_ = circle_color;
}

double CircleItem::getRadius() const {
  return radius_;
}

QRectF CircleItem::boundingRect() const {
  return QRectF(-radius_, -radius_, 2 * radius_, 2 * radius_);
}

void CircleItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {

  QColor circle_color = collidingItems().isEmpty() ? color_ : Qt::red;
  painter->setPen(QPen(QBrush(circle_color), isSelected() ? 1 : 0.5,
      Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

  painter->drawEllipse(boundingRect());
}

QPainterPath CircleItem::shape() const {
  QPainterPath path;
  path.addEllipse(boundingRect());
  return path;
}
